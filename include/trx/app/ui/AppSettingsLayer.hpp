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
#include <trx/core/ui/Layer.hpp>

/* External Headers */
#include <spdlog/common.h>

namespace trx
{

class AppSettingsLayer : public Layer
{
public:
    AppSettingsLayer();

    void OnInitialize() override;

    void OnRender() override;

    void OnUpdate(double delta) override;

    void OnShutdown() override;

private:
	bool m_isWindowOpen;

	const char* m_logLevels[6] = { "Trace", "Debug", "Info", "Warning", "Error", "Critical" };

	const std::unordered_map<const char*, spdlog::level::level_enum> m_logLevelsChrMap = {
		{"Trace", spdlog::level::level_enum::trace},
		{"Debug", spdlog::level::level_enum::debug},
		{"Info", spdlog::level::level_enum::info},
		{"Warning", spdlog::level::level_enum::warn},
		{"Error", spdlog::level::level_enum::err},
		{"Critical", spdlog::level::level_enum::critical},
		{"Off", spdlog::level::level_enum::off}
	};

	struct SettingsData
	{
		/* Logging Settings */
		int* CurrentLogLevel;
		int* PreviousLogLevel;

		/* UI Components Control */
		bool ApplySettingsButton;
	};

	SettingsData m_settingsDataRef;
};

} // ns trx