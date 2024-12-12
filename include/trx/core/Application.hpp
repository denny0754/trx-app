/*
	`transaction-x` allows users to manage their personal expenses.
	Copyright (C) 2024  Diego Vaccher

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#pragma once

/* Project Headers */
#include <trx/core/framework/Framework.hpp>
#include <trx/core/event/Event.hpp>

/* Standard Headers */
#include <vector>
#include <memory>
#include <mutex>

namespace trx
{

class Application
{
public:
	/**
	* 
	* Returns a single instance of the Application.
	* The first time this method is called, the instance is create.
	* 
	* @return The single instance of the Application.
	* 
	**/
	static Application& Get();

	/**
	* 
	* Initializes all components of the Application.
	* 
	**/
	void Initialize();

	/**
	* 
	* Runs the application in an infinite loop
	* until the `Stop` method is called.
	* 
	**/
	void Run();

	/**
	* 
	* Stops the Application execution.
	* `Shutdown` method must be called to de-initialize all components.
	* 
	**/
	void Stop();

	/**
	* 
	* Shutsdown the Application and all its components.
	* 
	**/
	void Shutdown();

	/**
	 * 
	 * Event Listener for when the Application
	 * should stop
	 * 
	 **/
	void OnApplicationStopEvent(Event* event);

protected:
	/**
	 * 
	 * Initializes the global logger,
	 * which would be used by all components
	 * of the application.
	 * 
	 **/
	void InitializeLogging();

	/**
	 * 
	 * Initializes the global configuration
	 * by either reading from the file located
	 * at `./cfg/application.cfg` or, if not found,
	 * creates a default configuration.
	 * 
	 * The default configuration will be saved at the end of the
	 * initialization of this method, only if the file does not exists.
	 * 
	 **/
	void InitializeConfiguration();

	void OnFrameworkEvent(Event* event);

private:
	/**
	* 
	* Default constructor of the application.
	* Set at default becase the initialization is done on the
	* `Initialize` method.
	* Defined in the private scope to avoid the creation of multiple
	* instances of this class.
	* 
	**/
	Application() = default;

private:
	/**
	* 
	* Member variable to store the state of execution of the Application.
	* 
	**/
	std::atomic<bool> m_running;

	/** 
	 * 
	 * A vector of Frameworks.
	 * 
	 **/
	std::vector<std::shared_ptr<Framework>> m_frameworks;
};

} // ns trx