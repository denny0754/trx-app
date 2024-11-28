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
#include <trx/utils/config/ConfigEntry.hpp>

/* Standard Headers */
#include <unordered_map>

namespace trx
{

class ConfigSection
{
public:
    using ConfigEntryMap = std::unordered_map<std::string, ConfigEntry>;
    using iterator = ConfigEntryMap::iterator;
    using const_iterator = ConfigEntryMap::const_iterator;

public:
    ConfigSection() = default;

    ConfigSection(const std::string& section_key, std::initializer_list<ConfigEntry> entries = { });

    ConfigEntry& At(const std::string& entry_key);

    iterator Find(const std::string& entry_key);

    ConfigEntry& operator[](const std::string& entry_key);

private:
    ConfigEntryMap m_entries;
};

} // ns trx