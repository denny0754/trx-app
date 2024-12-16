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
#include <trx/rsrc/RTResource.hpp>

/* External Headers */
#include <nlohmann/json.hpp>

/* Standard Headers */
#include <filesystem>

namespace trx::rsrc
{

class RTAppConfig : public RTResource
{
public:
    void Initialize() override;

	void Load(const std::filesystem::path& file_path);

	void Load(const std::string& json_data);

	void LoadOrDefault(const std::filesystem::path& file_path, const std::string& json_data);

	void Reload();

	void Save();

    void Destroy() override;

    nlohmann::json& GetConfig();

private:
    nlohmann::json m_appConfig;

	std::filesystem::path m_configPath;
	std::filesystem::path m_configFile;
};

} // ns trx::rsrc