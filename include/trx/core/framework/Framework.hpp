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

namespace trx
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
		: m_isReady(false)
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
};

} // ns trx