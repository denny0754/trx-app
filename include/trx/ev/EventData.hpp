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

namespace trx::ev
{

/**
 * 
 * `EventData` is a pure base class, meaning
 * that it does not contain any data/member variables.
 * The actual data should be implemented in the derived
 * class. 
 * 
 **/
class EventData
{
public:
	/**
	 * 
	 * Constructor without parameters for the Event Data class.
	 * This is a purely base class, as the actual data, if needed
	 * should be implemented on the derived class.
	 * 
	 **/
    EventData() = default;

	/**
	 * 
	 * Converts the EventData class instance to
	 * the given Type.
	 * 
	 * @param Type The type of the derived class.
	 * 
	 * @return A cast to the derived class.
	 * 
	 * @warning
	 * 
	 * The `Type` parameter must hold a type that is derived
	 * from this class.
	 * 
	 * Passing an invalid type could throw an exception.
	 * 
	 **/
	template<typename Type>
	const Type* ToType() const
	{
		return static_cast<const Type*>(this);
	}
};

} // ns trx::ev