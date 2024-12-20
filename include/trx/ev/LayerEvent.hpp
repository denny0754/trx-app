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
#include <trx/ev/Event.hpp>
#include <trx/ev/LayerEventData.hpp>

namespace trx::ev
{

/**
 * 
 * Layer Event is a specific event
 * for the Layer and Layer Stack classes.
 * 
 **/
class LayerEvent : public Event
{
public:
	/**
	 * 
	 * Initializes the LayerEvent class.
	 * 
	 * @param layer_data The data of the Layer.
	 * 
	 * @param layer_event_type The type of layer event.
	 * 
	 **/
    LayerEvent(LayerEventData* layer_data, EventKey layer_event_type)
        : Event(layer_data, layer_event_type)
    {

    }
};

} // ns trx::ev