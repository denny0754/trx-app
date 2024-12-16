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
#include <spdlog/common.h>

/* Standard Headers */
#include <string>
#include <filesystem>

namespace trx::util
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
     * By default, this is set to `true`.
     * 
     */
    bool EnableConsole = false;

    /**
     * 
     * Enables or disables logging to file.
     * If enabled, `OutFilePath` must be set to a valid path.
     * 
     * By default, this is set to `true`.
     * 
     **/
    bool EnableFile = true;

    /**
     * 
     * If enabled, the files created wil be rotating.
     * The number of rotating files should be set
     * using memeber variable `NrOfRotatingFiles`.
     * 
     * By default, this flag will be set to `true`.
     * 
     **/
    bool EnableRotatingFile = true;

    /**
     * 
     * Defines the number of rotating files.
     * Please, see `spdlog`'s rotating file for more
     * details about the functionality of it.
     * 
     **/
    unsigned int NrOfRotatingFiles = 7;

    /**
     * 
     * Defines the maximum size of a log file
     * after which a new file is created.
     * 
     * This is expressed in bytes.
     * 
     * By default, this is set to 50MB
     * 
     **/
    unsigned int MaxFileSize = 52428800U;

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
    spdlog::level::level_enum MinLevel = spdlog::level::level_enum::err;

    /**
     * 
     * The pattern of log's messages.
     * 
     **/
    std::string LogPattern = "[%Y-%m-%d %H:%M:%S] %n - %^%l%$: %v";
};

} // ns trx::util