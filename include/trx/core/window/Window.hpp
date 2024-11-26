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
#include <trx/core/window/WindowContextSettings.hpp>

/* External Headers */
#include <GLFW/glfw3.h>

/* Standard Headers */
#include <string>

namespace trx
{

class Window
{
public:
	Window(Vector2u win_size, const std::string& win_title);

	Window(const WindowContextSettings& context_settings);

	void SetSize(Vector2u win_size);

	Vector2u GetSize() const;

	void SetTitle(const std::string& win_title);

	const std::string& GetTitle() const;

private:
	void InitWindow();

private:
	GLFWwindow* m_nativeWindow;

	WindowContextSettings m_winSettings;
};

} // ns trx