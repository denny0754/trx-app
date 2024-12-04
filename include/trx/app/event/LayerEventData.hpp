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

/**
 * 
 * Implementation of the event data for events
 * of type `trx::LayerEvent`.
 * 
 **/
class LayerEventData : public EventData
{
public:
    /**
     * 
     * Initializes the data of the event.
     * 
     * @param layer The layer to be managed by the event.
     *              If the layer is not needed, set it as `nullptr`.
     * 
     * @param layer_name The name of the layer to be managed by the event.
     *                   By default, the name of the layer is set as an empty string.
     *                   Not all events require solely the name of the event.
     * 
     **/
    LayerEventData(Layer* layer, const std::string& layer_name = "")
        : EventData(), m_layer(layer), m_layerName(layer_name)
    {
    }

    /**
     * 
     * Returns the raw pointer to the Layer.
     * 
     * @return A pointer to the layer.
     * 
     * @warning
     * The lifetime of the layer should be managed by the user.
     * Currently it is not managed by a smart pointer, but it may
     * be a possibility in the future.
     * 
     **/
    Layer* GetLayer() inline const
    {
        return m_layer;
    }

    /**
     * 
     * Returns the name of the layer.
     * 
     * @return The name of the layer.
     * 
     **/
    const std::string& GetLayerName() const
    {
        return m_layerName;
    }

private:
    /**
     * 
     * The actual layer to be managed by the event.
     * 
     * @warning currently it is a raw pointer and the lifetime of
     * it is not quite safe. In the future
     * this parameter's type may be changed to a smart pointer,
     * most probably an `std::shared_ptr` to allow the Owner of the object
     * to change it whenever needed and to avoid being popped out.
     * 
     **/
    Layer* m_layer;

    /**
     * 
     * The name of the Layer to be managed on the event.
     * 
     * @note
     * Currently, this parameter is used when events
     * only need the name of the event.
     * 
     * Example: Popping layers only requires the name of the layer.
     * 
     **/
    std::string m_layerName;
};

};