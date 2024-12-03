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
#include <trx/core/event/EventKey.hpp>

/* Standard Headers */
#include <cstdint>

namespace trx
{

class Event
{
public:
    Event(EventData* event_data, EventKey event_key)
		: m_eventData(event_data), m_eventKey(event_key)
	{

	}

    inline EventData* GetEventData()
	{
		return m_eventData;
	}

    inline const EventKey GetEventKey() const
	{
		return m_eventKey;
	}

	template<typename Type>
	inline const Type* ToType() const
	{
		return static_cast<const Type*>(this);
	}

protected:
    EventData* m_eventData;

    EventKey m_eventKey;
};

} // ns trx