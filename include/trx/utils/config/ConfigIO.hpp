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
#include <trx/utils/config/Config.hpp>
#include <trx/utils/config/ConfigWriter.hpp>

/* Standard Headers */
#include <filesystem>

namespace trx
{

class ConfigIO
{
public:
	static bool IsEntry(const std::string& buf);

	static bool IsSection(const std::string& buf);

	static bool IsComment(const std::string& buf);

	static ConfigEntry ParseEntry(const std::string& entry_str);

    static Config ParseFile(const std::filesystem::path& file);

	static Config ParseString(const std::string& buf);

	static std::string ConvertToString(const Config& config);

    static void WriteFile(const Config& config, const std::filesystem::path& file);
};

} // ns trx