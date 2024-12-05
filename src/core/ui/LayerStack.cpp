/* Project Headers */
#include <trx/core/ui/LayerStack.hpp>
#include <trx/core/Middleware.hpp>
#include <trx/utils/logging/LogManager.hpp>

namespace trx
{

LayerStack::LayerStack()
{
    m_layerOverlayIndex = 0;

    TRX_TRC("APP", "Layer Stack is being initialized...");

    Middleware::Get().RegisterListener(
        EventKey::PUSH_LAYER_EVENT,
        std::bind(&LayerStack::OnLayerEvent, this, std::placeholders::_1)
    );

    Middleware::Get().RegisterListener(
        EventKey::POP_LAYER_EVENT,
        std::bind(&LayerStack::OnLayerEvent, this, std::placeholders::_1)
    );
}

void LayerStack::PushOverlay(std::shared_ptr<Layer> overlay)
{
    const std::string overlay_name = overlay->GetLayerName();

    TRX_TRC("APP", "Pushing overlay `{0}` to the Layer Stack.", overlay_name);

    auto overlay_it = FindLayer(overlay_name);

    if(overlay_it != m_layers.end())
    {
        TRX_TRC("APP", "Overlay `{0}` alrady exists. Erasing it...", overlay_name);
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

    TRX_TRC("APP", "Overlay `{0}` has been initialized and succesfully pushed to the Layer Stack. Stack Pointer(Overlay) at: `{1}`", overlay_name, m_layerOverlayIndex);
}

void LayerStack::PushLayer(std::shared_ptr<Layer> layer)
{    
    const std::string& layer_name = layer->GetLayerName();

    TRX_TRC("APP", "Pushing layer `{0}` to the Layer Stack.", layer_name);
 
    auto layer_it = FindLayer(layer_name);

    if(layer_it != m_layers.end())
    {
        TRX_TRC("APP", "Layer `{0}` alrady exists. Erasing it...", layer_name);
        (*layer_it)->OnShutdown();
        m_layers.erase(layer_it);
    }

    // Should it be called here?
    layer->OnInitialize();

    m_layers.push_back(layer);

    TRX_TRC("APP", "Layer `{0}` has been initialized and succesfully pushed to the Layer Stack. Size of Layer Stack: {1}", layer_name, m_layers.size());
}

void LayerStack::PopOverlay(const std::string& overlay_name)
{
    auto overlay_it = FindLayer(overlay_name);

    if(overlay_it != m_layers.end())
    {
        m_layerOverlayIndex--;
        m_layers.erase(overlay_it);
        TRX_TRC("APP", "Overlay `{0}` has been found and removed from the Layer Stack. Layer Stack Pointer(Overlay) at {1}.", overlay_name, m_layerOverlayIndex);
    }
    else
    {
        TRX_TRC("APP", "Overlay `{0}` could not be found.", overlay_name);
    }
}

void LayerStack::PopLayer(const std::string& layer_name)
{
    auto layer_it = FindLayer(layer_name);

    if(layer_it != m_layers.end())
    {
        m_layers.erase(layer_it);
        TRX_TRC("APP", "Layer `{0}` has been found and removed from the Layer Stack. Size of Layer Stack: {1}", layer_name, m_layers.size());
    }
    else
    {
        TRX_TRC("APP", "Layer `{0}` could not be found.", layer_name);
    }
}

void LayerStack::Update(double frame_time)
{
    for(auto& layer : m_layers)
    {
        layer->OnUpdate(frame_time);
    }
}

void LayerStack::Render()
{
    for(auto& layer : m_layers)
    {
        layer->OnRender();
    }
}

void LayerStack::Shutdown()
{
    for(auto& layer : m_layers)
    {
        layer->OnShutdown();
    }
}

void LayerStack::OnLayerEvent(Event* event)
{
    const LayerEvent* layer_event = event->ToType<LayerEvent>();

    const LayerEventData* layer_event_data = event->GetEventData()->ToType<LayerEventData>();

    if(layer_event->GetEventKey() == EventKey::PUSH_LAYER_EVENT)
    {
        TRX_TRC("APP", "Fulfilling the request to push layer `{0}` to the Layer Stack...", layer_event_data->GetLayer()->GetLayerName());
        PushLayer(std::shared_ptr<Layer>(layer_event_data->GetLayer()));
    }
    else if (layer_event->GetEventKey() == EventKey::POP_LAYER_EVENT)
    {
        TRX_TRC("APP", "Fulfilling the request to pop layer `{0}` from the Layer Stack...", layer_event_data->GetLayerName());
        PopLayer(layer_event_data->GetLayerName());
    }
}

std::vector<std::shared_ptr<Layer>>::iterator LayerStack::FindLayer(const std::string& layer_name)
{
    auto layer_it = std::find_if(
        m_layers.begin(),
        m_layers.end(),
        [layer_name](std::shared_ptr<Layer>& _layer) {
            return _layer->GetLayerName() == layer_name;
        }
    );
    return layer_it;
}

} // ns trx