/* Project Headers */
#include <trx/core/ui/LayerStack.hpp>

namespace trx
{

LayerStack::LayerStack()
{
    m_layers = {};
    m_layerOverlayIndex = 0;
}

void LayerStack::PushOverlay(Layer* overlay)
{
    auto overlay_it = std::find_if(
        m_layers.begin(),
        m_layers.end(),
        [overlay](Layer& _overlay) {
            return _overlay.GetLayerName() == overlay->GetLayerName();
        }
    );

    if(overlay_it != m_layers.end())
    {
        m_layerOverlayIndex--;
        m_layers.erase(overlay_it);
    }

    // Should it be called here?
    overlay->OnInitialize();

    m_layers.insert(
        m_layers.begin()+m_layerOverlayIndex,
        overlay
    );

    m_layerOverlayIndex++;
}

void LayerStack::PushLayer(Layer* layer)
{
    auto layer_it = std::find_if(
        m_layers.begin(),
        m_layers.end(),
        [layer](Layer& _layer) {
            return _layer.GetLayerName() == layer->GetLayerName();
        }
    );

    if(layer_it != m_layers.end())
    {
        m_layers.erase(layer_it);
    }

    // Should it be called here?
    layer->OnInitialize();

    m_layers.push_back(layer);
}

void LayerStack::PopOverlay(const std::string& overlay_name)
{
    auto overlay_it = std::find_if(
        m_layers.begin(),
        m_layers.end(),
        [overlay_name](Layer& _overlay) {
            return _overlay.GetLayerName() == overlay_name;
        }
    );

    if(overlay_it != m_layers.end())
    {
        m_layerOverlayIndex--;
        m_layers.erase(overlay_it);
    }
}

void LayerStack::PopLayer(const std::string& layer_name)
{
    auto layer_it = std::find_if(
        m_layers.begin(),
        m_layers.end(),
        [layer_name](Layer& _layer) {
            return _layer.GetLayerName() == layer_name;
        }
    );

    if(layer_it != m_layers.end())
    {
        m_layers.erase(layer_it);
    }
}

void LayerStack::Update(double frame_time)
{
    for(auto layer : m_layers)
    {
        layer->OnUpdate(frame_time);
    }
}

void LayerStack::Render()
{
    for(auto layer : m_layers)
    {
        layer->OnRender();
    }
}

void LayerStack::Shutdown()
{
    for(auto layer : m_layers)
    {
        layer->OnShutdown();
    }
}

} // ns trx