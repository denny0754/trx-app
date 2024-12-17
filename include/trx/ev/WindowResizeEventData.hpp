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
#include <trx/ev/EventData.hpp>

namespace trx::ev
{

/**
 * 
 * Defines the data of the Window Size for
 * the WindowResizeEvent.
 * 
 **/
class WindowResizeEventData : public EventData
{
public:
	/**
	 * 
	 * Initializes the new window Width and Height.
	 * 
	 * @param width The new width of the Window.
	 * 
	 * @param height The new height of the Window.
	 * 
	 **/
    inline WindowResizeEventData(int width, int height)
		: EventData(), m_winWidth(width), m_winHeight(height)
	{

	}

	/**
	 * 
	 * Returns the width of the Window.
	 * 
	 * @return The width of the Window.
	 * 
	 **/
    inline int GetWidth() const
	{
		return m_winWidth;
	}

	/**
	 * 
	 * Returns the height of the Window.
	 * 
	 * @return The height of the Window.
	 * 
	 **/
    inline int GetHeight() const
	{
		return m_winHeight;
	}

private:
	/**
	 * 
	 * The new width of the Window.
	 * 
	 **/
    int m_winWidth;

	/**
	 * 
	 * The new height of the Window.
	 * 
	 **/
    int m_winHeight;
};

} // ns::ev