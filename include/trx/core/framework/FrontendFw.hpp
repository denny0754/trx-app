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

class FrontendFw : public Framework
{
public:
	FrontendFw() = default;

	void Initialize() override;

	void Update() override;

	void Shutdown() override;

	void Restart() override;

private:
	GLFWwindow* m_nativeWindow;

	ImGuiIO m_imguiContext;

	LayerStack m_layerStack;

	Config m_config;
};

} // ns trx