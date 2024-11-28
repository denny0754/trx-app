/* Project Headers */
#include <trx/core/framework/FrontendFw.hpp>
#include <trx/core/Middleware.hpp>
#include <trx/utils/logging/LogManager.hpp>

/* External Headers */
#include <GLFW/glfw3.h>

namespace trx
{

void FrontendFw::Initialize()
{
    TRX_CREATE_LOGGER("FrontendFw", true, false, "", spdlog::level::level_enum::debug)
    TRX_INF("FrontendFw", "Initializing Frontend Framework...");

    if(!glfwInit())
    {
        TRX_ERR("FrontendFw", "Error while initializing GLFW context...");
        return;
    }

    m_nativeWindow = glfwCreateWindow(600, 400, "Transaction-X", NULL, NULL);
    if(!m_nativeWindow)
    {
        TRX_ERR("FrontendFw", "Error while initializing GLFW window...");
        return;
    }

    glfwMakeContextCurrent(m_nativeWindow);

    m_layerStack = LayerStack();

    /* Begin of push of all Layers */

    /* End of push of all Layers */

    m_isReady = true;
}

void FrontendFw::Update()
{
    if(glfwWindowShouldClose(m_nativeWindow))
    {
        Middleware::Get().PushEvent(new Event(nullptr, EventKey::APPLICATION_SHOULD_CLOSE));
    }

    glfwPollEvents();

    static double currentFrameTime = 0.f;
    static double currentDeltaTime = 0.f;
    static double previousFrameTime = 0.f;

    currentFrameTime = glfwGetTime();
    currentDeltaTime = currentDeltaTime - previousFrameTime;
    previousFrameTime = currentDeltaTime;

    m_layerStack.Update(currentFrameTime);

    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(.5f, .5f, .5f, 0.0f);

    m_layerStack.Render();

    glfwSwapBuffers(m_nativeWindow);
}

void FrontendFw::Shutdown()
{
    m_layerStack.Shutdown();

    glfwTerminate();
}

void FrontendFw::Restart()
{
    //!TODO: As soon as the `Shutdown` method has been fully implemented
    //       the call to the `Shutdown` may be removed.
    // First, shutdown the framework.
    Shutdown();
    // Second, initialize it once again.
    Initialize();
}

} // ns trx