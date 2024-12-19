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

/* Project Header */
#include <trx/intf/Framework.hpp>

/* Standard Headers */
#include <string>
#include <memory>

namespace trx::net
{

enum class SessionType
{
    REMOTE_SESSION,
    LOCAL_SESSION
};

class SessionFw : public intf::Framework
{
public:
    /**
     * 
     * Initializes the Remote or Local Session.
     * 
     * @param stype The type of connection to be enstablished. See `SessionType` for more details.
     * 
     * @param conn_string The connection string used to initialize the connection to the Backend.
     *                    If `stype` is set to `LOCAL`, this needs to be set to the local database file.
     *                    If `stype` is set to `REMOTE`, this needs to be formatted and set to the following string:
     *                    `{API_URL};{USERNAME};{API_KEY|PASSWORD}`
     * 
     **/
    SessionFw(SessionType stype, const std::string& address, const std::string& user, const std::string& pwd);

    void Initialize() override;

    void Update() override;

    void Shutdown() override;

    void Restart() override;

protected:
    void InitializeRemoteSession();

    void InitializeLocalSession();

private:
    SessionType m_sessionType;

    std::string m_srvAddress;
    std::string m_srvUser;
    std::string m_srvPass;
};

} // ns trx::net