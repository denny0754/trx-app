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
#include <trx/core/event/Event.hpp>
#include <trx/app/event/WindowResizeEventData.hpp>

namespace trx
{

/**
 * 
 * Defines an event used when the size of
 * the main window has been changed.
 * 
 **/
class WindowResizeEvent : public Event
{
public:
	/**
	 * 
	 * Initializes the event with the new window size data.
	 * 
	 * @param new_window_size The data storing the new size of the window.
	 * 
	 **/
    inline WindowResizeEvent(WindowResizeEventData* new_window_size)
		: Event(new_window_size, EventKey::WINDOW_RESIZE_EVENT)
	{

	}
    
};

} // ns