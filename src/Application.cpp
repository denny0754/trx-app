/* Project Headers */
#include <trx/util/logging/LogManager.hpp>
#include <trx/Application.hpp>
#include <trx/ui/FrontendFw.hpp>
#include <trx/ev/MiddlewareFw.hpp>
#include <trx/rsrc/RTResourceManagerFw.hpp>
#include <trx/sys/ThreadPool.hpp>
#include <trx/rsrc/RTAppConfig.hpp>
#include <trx/ev/FrameworkEvent.hpp>

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
	util::LogManager::Get().Initialize();

	// Middleware Initialization
	std::shared_ptr<ev::MiddlewareFw> mw_fw = std::make_shared<ev::MiddlewareFw>();
	m_frameworks[mw_fw->GetFwID()] = mw_fw;

	// Runtime Resource Manager Initialization
	std::shared_ptr<rsrc::RTResourceManagerFw> rt_fw = std::make_shared<rsrc::RTResourceManagerFw>();
	m_frameworks[rt_fw->GetFwID()] = rt_fw;

	rt_fw->PushResource("GLB_APP_CONFIG", std::make_shared<rsrc::RTAppConfig>());
	rt_fw->PushResource("USR_APP_CONFIG", std::make_shared<rsrc::RTAppConfig>());

	/* Loading the Global and User settings */
	std::string default_settings_jdata = R"({"appearance":{"font":"","height":720,"vsync":true,"width":1280},"log":{"file_size":50,"level":"info","max_retention":10}})";
	rt_fw->GetResource("GLB_APP_CONFIG")->ToType<rsrc::RTAppConfig>()->LoadOrDefault("./cfg/app.json", default_settings_jdata);
	rt_fw->GetResource("USR_APP_CONFIG")->ToType<rsrc::RTAppConfig>()->LoadOrDefault("./cfg/usr_app.json", default_settings_jdata);

	InitializeLogging();

	TRX_INF("APP", "Bootstraping the application.");
	
	std::shared_ptr<ui::FrontendFw> fw_fw = std::make_shared<ui::FrontendFw>();
	m_frameworks[fw_fw->GetFwID()] = fw_fw;

	TRX_TRC("APP", "Finished pushing frameworks to the Framework Stack. Number of frameworks registered: {0}", m_frameworks.size());

	// Initializing all Frameworks
	for (auto& [fw_id, fw] : m_frameworks)
	{
		TRX_TRC("APP", "Initializing Framework with ID `{0}`...", fw_id);
		fw->Initialize();
	}

	// Subscribing Listeners to the MW
	mw_fw->Subscribe(
		ev::EventKey::APPLICATION_SHOULD_CLOSE,
		std::bind(&Application::OnApplicationStopEvent, g_instance, std::placeholders::_1)
	);

	mw_fw->Subscribe(
		ev::EventKey::BOOTSTRAP_FRAMEWORK,
		std::bind(&Application::OnFrameworkEvent, g_instance, std::placeholders::_1)
	);

	TRX_INF("APP", "Application has finished boostraping. Everything has been initialized.");

	m_running = true;
}

void Application::Run()
{
	TRX_DBG("APP", "Initializing Thread Pool for detached frameworks...");
	trx::ThreadPool framework_pool = trx::ThreadPool();

	for(auto& [fw_id, fw] : m_frameworks)
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
		for(auto& [fw_id, fw] : m_frameworks)
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

	for(auto& [fw_id, fw] : m_frameworks)
	{
		TRX_DBG("APP", "Shutting down Framework with ID `{0}`", fw_id);
		fw->Shutdown();
	}

	delete g_instance;
}

std::shared_ptr<intf::Framework> Application::GetFw(const std::string& fwId)
{
	if (m_frameworks.find(fwId) != m_frameworks.end())
	{
		return m_frameworks.at(fwId);
	}
	return nullptr;
}

void Application::InitializeLogging()
{
	if (GetFw("_APP_RT_RSRC_MANAGER") != nullptr)
	{
		auto rt_fw = GetFw("_APP_RT_RSRC_MANAGER")->ToType<rsrc::RTResourceManagerFw*>();
		nlohmann::json& config = rt_fw->GetResource("GLB_APP_CONFIG")->ToType<rsrc::RTAppConfig>()->GetConfig();

		auto log_level = config["log"]["level"].get<spdlog::level::level_enum>();
		auto log_file_size = config["log"]["file_size"].get<unsigned int>();
		auto max_retention = config["log"]["max_retention"].get<unsigned int>();

		util::LogSettings app_log_settings = util::LogSettings();

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

		util::LogManager::Get().RegisterLogger(app_log_settings);
	}
}

void Application::OnApplicationStopEvent(ev::Event* event)
{
	Stop();
}

void Application::OnFrameworkEvent(ev::Event* event)
{
	const ev::FrameworkEvent* fw_event = event->ToType<ev::FrameworkEvent>();
	const ev::FrameworkEventData* fw_event_data = event->GetEventData()->ToType<ev::FrameworkEventData>();

	if (fw_event->GetEventKey() == ev::EventKey::BOOTSTRAP_FRAMEWORK)
	{
		const std::string& fw_id = fw_event_data->GetFramework()->GetFwID();
		if (m_frameworks.find(fw_id) != m_frameworks.end())
		{
			if (!m_frameworks.at(fw_id)->ShouldRegisterOnce())
			{
				m_frameworks.erase(fw_id);
				m_frameworks[fw_id] = std::shared_ptr<intf::Framework>(fw_event_data->GetFramework());
			}
			else
			{
				// Should we really manage the restart of a Framework this way?
				m_frameworks.at(fw_id)->Restart();
			}
		}
		else
		{
			m_frameworks[fw_id] = std::shared_ptr<intf::Framework>(fw_event_data->GetFramework());
		}
	}
}

} // ns trx