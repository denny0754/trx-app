#include <iostream>
#include <trx/Application.hpp>

int main()
{
	trx::Application::Get().Initialize();

	trx::Application::Get().Run();

	trx::Application::Get().Shutdown();

	return 0;
}