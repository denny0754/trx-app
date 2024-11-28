#include <trx/core/ui/window/Window.hpp>
#include <trx/utils/logging/LogManager.hpp>

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

Window::~Window()
{
    glfwTerminate();
}

void Window::InitWindow()
{
    TRX_CREATE_LOGGER("Core-Window", true, false, "", spdlog::level::level_enum::debug)
    TRX_GET_LOGGER("Core-Window").info("Initializing Application Core-Window...");

    m_nativeWindow = nullptr;
    
    if(!glfwInit())
    {
        TRX_GET_LOGGER("Core-Window").debug("Error while initializing GLFW context...");
        m_isWindowReady = false;
        return;
    }

    m_nativeWindow = glfwCreateWindow(
        m_winSettings.WindowSize.x,         // Width
        m_winSettings.WindowSize.y,         // Height
        m_winSettings.WindowTitle.c_str(),  // Title
        NULL,                               // Monitor: Fullscreen or Windowed
        NULL                                // Shared Window
    );

    if (!m_nativeWindow)
    {
        TRX_GET_LOGGER("Core-Window").debug("Error while initializing GLFW window...");
        glfwTerminate();
        m_isWindowReady = false;
        return;
    }

    glfwMakeContextCurrent(m_nativeWindow);

    m_isWindowReady = true;

    // Initialize Event Listeners
    TRX_GET_LOGGER("Core-Window").debug("Window initialized succesfully...");

    // while(!glfwWindowShouldClose(m_nativeWindow))
    // {
    //     glfwPollEvents();

    //     glClear(GL_COLOR_BUFFER_BIT);

    //     glfwSwapBuffers(m_nativeWindow);
    // }
}

void Window::Create(const WindowContextSettings& context_settings)
{
    m_winSettings = context_settings;
    InitWindow();
}

void Window::SetSize(Vector2u win_size)
{
    m_winSettings.WindowSize = win_size;
    glfwSetWindowSize(m_nativeWindow, win_size.x, win_size.x);
}

Vector2u Window::GetSize() const
{
    return m_winSettings.WindowSize;
}

void Window::SetTitle(const std::string& win_title)
{
    m_winSettings.WindowTitle = win_title;
    glfwSetWindowTitle(m_nativeWindow, win_title.c_str());
}

const std::string& Window::GetTitle() const
{
    return m_winSettings.WindowTitle;
}

bool Window::IsWindowReady() const
{
    return m_isWindowReady;
}

bool Window::ShouldWindowClose() const
{
    return glfwWindowShouldClose(m_nativeWindow);
}

GLFWwindow* Window::GetNativeWindow()
{
    return m_nativeWindow;
}

} // ns trx