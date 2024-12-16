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
#include <trx/rsrc/RTResource.hpp>

/* Standard Headers */
#include <memory>
#include <string>
#include <unordered_map>
#include <mutex>

namespace trx::rsrc
{

class RTResourceManagerFw : public intf::Framework
{
public:
	RTResourceManagerFw();

    void Initialize() override;

	void Update() override;

    void Shutdown() override;

	void Restart() override;

    void PushResource(const std::string& rsrc_key, std::shared_ptr<RTResource> rsrc);

    void PushResource(const std::string& rsrc_key, RTResource* rsrc);

    std::shared_ptr<RTResource> GetResource(const std::string& rsrc_key);

    void PopResource(const std::string& rsrc_key);

private:
    using RTResourceMap = std::unordered_map<std::string, std::shared_ptr<RTResource>>;

    RTResourceMap m_resources;

    std::mutex m_mtMutex;
};

} // ns trx::rsrc