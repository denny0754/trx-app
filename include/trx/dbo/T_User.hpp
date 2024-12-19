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
#include <trx/dbo/AbstractTable.hpp>

/* External Headers */
#include <Wt/Dbo/Dbo.h>

/* Standard Headers */
#include <string>

namespace trx::dbo
{

class T_User : public AbstractTable
{
public:
	template <class Action>
	void persist(Action& action)
	{
		Wt::Dbo::field(action, m_username, "username");
		Wt::Dbo::field(action, m_firstName, "first_name");
		Wt::Dbo::field(action, m_lastName, "last_name");
		Wt::Dbo::field(action, m_createdOn, "created_on");
		Wt::Dbo::field(action, m_changedOn, "changed_on");
		Wt::Dbo::field(action, m_lastLoggedOn, "last_logged_on");
	}

private:
	std::string m_username;
	
	std::string m_firstName;
	
	std::string m_lastName;

	std::time_t m_createdOn;
	
	std::time_t m_changedOn;

	std::time_t m_lastLoggedOn;
};

} // ns trx::dbo