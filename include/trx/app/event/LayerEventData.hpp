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
#include <trx/core/event/EventData.hpp>
#include <trx/core/ui/Layer.hpp>

/* Standard Headers */
#include <memory>

namespace trx
{

class LayerEventData : public EventData
{
public:
    LayerEventData(Layer* layer, const std::string& layer_name = "")
        : EventData(), m_layer(layer), m_layerName(layer_name)
    {
    }

    Layer* GetLayer() inline const
    {
        return m_layer;
    }

    const std::string& GetLayerName() const
    {
        return m_layerName;
    }

private:
    Layer* m_layer;

    std::string m_layerName;
};

};