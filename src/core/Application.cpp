/* Project Headers */
#include <trx/utils/logging/LogManager.hpp>
#include <trx/core/Application.hpp>
#include <trx/core/framework/FrontendFw.hpp>
#include <trx/core/Middleware.hpp>
#include <trx/core/runtime/RTResourceManager.hpp>
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
	RTResourceManager::Get();

	LogManager::Get().Initialize();

	RTResourceManager::Get().PushResource("GLB_APP_CONFIG", std::make_shared<RTAppConfig>());

	InitializeLogging();

	RTResourceManager::Get().Initialize();
	
	Middleware::Get().Initialize();

	TRX_INF("APP", "Bootstraping the application.");

	Middleware::Get().RegisterListener(
		EventKey::APPLICATION_SHOULD_CLOSE,
		std::bind(&Application::OnApplicationStopEvent, g_instance, std::placeholders::_1)
	);

	m_frameworks.push_back(new FrontendFw());

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
	while (m_running)
	{
		for(auto& fw : m_frameworks)
		{
			fw->Update();
		}
	}
	TRX_INF("APP", "Exiting the application. Good bye!!");
}

void Application::Stop()
{
	m_running = false;
}

void Application::Shutdown()
{
	TRX_DBG("APP", "Shutting down all frameworks registered.");

	for(auto& fw : m_frameworks)
	{
		fw->Shutdown();
		delete fw;
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

	app_log_settings.EnableConsole = false;
	app_log_settings.EnableFile = true;
	app_log_settings.EnableRotatingFile = true;
	// app_log_settings.MaxFileSize = log_file_size * 1024 * 1024;
	app_log_settings.MinLevel = spdlog::level::level_enum::trace;
	app_log_settings.Name = "APP";
	// app_log_settings.NrOfRotatingFiles = max_retention;
	app_log_settings.OutFilePath = "./log/app.txt";

	LogManager::Get().RegisterLogger(app_log_settings);
}

void Application::OnApplicationStopEvent(Event* event)
{
	Stop();
}

} // ns trx