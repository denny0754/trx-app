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

class Layer
{
public:
	Layer(const std::string& layer_name);

    virtual void OnInitialize() { };

    virtual void OnRender() { };

    virtual void OnUpdate(double delta) { };

    virtual void OnShutdown() { };

	const std::string& GetLayerName() const;

protected:
	std::string m_layerName;
};

} // ns