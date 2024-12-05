/* Project Headers */
#include <trx/utils/logging/LogManager.hpp>
#include <trx/core/Application.hpp>
#include <trx/core/framework/FrontendFw.hpp>
#include <trx/core/Middleware.hpp>
#include <trx/core/runtime/RTResourceManager.hpp>
#include <trx/core/thread/ThreadPool.hpp>
#include <trx/app/runtime/RTAppConfig.hpp>

/* External Headers */
#include <nlohmann/json.hpp>

/* Standard Headers */
#include <iostream>
#include <fstream>

namespace trx
{

static Application* g_instance = nullptr;

Application& Application::Get()
{
	if (!g_instance)
	{
		g_instance = new Application();
	}
	return *g_instance;
}

void Application::Initialize()
{
	LogManager::Get().Initialize();

	RTResourceManager::Get().Initialize();
	
	Middleware::Get().Initialize();

	RTResourceManager::Get().PushResource("GLB_APP_CONFIG", std::make_shared<RTAppConfig>());
	RTResourceManager::Get().PushResource("USR_APP_CONFIG", std::make_shared<RTAppConfig>());

	/* Loading the Global and User settings */
	std::string default_settings_jdata = R"({"appearance":{"font":"","height":720,"vsync":true,"width":1280},"log":{"file_size":50,"level":"info","max_retention":10}})";
	RTResourceManager::Get().GetResource("GLB_APP_CONFIG")->ToType<RTAppConfig>()->LoadOrDefault("./cfg/app.json", default_settings_jdata);
	RTResourceManager::Get().GetResource("USR_APP_CONFIG")->ToType<RTAppConfig>()->LoadOrDefault("./cfg/usr_app.json", default_settings_jdata);

	InitializeLogging();

	TRX_INF("APP", "Bootstraping the application.");

	Middleware::Get().RegisterListener(
		EventKey::APPLICATION_SHOULD_CLOSE,
		std::bind(&Application::OnApplicationStopEvent, g_instance, std::placeholders::_1)
	);
	
	TRX_TRC("APP", "Pushing all registered frameworks to the Stack.");
	m_frameworks.push_back(std::make_shared<FrontendFw>());
	TRX_TRC("APP", "Finished pushing frameworks to the Framework Stack. Number of frameworks registered: {0}", m_frameworks.size());

	// Initializing all Frameworks
	for(auto& fw : m_frameworks)
	{
		fw->Initialize();
	}

	TRX_INF("APP", "Application has finished boostraping. Everything has been initialized.");

	m_running = true;
}

void Application::Run()
{
	TRX_DBG("APP", "Initializing Thread Pool for detached frameworks...");
	trx::ThreadPool framework_pool = trx::ThreadPool();

	for(auto& fw : m_frameworks)
	{
		if(fw->IsDetached())
		{
			framework_pool.Submit([this, fw](){
				while(m_running.load(std::memory_order_acquire))
				{
					try
					{
						fw->Update();
					}
					catch(std::exception& exception)
					{
						TRX_ERR("APP", "Error while updating framework task: {0}", exception.what());
					}
					catch(...)
					{
						TRX_ERR("APP", "An unknown error occured while updating framework in the Thread Pool.");
					}
				}
			});
		}
	}

	while (m_running.load(std::memory_order_acquire))
	{
		for(auto& fw : m_frameworks)
		{
			if(!fw->IsDetached())
			{
				fw->Update();
			}
		}
	}

	TRX_INF("APP", "Exiting the application. Good bye!!");
}

void Application::Stop()
{
	m_running.store(false, std::memory_order_release);
}

void Application::Shutdown()
{
	TRX_DBG("APP", "Shutting down all frameworks registered.");

	for(auto& fw : m_frameworks)
	{
		fw->Shutdown();
	}

	RTResourceManager::Get().Shutdown();

	delete g_instance;
}

void Application::InitializeLogging()
{

	nlohmann::json& config = RTResourceManager::Get().GetResource("GLB_APP_CONFIG")->ToType<RTAppConfig>()->GetConfig();

	auto log_level = config["log"]["level"].get<spdlog::level::level_enum>();
	auto log_file_size = config["log"]["file_size"].get<unsigned int>();
	auto max_retention = config["log"]["max_retention"].get<unsigned int>();

	LogSettings app_log_settings = LogSettings();

#if defined(TRX_DEVELOPER_BUILD)
	app_log_settings.EnableConsole = true;
#endif
	app_log_settings.EnableFile = true;
	app_log_settings.EnableRotatingFile = true;
	app_log_settings.MaxFileSize = log_file_size * 1024 * 1024;
	app_log_settings.MinLevel = log_level;
	app_log_settings.Name = "APP";
	app_log_settings.NrOfRotatingFiles = max_retention;
	app_log_settings.OutFilePath = "./log/app.txt";

	LogManager::Get().RegisterLogger(app_log_settings);
}

void Application::OnApplicationStopEvent(Event* event)
{
	Stop();
}

} // ns trx