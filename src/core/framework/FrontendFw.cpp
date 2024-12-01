/* Project Headers */
#include <trx/core/framework/FrontendFw.hpp>
#include <trx/core/Middleware.hpp>
#include <trx/utils/logging/LogManager.hpp>
#include <trx/utils/config/ConfigIO.hpp>
#include <trx/app/ui/MenuOverlay.hpp>
#include <trx/app/ui/SessionSelectorLayer.hpp>

/* External Headers */
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace trx
{

void FrontendFw::Initialize()
{
    TRX_CREATE_LOGGER("FrontendFw", true, false, "", spdlog::level::level_enum::debug)
    TRX_INF("FrontendFw", "Initializing Frontend Framework...");

    m_config = ConfigIO::ParseFile("./config/frontend.cfg");

    ConfigSection& window_settings = m_config.get("WINDOW", ConfigSection("FRONTEND", {
        ConfigEntry("WINDOW_WIDTH", "1280"),
        ConfigEntry("WINDOW_HEIGHT", "720"),
        ConfigEntry("ENABLE_VSYNC", "true")
    }));

    if(!glfwInit())
    {
        TRX_ERR("FrontendFw", "Error while initializing GLFW context...");
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    m_nativeWindow = glfwCreateWindow(
        static_cast<int>(window_settings.get("WINDOW_WIDTH")),
        static_cast<int>(window_settings.get("WINDOW_HEIGHT")),
        "Transaction-X",
        nullptr,
        nullptr
    );

    if(!m_nativeWindow)
    {
        TRX_ERR("FrontendFw", "Error while initializing GLFW window...");
        return;
    }

    glfwMakeContextCurrent(m_nativeWindow);

    /* Setting the VSYNC flag */
    glfwSwapInterval((bool)window_settings.get("ENABLE_VSYNC"));

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    m_imguiContext = ImGui::GetIO();
    
    // Enables keyboard controls
    m_imguiContext.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    m_imguiContext.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    m_imguiContext.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    m_imguiContext.ConfigDockingNoSplit = false;
    m_imguiContext.ConfigViewportsNoTaskBarIcon = false;

    // Sets the ImGui theme to dark by default.
    ImGui::StyleColorsDark();

    // Making some tweaks to the ImGui windows
    ImGuiStyle& style = ImGui::GetStyle();
    if (m_imguiContext.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    // Initializing the native GLFW window to be used by the ImGui context.
    ImGui_ImplGlfw_InitForOpenGL(m_nativeWindow, true);

    // Initializing the version of OpenGL
    ImGui_ImplOpenGL3_Init("#version 130");

    m_layerStack = LayerStack();

    /* Begin of push of all Layers */
    m_layerStack.PushOverlay(new MenuOverlay());
    m_layerStack.PushLayer(new SessionSelectorLayer());
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

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGuiID dockspace_id = ImGui::GetID("ROOT_DOCKSPACE");
    ImGui::DockSpace(dockspace_id, ImVec2(0.f, 0.f), ImGuiDockNodeFlags_PassthruCentralNode);

    m_layerStack.Render();

    ImGui::Render();
    
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(.5f, .5f, .5f, 0.0f);
    
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if (m_imguiContext.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        GLFWwindow* backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }

    glfwSwapBuffers(m_nativeWindow);
}

void FrontendFw::Shutdown()
{
    m_layerStack.Shutdown();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(m_nativeWindow);
    glfwTerminate();

    m_nativeWindow = nullptr;
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