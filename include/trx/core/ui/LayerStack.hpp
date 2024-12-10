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
#include <trx/app/event/LayerEvent.hpp>

/* Standard Headers */
#include <unordered_map>
#include <vector>
#include <queue>

namespace trx
{

class LayerStack
{
public:
	/**
	 * 
	 * Initializes the Layer Stack instance:
	 * 
	 **/
    LayerStack();

	/**
	 * 
	 * Pushes an Overlay to the Layer Stack.
	 * The Overlay is pushed on the front of the Stack.
	 * 
	 * @param layer A shared pointer to the Overlay.
	 * 
	 * @note
	 * 
	 * When pushing multiple overlays, the order of call is the order
	 * in the storage.
	 * 
	 * Example: given two Overlays `OverlayA` and `OverlayB`.
	 * 
	 * Pushing `OverlayA` first and `OverlayB` second will result in the following:
	 * 
	 * 	- Overlay at index `0`: `OverlayA`
	 * 
	 * 	- Overly  at index `1`: `OverlayB`
	 * 
	 * Thus, `OverlayA` will always be the first to be drawn and updated.
	 * 
	 **/
	void PushOverlay(std::shared_ptr<Layer> layer);

	/**
	 * 
	 * Pushes a Layer to the Layer Stack.
	 * 
	 * @param layer A shared pointer to the Layer.
	 * 
	 **/
    void PushLayer(std::shared_ptr<Layer> layer);

	/**
	 *
	 * Pushes a Layer to the Layer Stack on the next frame.
	 *
	 * @param layer A shared pointer to the Layer.
	 *
	 **/
	void PushLayerDeferred(std::shared_ptr<Layer> layer);

	void PushOverlayDeferred(std::shared_ptr<Layer> overlay);

	/**
	 * 
	 * Pops an overlay given its name.
	 * If the overlay does not exists, nothing is done.
	 * 
	 * @param overlay_name The name of the overlay to be popped.
	 * 
	 * @warning
	 * 
	 * Currently, if the Overlay exists, it is popped/erased from
	 * the Layer Stack, though the `Shutdown` method will not be called.
	 * The smart pointer storing the raw pointer to the Overlay
	 * should take care of it automatically, because the destructor of the Layer
	 * base class actually calls the `Shutdown` method.
	 * This has been verified, but if the user still has the raw pointer to the layer,
	 * it could be problematic.
	 * 
	 **/
	void PopOverlay(const std::string& overlay_name);

	/**
	 * 
	 * Pops an layer given its name.
	 * If the layer does not exists, nothing is done.
	 * 
	 * @param layer_name The name of the layer to be popped.
	 * 
	 * @warning
	 * 
	 * Please, see warning on `PopOverlay` method.
	 * 
	 **/
    void PopLayer(const std::string& layer_name);

	void PopLayerDeferred(const std::string& layer_name);

	void PopOverlayDeferred(const std::string& overlay_name);

	/**
	 * 
	 * Calls the Update method of all Overlays and Layers.
	 * 
	 **/
    void Update(double frame_time);

	/**
	 * 
	 * Calls the Render method of all Overlays and Layers.
	 * 
	 **/
    void Render();

	/**
	 * 
	 * The Shutdown method will call the `Layer::Shutdown` method for all 
	 * overlays and layers currently in stack.
	 * 
	 **/
    void Shutdown();

protected:
	/**
	 * 
	 * This method is used as a listener for Layer
	 * events.
	 * 
	 * @param event The event to be managed.
	 * 
	 * @warning
	 * 
	 * Do not call this method! Its use is purely as a listener and
	 * it's registered on initialization to the Middelware.
	 * 
	 **/
	void OnLayerEvent(Event* event);

	/**
	 * 
	 * Utility method used to find the layer/overlay given
	 * its name.
	 * 
	 * @param layer_name The name of the layer to be searched.
	 * 
	 * @return The iterator pointer to the layer. Returns `end()` if not found.
	 * 
	 **/
	std::vector<std::shared_ptr<Layer>>::iterator FindLayer(const std::string& layer_name);

	void EmptyDeferredQueue();

private:
	/**
	 * 
	 * Holds all Layers as well as all Overlays.
	 * The key difference between the two is that
	 * the Overlay, when pushed, is placed at the front
	 * of the vector. See `m_layerOverlayIndex` for reference.
	 * Normal layers, are pushed to the back of the vector.
	 * 
	 **/
	std::vector<std::shared_ptr<Layer>> m_layers;

	/**
	 * 
	 * This member variables holds the index of the last
	 * pushed overlay.
	 * This index is required because overlays
	 * must be updated and rendered before any actual layer.
	 * The following variable is used to push from the front of the vector.
	 * 
	 **/
	size_t m_layerOverlayIndex;

	std::queue<std::shared_ptr<Layer>> m_deferredLayersPush;

	std::queue<std::shared_ptr<Layer>> m_deferredOverlaysPush;

	std::queue<std::string> m_deferredLayersPop;

	std::queue<std::string> m_deferredOverlaysPop;
};

} // ns trx