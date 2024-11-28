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

/* External Headers */
#include <spdlog/logger.h>

/* Standard Headers */
#include <string>
#include <filesystem>

namespace trx
{

struct LogSettings
{
    /**
     * 
     * The name of the logger as well as the
     * key to access it when registering under LogManager.
     * 
     **/
    std::string Name;

    /**
     * 
     * Enables or disables logging to console.
     * 
     */
    bool EnableConsole;

    /**
     * 
     * Enables or disables logging to file.
     * If enabled, `OutFilePath` must be set to a valid path.
     * 
     **/
    bool EnableFile;

    /**
     * 
     * The output directory and file for the logger.
     * This is used only if flag `EnableFile` is enabled.
     * 
     **/
    std::filesystem::path OutFilePath;

    /**
     * 
     * The minimum level of the logs.
     * 
     **/
    spdlog::level::level_enum MinLevel;

    /**
     * 
     * The pattern of log's messages.
     * 
     **/
    std::string LogPattern = "[%Y-%m-%d %H:%M:%S] %n - %^%l%$: %v";
};

} // ns trx