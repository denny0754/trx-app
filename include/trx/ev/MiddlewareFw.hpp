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
#include <trx/intf/Framework.hpp>
#include <trx/ev/Event.hpp>

/* Standard Headers */
#include <functional>
#include <unordered_map>
#include <vector>
#include <queue>
#include <memory>

namespace trx::ev
{

class MiddlewareFw : public intf::Framework
{
public:
	using EventListenerRef = std::function<void(Event*)>;


public:
	MiddlewareFw();

	void Initialize() override;

	void Update() override;

	void Shutdown() override;

	void Restart();

	void Subscribe(EventKey event_key, EventListenerRef listener);

	void Unsubscribe(const EventListenerRef& listener);

	void Unsubscribe(EventKey event_key, const EventListenerRef& listener);

	void PushEvent(Event* event);

	void QueueEvent(std::unique_ptr<Event> event);

private:
	std::unordered_map<EventKey, std::vector<EventListenerRef>> m_subscribers;

	std::queue<std::unique_ptr<Event>> m_eventQueue;
};

} // ns trx::ev