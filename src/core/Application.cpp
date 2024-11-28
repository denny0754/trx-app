/* Project Headers */
#include <trx/core/Application.hpp>
#include <trx/core/framework/FrontendFw.hpp>
#include <trx/core/Middleware.hpp>
#include <trx/utils/logging/LogManager.hpp>

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
	Middleware::Get().Initialize();
	{
		LogSettings app_log_settings = LogSettings();
		app_log_settings.EnableConsole = true;
		app_log_settings.EnableFile = false;
		app_log_settings.MinLevel = spdlog::level::level_enum::info;
		app_log_settings.Name = "Application";
		TRX_REG_LOGGER(app_log_settings);
	}

	TRX_GET_LOGGER("Application").info("Initializing the Application...");

	Middleware::Get().RegisterListener(
		EventKey::APPLICATION_SHOULD_CLOSE,
		std::bind(&Application::OnApplicationStopEvent, g_instance, std::placeholders::_1)
	);

	m_frameworks.push_back(new FrontendFw());

	TRX_INF("Application", "Number of frameworks initialized: {}", m_frameworks.size());

	// Initializing all Frameworks
	for(auto& fw : m_frameworks)
	{
		fw->Initialize();
	}

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
	TRX_GET_LOGGER("Application").info("Exiting application...");
}

void Application::Stop()
{
	m_running = false;
}

void Application::Shutdown()
{
	TRX_INF("Application", "Shutting down all frameworks.");
	for(auto& fw : m_frameworks)
	{
		fw->Shutdown();
		delete fw;
	}

	delete g_instance;
}

void Application::OnApplicationStopEvent(Event* event)
{
	Stop();
}

} // ns trx