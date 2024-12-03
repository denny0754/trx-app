/* Project Headers */
#include <trx/app/event/WindowResizeEventData.hpp>

namespace trx
{

WindowResizeEventData::WindowResizeEventData(int width, int height)
    : EventData(), m_winWidth(width), m_winHeight(height)
{

}

int WindowResizeEventData::GetWidth() const
{
    return m_winWidth;
}

int WindowResizeEventData::GetHeight() const
{
    return m_winHeight;
}

} // ns