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
#include <trx/utils/config/ConfigSection.hpp>

namespace trx
{

class Config
{
public:
    using ConfigSectionMap = std::unordered_map<std::string, ConfigSection>;
    using iterator = ConfigSectionMap::iterator;
    using const_iterator = ConfigSectionMap::const_iterator;

public:
    Config() = default;

    Config(std::initializer_list<ConfigSection> sections);

	bool exist(const std::string& section_key);

	/**
	 * 
	 * This method returns a section with the given key
	 * and, if not found, the fallback section is returned.
	 * 
	 **/
	ConfigSection& get(std::string key, const ConfigSection& fallback_section);

    ConfigSection& at(const std::string& section_key);

    iterator find(const std::string& section_key);

	iterator begin();

	iterator begin(size_t i);

	const_iterator begin() const;

	iterator end();

	const_iterator end() const;

	const_iterator cbegin() const;

	const_iterator cend() const;

    ConfigSection& operator[](const std::string& section_key);

private:
    ConfigSectionMap m_sections;
};

} // ns trx