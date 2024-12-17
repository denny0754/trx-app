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

/* Standard Headers */
#include <string>

namespace trx::intf
{

class Framework
{
public:
	/**
	 * 
	 * Default constructor.
	 * Initializes the base framework.
	 * 
	 **/
	Framework()
		: m_isReady(false), m_isDetached(false), m_registerOnce(false), m_fwId(std::string(""))
	{

	}
	
	/**
	 * 
	 * Pure virtual method.
	 * Called on Application framework's initialization.
	 * 
	 **/
	virtual void Initialize() = 0;

	/**
	 * 
	 * Pure virtual method.
	 * Called on Application framework's update.
	 * 
	 **/
	virtual void Update() = 0;

	/**
	 * 
	 * Pure virtual method.
	 * Called on Application framework's shutdown.
	 * 
	 **/
	virtual void Shutdown() = 0;

	/**
	 * 
	 * Virtual method.
	 * Used to restart the framework.
	 * Not mandatory to be overridden.
	 * It is recommended to be overridden if the derived Framework
	 * support restarting.
	 * 
	 **/
	virtual void Restart() { };

	/**
	 * 
	 * Returns the readiness of the Framework.
	 * 
	 * @return True if the Framework has been initialized and ready to
	 * 		   be used. False otherwise.
	 **/
	inline bool IsReady() const
	{
		return m_isReady;
	}

	/**
	 * 
	 * Returns true if the Framework should be
	 * executing in detached mode(dedicated thread) or
	 * not(Main thread).
	 * 
	 * @return True if the Framework runs on detached mode(dedicated Thread)
	 * 		   or not(Main thread).
	 * 
	 **/
	inline bool IsDetached() const
	{
		return m_isDetached;
	}

	inline bool ShouldRegisterOnce() const
	{
		return m_registerOnce;
	}

	inline const std::string& GetFwID() const
	{
		return m_fwId;
	}

	template<typename Type>
	inline Type ToType()
	{
		return static_cast<Type>(this);
	}

protected:
	/**
	 * 
	 * Member variable used to flag the framework
	 * as being ready to be used or not.
	 * 
	 * This flag should be used as follow:
	 * 
	 * 	* False: if the framework initialization process has failed.
	 * 
	 *	* True: if the framework initialization process has finished succesfuly.
	 * 
	 **/
	bool m_isReady;

	/**
	 * 
	 * Member variable used to flag the framework
	 * as running in detached mode.
	 * 
	 * This flag tells the application the two way of exeuction:
	 * 
	 * 	* False: The framework is updated on the Main thread.
	 * 
	 * 	* True: The framework run on a separate thread.
	 * 
	 **/
	bool m_isDetached;

	/**
	 *
	 * Member variable used to flag the framework
	 * as being able to be registered once or multiple times.
	 *
	 * This flag tells the application the number of times the derived
	 * framework could be registered.
	 *
	 * 	* False: The framework can be registered multiple times.
	 *
	 * 	* True: The framework will be registered once. Other tentative of registering
	 *			the same framework will not succeed.
	 *
	 **/
	bool m_registerOnce;

	/**
	* 
	* Member variable used to identify the name or
	* ID of the Framework.
	* Note: The ID of the Framework can be used to access
	* the reference of the Framework itself when it has been registered
	* on the Application and, for some reason, you do not have
	* access to it anymore.
	* 
	* Attention: This member MUST be initialized and set before pushing
	* the framework to the Application.
	* 
	**/
	std::string m_fwId;
};

} // ns trx::intf