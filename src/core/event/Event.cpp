/* Project Headers */
#include <trx/core/event/Event.hpp>

namespace trx
{

Event::Event(EventData* event_data, EventKey event_key)
{
    m_eventData = event_data;
    m_eventKey = event_key;
}

EventData* Event::GetEventData()
{
    return m_eventData;
}

const EventKey Event::GetEventKey() const
{
    return m_eventKey;
}

} // ns trx