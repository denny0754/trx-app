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
#include <trx/app/event/LayerEvent.hpp>

/* Standard Headers */
#include <unordered_map>
#include <vector>

namespace trx
{

class LayerStack
{
public:
    LayerStack();

	void PushOverlay(std::shared_ptr<Layer> layer);

    void PushLayer(std::shared_ptr<Layer> layer);

	void PopOverlay(const std::string& overlay_name);

    void PopLayer(const std::string& layer_name);

    void Update(double frame_time);

    void Render();

    void Shutdown();

protected:
	void OnLayerEvent(Event* event);

	std::vector<std::shared_ptr<Layer>>::iterator FindLayer(const std::string& layer_name);

private:
	std::vector<std::shared_ptr<Layer>> m_layers;

	size_t m_layerOverlayIndex;
};

} // ns trx