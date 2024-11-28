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

/* Standard Headers */
#include <functional>
#include <unordered_map>
#include <string>
#include <vector>

namespace trx
{

class Middleware
{
public:
    using EventListener = std::function<void(Event*)>;
	using ListenerHandle = uint32_t;

public:
	/**
	 * 
	 * This method initializes the Middleware instance
	 * and returns it.
	 * 
	 * @return The unique instance of this class.
	 * 
	 **/
    static Middleware& Get();

	/**
	 * 
	 * Initializes the Middleware.
	 * 
	 **/
    void Initialize();

	/**
	 * 
	 * Registers an event listeners using the given event key.
	 * 
	 * @param event_key : EventKey The key of the event.
	 * 
	 * @param listener : EventListener The function or method that should be called when the event is triggered.
	 * 
	 * @return The listener handle, used to unregister the listener when needed.
	 * 
	 **/
    ListenerHandle RegisterListener(EventKey event_key, EventListener listener);

	/**
	 * 
	 * Unregisters the listener with the given event key and handle.
	 * Nothing is done if the event key and the handle do not exist.
	 * 
	 * @param event_key : EventKey The key of the event to be unregistered.
	 * 
	 * @param handle : ListenerHandle The handle of the event that was previously registered.
	 * 
	 **/
    void UnregisterListener(EventKey event_key, ListenerHandle handle);

	/**
	 * 
	 * Dispatches an event. The listener associated with the given
	 * event is called immediately.
	 * 
	 * @param event : Event* The event to be dispatched.
	 * 
	 **/
    void PushEvent(Event* event);

private:
	/**
	 * 
	 * Default constructor made private because this
	 * class is a singleton.
	 * 
	 **/
    Middleware() = default;

private:
	std::unordered_map<ListenerHandle, EventListener> m_listenersHandle;
	std::unordered_map<EventKey, std::vector<ListenerHandle>> m_listenerKeys;

	ListenerHandle m_currentHandle;
};

} // ns trx