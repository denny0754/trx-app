/* Project Headers */
#include <trx/ui/FrontendFw.hpp>
#include <trx/ev/MiddlewareFw.hpp>
#include <trx/util/logging/LogManager.hpp>
#include <trx/rsrc/RTResourceManagerFw.hpp>
#include <trx/ui/MenuOverlay.hpp>
#include <trx/ui/SessionSelectorLayer.hpp>

#include <trx/ev/WindowResizeEvent.hpp>
#include <trx/ev/WindowResizeEventData.hpp>

#include <trx/rsrc/RTAppConfig.hpp>

#include <trx/util/tools/Timer.hpp>

#include <trx/Application.hpp>

/* External Headers */
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace trx::ui
{

FrontendFw::FrontendFw()
    : Framework()
{
    m_fwId = "_APP_FRONTEND";
    m_nativeWindow = nullptr;
}

void FrontendFw::Initialize()
{
    TRX_DBG("APP", "Initializing the Frontend Framework...");

    auto rt_fw = Application::Get().GetFw("_APP_RT_RSRC_MANAGER")->ToType<rsrc::RTResourceManagerFw*>();

    nlohmann::json& glb_app_config = rt_fw->GetResource("GLB_APP_CONFIG")->ToType<rsrc::RTAppConfig>()->GetConfig();
    // nlohmann::json& usr_app_config = RTResourceManager::Get().GetResource("USR_APP_CONFIG")->ToType<RTUserAppConfig>();
    int glfw_window_width = glb_app_config["appearance"]["width"].get<int>();
    int glfw_window_height = glb_app_config["appearance"]["height"].get<int>();
    bool glfw_use_vsync = glb_app_config["appearance"]["vsync"].get<bool>();

    if(!glfwInit())
    {
        int glfw_error_code = glfwGetError(NULL);
        TRX_DBG("APP", "GLFW Window couldn't be initialized. GLFW Error Code: {0}", glfw_error_code);
        TRX_CRT("APP", "A problem occured while initializing the Application Window. Please, report it to the developer and provide a more verbose log.");
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    TRX_TRC("APP", "Initializing GLFW Window.");
    m_nativeWindow = glfwCreateWindow(
        glfw_window_width,
        glfw_window_height,
        "Transaction-X",
        nullptr,
        nullptr
    );

    if(!m_nativeWindow)
    {
        TRX_ERR("APP", "Error while initializing GLFW window...");
        return;
    }

    glfwMakeContextCurrent(m_nativeWindow);

    /* Setting the VSYNC flag */
    glfwSwapInterval(glfw_use_vsync);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    // m_imguiContext = ImGui::GetIO();
    ImGuiIO& io = ImGui::GetIO();

    // Enables keyboard controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    // Sets the ImGui theme to dark by default.
    ImGui::StyleColorsDark();

    // Making some tweaks to the ImGui windows
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    // Initializing the native GLFW window to be used by the ImGui context.
    ImGui_ImplGlfw_InitForOpenGL(m_nativeWindow, true);

    // Initializing the version of OpenGL
    ImGui_ImplOpenGL3_Init("#version 130");

    glfwSetWindowSizeCallback(m_nativeWindow, [](GLFWwindow* window, int width, int height){
        auto mw_fw = Application::Get().GetFw("_APP_MIDDLEWARE")->ToType<ev::MiddlewareFw*>();
        mw_fw->PushEvent(new ev::WindowResizeEvent(new ev::WindowResizeEventData(width, height)));
    });

    // m_layerStack = LayerStack();

    /* Begin of push of all Layers */
    m_layerStack.PushOverlay(std::make_unique<MenuOverlay>());
    m_layerStack.PushLayer(std::make_unique<SessionSelectorLayer>());
    /* End of push of all Layers */

    m_isReady = true;
}

void FrontendFw::Update()
{
    util::Timer fw_timer = util::Timer();

    ImGuiIO& io = ImGui::GetIO();
    auto mw_fw = Application::Get().GetFw("_APP_MIDDLEWARE")->ToType<ev::MiddlewareFw*>();
    
    if(glfwWindowShouldClose(m_nativeWindow))
    {
        mw_fw->PushEvent(new ev::Event(nullptr, ev::EventKey::APPLICATION_SHOULD_CLOSE));
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
    ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport());
    
    m_layerStack.Render();

    ImGui::Render();
    
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(.5f, .5f, .5f, 0.0f);
    
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        GLFWwindow* backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }

    glfwSwapBuffers(m_nativeWindow);

     TRX_TRC("APP", "FrontendFw~Update took: {0}ms", fw_timer.ElapsedMillis());
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

} // ns trx::ui