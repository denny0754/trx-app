/* Project Headers */
#include <trx/ui/LayerStack.hpp>
#include <trx/ev/MiddlewareFw.hpp>
#include <trx/util/logging/LogManager.hpp>
#include <trx/Application.hpp>

namespace trx::ui
{

LayerStack::LayerStack()
{
    m_layerOverlayIndex = 0;

    TRX_TRC("APP", "Layer Stack is being initialized...");

    auto mw_fw = Application::Get().GetFw("_APP_MIDDLEWARE")->ToType<ev::MiddlewareFw*>();

    mw_fw->Subscribe(
        ev::EventKey::PUSH_LAYER_EVENT,
        std::bind(&LayerStack::OnLayerEvent, this, std::placeholders::_1)
    );

    mw_fw->Subscribe(
        ev::EventKey::PUSH_LAYER_DEFERRED,
        std::bind(&LayerStack::OnLayerEvent, this, std::placeholders::_1)
    );

    mw_fw->Subscribe(
        ev::EventKey::POP_LAYER_EVENT,
        std::bind(&LayerStack::OnLayerEvent, this, std::placeholders::_1)
    );

    mw_fw->Subscribe(
        ev::EventKey::POP_LAYER_DEFERRED,
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

void LayerStack::PushLayerDeferred(std::shared_ptr<Layer> layer)
{
    m_deferredLayersPush.push(layer);
}

void LayerStack::PushOverlayDeferred(std::shared_ptr<Layer> overlay)
{
    m_deferredOverlaysPush.push(overlay);
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

void LayerStack::PopLayerDeferred(const std::string& layer_name)
{
    m_deferredLayersPop.push(layer_name);
}

void LayerStack::PopOverlayDeferred(const std::string& overlay_name)
{
    m_deferredLayersPop.push(overlay_name);
}

void LayerStack::Update(double frame_time)
{
    EmptyDeferredQueue();

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

    auto mw_fw = Application::Get().GetFw("_APP_MIDDLEWARE")->ToType<ev::MiddlewareFw*>();
    mw_fw->Unsubscribe(std::bind(&LayerStack::OnLayerEvent, this, std::placeholders::_1));
}

void LayerStack::OnLayerEvent(ev::Event* event)
{
    const ev::LayerEvent* layer_event = event->ToType<ev::LayerEvent>();

    const ev::LayerEventData* layer_event_data = event->GetEventData()->ToType<ev::LayerEventData>();

    if(layer_event->GetEventKey() == ev::EventKey::PUSH_LAYER_EVENT)
    {
        TRX_TRC("APP", "Fulfilling the request to push layer `{0}` to the Layer Stack...", layer_event_data->GetLayer()->GetLayerName());
        PushLayer(std::shared_ptr<Layer>(layer_event_data->GetLayer()));
    }
    else if (layer_event->GetEventKey() == ev::EventKey::POP_LAYER_EVENT)
    {
        TRX_TRC("APP", "Fulfilling the request to pop layer `{0}` from the Layer Stack...", layer_event_data->GetLayerName());
        PopLayer(layer_event_data->GetLayerName());
    }
    else if (layer_event->GetEventKey() == ev::EventKey::PUSH_LAYER_DEFERRED)
    {
        TRX_TRC("APP", "Fulfilling the request to push layer `{0}` to the Layer Stack in deferred mode...", layer_event_data->GetLayer()->GetLayerName());
        PushLayerDeferred(std::shared_ptr<Layer>(layer_event_data->GetLayer()));
    }
    else if (layer_event->GetEventKey() == ev::EventKey::POP_LAYER_DEFERRED)
    {
        TRX_TRC("APP", "Fulfilling the request to pop layer `{0}` from the Layer stack in deferred mode...", layer_event_data->GetLayerName());
        PopLayerDeferred(layer_event_data->GetLayerName());
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

void LayerStack::EmptyDeferredQueue()
{
    if(!m_deferredOverlaysPop.empty()) TRX_TRC("APP", "Popping {0} of deferred overlays...", m_deferredOverlaysPop.size());
    while (!m_deferredOverlaysPop.empty())
    {
        PopOverlay(m_deferredOverlaysPop.front());
        m_deferredOverlaysPop.pop();
    }

    if(!m_deferredLayersPop.empty()) TRX_TRC("APP", "Popping {0} of deferred layers...", m_deferredLayersPop.size());
    while (!m_deferredLayersPop.empty())
    {
        PopLayer(m_deferredLayersPop.front());
        m_deferredLayersPop.pop();
    }

    if(!m_deferredOverlaysPush.empty()) TRX_TRC("APP", "Pushing {0} of deferred overlays...", m_deferredOverlaysPush.size());
    while (!m_deferredOverlaysPush.empty())
    {
        PushOverlay(m_deferredOverlaysPush.front());
        m_deferredOverlaysPush.pop();
    }

    if(!m_deferredLayersPush.empty()) TRX_TRC("APP", "Pushing {0} of deferred layers...", m_deferredLayersPush.size());
    while (!m_deferredLayersPush.empty())
    {
        PushLayer(m_deferredLayersPush.front());
        m_deferredLayersPush.pop();
    }
}

} // ns trx::ui