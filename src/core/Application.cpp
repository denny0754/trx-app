#include <trx/core/Application.hpp>

namespace trx
{
namespace core
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

}

void Application::Run()
{
	while (m_running)
	{

	}
}

void Application::Stop()
{
	m_running = false;
}

void Application::Shutdown()
{
	delete g_instance;
}

} // ns core
} // ns trx