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
#include <trx/util/logging/LogSettings.hpp>

/* External Headers */
#include <spdlog/spdlog.h>
#include <spdlog/common.h>
#include <nlohmann/json.hpp>

/* Standard Headers */
#include <unordered_map>

namespace trx::util
{

class LogManager
{
public:
    /**
     * 
     * Initializes on the first call and returns the instance of the class.
     * 
     * @return Instance of this class.
     * 
     **/
    static LogManager& Get();

    /**
     * 
     * Initializes this class and sets up a default logger which can be used
     * in case specific ones are not needed.
     * 
     **/
    void Initialize();

    /**
     * 
     * Shutsdown the instance of the Log Manager.
     * 
     **/
    void Shutdown();

    /**
     * 
     * Registers a new Logger.
     * 
     * @param log_settings : LogSettings The settings of the new logger to be registered.
     * 
     **/
    void RegisterLogger(const LogSettings& log_settings);

    /**
     *
     * Unregisteres an existing logger. Nothing is done if the
     * logger is with the given key name is not found.
     * 
     * @param name : std::string The name of the Logger that was previously regsistered.
     * 
     **/
    void UnregisterLogger(const std::string& name);

    /**
     * 
     * Returns a reference of the logger with the given name.
     * 
     * @param name : std::string The name of the Logger to be returned.
     * 
     * @return A reference to the logger. If the Logger with the given key does not exists
     *         the default one(name="DEFAULT") will be returned.
     **/
    spdlog::logger& GetLogger(const std::string& name);

    /**
     * 
     * Returns the default logger.
     * 
     * @return The default logger.
     **/
    spdlog::logger& GetDefaultLogger();

private:
    /**
     * 
     * Map of registered loggers
     * 
     **/
    std::unordered_map<std::string, std::unique_ptr<spdlog::logger>> m_loggers;
};

} // ns trx::util

#define TRX_GET_LOGGER(logger_name) trx::util::LogManager::Get().GetLogger(logger_name)
#define TRX_REG_LOGGER(log_settings) trx::util::LogManager::Get().RegisterLogger(log_settings)
#define TRX_UNR_LOGGER(log_settings) trx::util::LogManager::Get().UnregisterLogger(log_settings)

#define TRX_CREATE_LOGGER(logger_name, enable_console, enable_file, file, min_level) \
{\
    LogSettings log_settings = LogSettings();\
    log_settings.EnableConsole = enable_console; \
    log_settings.EnableFile = enable_file;\
    log_settings.MinLevel = min_level;\
    log_settings.OutFilePath = file;\
    log_settings.Name = logger_name;\
    TRX_REG_LOGGER(log_settings);\
}

#define TRX_CRT(logger_name, message, ...) trx::util::LogManager::Get().GetLogger(logger_name).critical(message, __VA_ARGS__)
#define TRX_ERR(logger_name, message, ...) trx::util::LogManager::Get().GetLogger(logger_name).error(message, __VA_ARGS__)
#define TRX_WRN(logger_name, message, ...) trx::util::LogManager::Get().GetLogger(logger_name).warn(message, __VA_ARGS__)
#define TRX_INF(logger_name, message, ...) trx::util::LogManager::Get().GetLogger(logger_name).info(message, __VA_ARGS__)
#define TRX_DBG(logger_name, message, ...) trx::util::LogManager::Get().GetLogger(logger_name).debug(message, __VA_ARGS__)
#define TRX_TRC(logger_name, message, ...) trx::util::LogManager::Get().GetLogger(logger_name).trace(message, __VA_ARGS__)

/* Specialized Json Serializer for Enum: spdlog::level::level_enum */
namespace spdlog::level
{
NLOHMANN_JSON_SERIALIZE_ENUM(spdlog::level::level_enum, {
    {spdlog::level::level_enum::off, nullptr},
    {spdlog::level::level_enum::off, ""},
    {spdlog::level::level_enum::off, "6"},
    {spdlog::level::level_enum::off, nullptr},

    {spdlog::level::level_enum::trace, "trace"},
    {spdlog::level::level_enum::trace, "t"},
    {spdlog::level::level_enum::trace, "0"},

    {spdlog::level::level_enum::debug, "debug"},
    {spdlog::level::level_enum::debug, "d"},
    {spdlog::level::level_enum::debug, "1"},

    {spdlog::level::level_enum::info, "info"},
    {spdlog::level::level_enum::info, "i"},
    {spdlog::level::level_enum::info, "2"},

    {spdlog::level::level_enum::warn, "warn"},
    {spdlog::level::level_enum::warn, "w"},
    {spdlog::level::level_enum::warn, "3"},

    {spdlog::level::level_enum::err, "error"},
    {spdlog::level::level_enum::err, "e"},
    {spdlog::level::level_enum::err, "4"},

    {spdlog::level::level_enum::critical, "critical"},
    {spdlog::level::level_enum::critical, "c"},
    {spdlog::level::level_enum::critical, "5"}
});
} // ns spdlog::level