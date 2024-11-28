/* Project Headers */
#include <trx/core/ui/LayerStack.hpp>

namespace trx
{

LayerStack::LayerStack()
{
    
}

void LayerStack::PushLayer(Layer* layer)
{
    if(m_layers.find(layer->GetLayerName()) != m_layers.end())
    {
        m_layers.at(layer->GetLayerName())->OnShutdown();
        m_layers.erase(layer->GetLayerName());
    }
    m_layers[layer->GetLayerName()] = layer;
}

void LayerStack::PopLayer(const std::string& layer_name)
{
    if(m_layers.find(layer_name) != m_layers.end())
    {
        m_layers.at(layer_name)->OnShutdown();
        m_layers.erase(layer_name);
    }
}

void LayerStack::Update(double frame_time)
{
    for(auto& [layer_name, layer] : m_layers)
    {
        layer->OnUpdate(frame_time);
    }
}

void LayerStack::Render()
{
    for(auto& [layer_name, layer] : m_layers)
    {
        layer->OnRender();
    }
}

void LayerStack::Shutdown()
{
    for(auto& [layer_name, layer] : m_layers)
    {
        layer->OnShutdown();
        delete layer;
    }
}

} // ns trx