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

/* External Headers */
#include <boost/beast/http.hpp>

/* Standard Headers */
#include <string>

namespace trx::net
{

class RESTServerFw : public intf::Framework
{
public:
    RESTServerFw(const std::string& address, uint16_t port);

    void Initialize() override;

    void Update() override;

    void Shutdown() override;

    void Restart() override;

private:
    std::string m_address;

    uint16_t m_port;
};

} // ns trx::net