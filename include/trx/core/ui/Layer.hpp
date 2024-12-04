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

/**
 * 
 * This class defines the a base for the implementation
 * of a custom layer.
 * All virtual methods are called automatically by the `trx::LayerStack`.
 * 
 **/
class Layer
{
public:	
	/**
	 * 
	 * Constructs the layer with a layer name.
	 * 
	 * @param layer_name : std::string The name of the layer
	 * 
	 **/
	Layer(const std::string& layer_name);

	/**
	 * 
	 * Initializes the Layer.
	 * 
	 **/
    virtual void OnInitialize() { };

	/**
	 * 
	 * Renders the layer.
	 * 
	 **/
    virtual void OnRender() { };

	/**
	 * 
	 * Updates the layer
	 * 
	 * @param delta : double The delta time from the last frame.
	 * 
	 **/
    virtual void OnUpdate(double delta) { };

	/**
	 * 
	 * Shutsdown/destroys the layer.
	 * 
	 **/
    virtual void OnShutdown() { };

	/**
	 * 
	 * Returns the name of the Layer.
	 * 
	 * @return The name of the layer.
	 * 
	 **/
	const std::string& GetLayerName() const;

	/**
	 * 
	 * Desctructor of Layer.
	 * Just calls the `OnShutdown` method, which
	 * should be overridden by the derived class to
	 * de-initialize its specific components.
	 * 
	 **/
	~Layer()
	{
		OnShutdown();
	}

protected:
	std::string m_layerName;
};

} // ns trx