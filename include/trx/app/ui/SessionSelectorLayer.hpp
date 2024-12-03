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
#include <trx/core/ui/Layer.hpp>
#include <trx/app/event/WindowResizeEvent.hpp>
#include <trx/core/Middleware.hpp>

/* External Headers */
#include <imgui.h>

/* Standard Headers */
#include <vector>

namespace trx
{

class SessionSelectorLayer : public Layer
{
public:
    SessionSelectorLayer();

    void OnInitialize() override;

    void OnRender() override;

    void OnUpdate(double delta) override;

    void OnShutdown() override;

protected:
	void OnWindowResize(Event* event);

private:
	ImVec2 m_selectorPivotPos;
	ImVec2 m_selectorWinSize;
};

} // ns trx