/* Project Headers */
#include <trx/app/event/WindowResizeEvent.hpp>

namespace trx
{

WindowResizeEvent::WindowResizeEvent(WindowResizeEventData* new_window_size)
    : Event(new_window_size, EventKey::WINDOW_RESIZE_EVENT)
{

}

} // ns