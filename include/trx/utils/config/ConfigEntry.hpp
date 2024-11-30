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

namespace trx
{

class ConfigEntry
{
public:
    ConfigEntry() = default;

    ConfigEntry(const std::string& key, const std::string& value);

    ConfigEntry(const ConfigEntry& entry);

    ConfigEntry(ConfigEntry&& entry);

    void SetKey(const std::string& key);

    const std::string& GetKey() const;

    void SetValue(const std::string& value);

    const std::string& GetValue() const;

    ConfigEntry& operator=(ConfigEntry& entry);

    ConfigEntry& operator=(ConfigEntry entry);

    bool operator==(ConfigEntry& entry);

    bool operator!=(ConfigEntry& entry);

    operator int();

    operator unsigned int();

    operator float();

    operator double();

    operator bool();

private:
    /**
     * 
     * The key of the entry.
     * 
     **/
    std::string m_key;

    /**
     * 
     * The value of the entry.
     * 
     **/
    std::string m_value;
};

} // ns trx