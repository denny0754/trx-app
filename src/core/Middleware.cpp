/* Project Headers */
#include <trx/core/Middleware.hpp>
#include <trx/utils/logging/LogManager.hpp>
#include <ios>

namespace trx
{

static Middleware* g_instance = nullptr;

Middleware& Middleware::Get()
{
    if(!g_instance)
    {
        g_instance = new Middleware();
    }
    return *g_instance;
}

void Middleware::Initialize()
{
    TRX_CREATE_LOGGER("Middleware", true, false, "", spdlog::level::level_enum::debug)

    TRX_GET_LOGGER("Middleware").info("Initializing Middleware...");
}

Middleware::ListenerHandle Middleware::RegisterListener(EventKey event_key, Middleware::EventListener listener)
{
    TRX_GET_LOGGER("Middleware").debug("Registering event listener with key {0:x}", (uint32_t)event_key);

    m_currentHandle++;

    m_listenerKeys[event_key].push_back(m_currentHandle);
    m_listenersHandle[m_currentHandle] = listener;

    return m_currentHandle;
}

void Middleware::UnregisterListener(EventKey event_key, ListenerHandle handle)
{
    if(m_listenerKeys.find(event_key) != m_listenerKeys.end())
    {
        const std::vector<ListenerHandle>& listener_handles = m_listenerKeys.at(event_key);
        for(auto listener_handle : listener_handles)
        {
            if(m_listenersHandle.find(handle) != m_listenersHandle.end() && listener_handle == handle)
            {
                m_listenersHandle.erase(handle);
                return;
            }
        }
    }    
}

void Middleware::PushEvent(Event* event)
{
    if(m_listenerKeys.find(event->GetEventKey()) != m_listenerKeys.end())
    {
        const std::vector<ListenerHandle>& handles = m_listenerKeys.at(event->GetEventKey());
        for(auto handle : handles)
        {
            if(m_listenersHandle.find(handle) != m_listenersHandle.end())
            {
                m_listenersHandle.at(handle)(event);
            }
        }
    }
}

} // ns trx