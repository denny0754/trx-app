/* Project Headers */
#include <trx/ev/MiddlewareFw.hpp>
#include <trx/util/logging/LogManager.hpp>

/* Standard Headers */
#include <random>

namespace trx::ev
{

MiddlewareFw::MiddlewareFw()
	: Framework()
{
	m_fwId = "_APP_MIDDLEWARE";
}

void MiddlewareFw::Initialize()
{
	m_isDetached = false;
	m_registerOnce = true;
	m_isReady = true;
}

void MiddlewareFw::Update()
{
	while (!m_eventQueue.empty())
	{
		PushEvent(m_eventQueue.front().get());
		m_eventQueue.pop();
	}
}

void MiddlewareFw::Shutdown()
{
	//  Removing all events currently queued.
	while (!m_eventQueue.empty())
	{
		m_eventQueue.pop();
	}
	m_subscribers.erase(m_subscribers.begin(), m_subscribers.end());
}

void MiddlewareFw::Restart()
{
	Shutdown();
}

void MiddlewareFw::Subscribe(EventKey event_key, MiddlewareFw::EventListenerRef listener)
{
	TRX_TRC("APP", "Subscribing to event with key `{0}` - Listener ID: `{1}`", (int)event_key, listener.target_type().raw_name());
	m_subscribers[event_key].emplace_back(listener);
}

void MiddlewareFw::Unsubscribe(const MiddlewareFw::EventListenerRef& listener)
{
	for (auto [event_key, handler] : m_subscribers)
	{
		Unsubscribe(event_key, listener);
	}
}

void MiddlewareFw::Unsubscribe(EventKey event_key, const EventListenerRef& listener)
{
	if (m_subscribers.find(event_key) != m_subscribers.end())
	{
		auto it = std::find_if(
			m_subscribers.at(event_key).begin(),
			m_subscribers.at(event_key).end(),
			[listener](const EventListenerRef& subscriber_ref) {
				return subscriber_ref.target_type().name() == listener.target_type().name();
			}
		);
		if (it != m_subscribers.at(event_key).end())
		{
			m_subscribers.at(event_key).erase(it);
		}
	}
}

void MiddlewareFw::PushEvent(Event* event)
{
	EventKey ekey = event->GetEventKey();
	if (m_subscribers.find(ekey) != m_subscribers.end())
	{
		for (auto handler : m_subscribers.at(ekey))
		{
			handler(event);
		}
	}
}

void MiddlewareFw::QueueEvent(std::unique_ptr<Event> event)
{
	m_eventQueue.push(std::move(event));
}

} // ns trx::ev