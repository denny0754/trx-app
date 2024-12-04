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
#include <trx/core/ui/LayerStack.hpp>
#include <trx/utils/config/Config.hpp>

/* External Headers */
#include <GLFW/glfw3.h>
#include <imgui.h>

/* Standard Headers */
#include <memory>
#include <vector>

namespace trx
{

/**
 * 
 * The Frontend framework is the framework responsible
 * of managing the Frontend components and processes.
 * Generally, this framework only manages the initialization,
 * update and rendering of all Layers.
 * The actual logics and processes are actually managed by
 * individual Layers or Overlays, such as the Main menu bar.
 * 
 **/
class FrontendFw : public Framework
{
public:
	/**
	 * 
	 * Constructor without parameters marked as default as
	 * all the initialization of the Framework is done
	 * by the `Initialize` method.
	 * 
	 **/
	FrontendFw() = default;

	/**
	 * 
	 * Initializes the frontend framework.
	 * The following components are initialized:
	 * 
	 *	* `GLFW` Window and `GLFW` Context.
	 * 
	 * 	* `ImGui` Context.
	 * 
	 * 	* Initial layers and overlays through the Layer Stack.
	 * 
	 * 	* `GLFW` Callbacks and `Middleware` listeners .
	 * 
	 **/
	void Initialize() override;

	/**
	 * 
	 * This method updates the Layer Stack.
	 * 
	 **/
	void Update() override;

	/**
	 * 
	 * Shutsdown and destroys all contexts: GLFW, ImGui and Layer Stack.
	 * 
	 **/
	void Shutdown() override;

	/**
	 * 
	 * Restarts the Frontend framework by firstly
	 * shutting it down with a call to the `Shutdown` method
	 * and then a re-initialization using the `Initialize` method.
	 * 
	 **/
	void Restart() override;

private:
	/**
	 * 
	 * Native GLFW window.
	 * 
	 **/
	GLFWwindow* m_nativeWindow;

	/**
	 * 
	 * The Layer Stack holding all managed
	 * layers and overlays.
	 * 
	 **/
	LayerStack m_layerStack;

	/**
	 * 
	 * The configuration of the Frontend, which
	 * is currently read from a static file path at: `./cfg/frontend.cfg`
	 * 
	 **/
	Config m_config;
};

} // ns trx