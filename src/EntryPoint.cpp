#include <iostream>
#include <trx/core/Application.hpp>

int main()
{
	trx::core::Application::Get().Initialize();

	//trx::core::Application::Get().Run();
	// Test Commit 2

	trx::core::Application::Get().Shutdown();
	return 0;
}