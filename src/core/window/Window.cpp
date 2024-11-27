#include <trx/core/window/Window.hpp>

namespace trx
{
    
Window::Window(Vector2u win_size, const std::string& win_title)
{
    m_winSettings = WindowContextSettings();
    m_winSettings.WindowSize = win_size;
    m_winSettings.WindowTitle = win_title;
    m_nativeWindow = nullptr;
    InitWindow();
}

Window::Window(const WindowContextSettings& context_settings)
{
    m_winSettings = context_settings;
    m_nativeWindow = nullptr;
    InitWindow();
}

void Window::InitWindow()
{
    m_nativeWindow = glfwCreateWindow(
        m_winSettings.WindowSize.x,         // Width
        m_winSettings.WindowSize.y,         // Height
        m_winSettings.WindowTitle.c_str(),  // Title
        NULL,                               // Monitor: Fullscreen or Windowed
        NULL                                // Shared Window
    );
}

void Window::SetSize(Vector2u win_size)
{

}

Vector2u Window::GetSize() const
{
    return m_winSettings.WindowSize;
}

void Window::SetTitle(const std::string& win_title)
{

}

const std::string& Window::GetTitle() const
{
    return m_winSettings.WindowTitle;
}

} // ns trx