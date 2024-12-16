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
#include <trx/ev/EventKey.hpp>

/* Standard Headers */
#include <cstdint>

namespace trx::ev
{

/**
 * 
 * Class event is the base class for events.
 * We can use this class directly or derive this class
 * to create a specific event.
 * Although we can use directly this class when there is no
 * specifc event data defined, it is recommended to create
 * the derived event class anyway.
 * 
 * When deriving this class, it is mandatory to call
 * the constructor of the Event class to set the Event Data and
 * Event Key parameters.
 * 
 * Example implementation:
 * 
 * class WindowResizeEvent : public trx::Event
 * {
 * public:
 * 	WindowResizeEvent(WindowResizeEventData* data)
 * 		: Event(data, trx::EventKey::WINDWO_RESIZE_EVENT) { }
 * }
 * 
 * 
 **/
class Event
{
public:
	Event() = default;

	/**
	 * 
	 * Initializes the base class event with a pointer to the event
	 * data and the key of the Event.
	 * 
	 * @param event_data The data of the Event. See `trx::EventData` for reference.
	 * 
	 * @param event_key The key of the event. See `trx::EventKey` for reference.
	 * 
	 **/
    Event(EventData* event_data, EventKey event_key)
		: m_eventData(event_data), m_eventKey(event_key)
	{

	}

	/**
	 * 
	 * Returns the data managed by the event.
	 * 
	 * @return The data of the event.
	 * 
	 **/
    inline EventData* GetEventData()
	{
		return m_eventData;
	}

	/**
	 * 
	 * Returns the key of the event.
	 * 
	 * @return The key of the event.
	 * 
	 **/
    inline const EventKey GetEventKey() const
	{
		return m_eventKey;
	}

	/**
	 * 
	 * Templated function to cast the event
	 * to another derived event.
	 * 
	 * @param Type the derived event class.
	 * 
	 * @return The casted event.
	 * 
	 **/
	template<typename Type>
	inline const Type* ToType() const
	{
		return static_cast<const Type*>(this);
	}

protected:
	/**
	 * 
	 * The data of the Event.
	 * Currently managed as a raw pointer to write
	 * less code when creating a new Event.
	 * @warning The lifetime of the EventData is not currently managed
	 * by the Event, but should be managed by the pusher of the event.
	 * 
	 **/
    EventData* m_eventData;

	/**
	 * 
	 * The key of the event.
	 * See `trx::EventKey` for the values accepted.
	 * 
	 **/
    EventKey m_eventKey;
};

} // ns trx::ev