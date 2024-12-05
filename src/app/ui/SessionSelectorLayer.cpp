/* Project Headers */
#include <trx/app/ui/SessionSelectorLayer.hpp>
#include <trx/core/Middleware.hpp>
#include <trx/utils/logging/LogManager.hpp>

/* External Headers */
#include <imgui.h>
#include <GLFW/glfw3.h>

/* Standard Headers */
#include <iostream>

namespace trx
{

SessionSelectorLayer::SessionSelectorLayer()
    : Layer("SESSION_SELECTOR_LAYER")
{

}

void SessionSelectorLayer::OnInitialize()
{
    auto win_size = ImGui::GetIO().DisplaySize;
    m_selectorWinSize.x = (float)win_size.x / 2;
    m_selectorWinSize.y = (float)win_size.y / 2;
    Middleware::Get().RegisterListener(
        EventKey::WINDOW_RESIZE_EVENT,
        std::bind(&SessionSelectorLayer::OnWindowResize, this, std::placeholders::_1)
    );
}

void SessionSelectorLayer::OnRender()
{
    static bool show_demo_window = false;
    static const char* sessions[] = {"Remote", "Local"};
    static int* selected = new int;
    static char server_url[80] = "https://app.trx-app.com";
    static char server_user[80] = "";
    static char server_pass[80] = "";

    ImGui::SetNextWindowSize(m_selectorWinSize);
    ImGui::Begin(
        "Session Selector",
        nullptr,
        ImGuiWindowFlags_::ImGuiWindowFlags_NoSavedSettings |
        ImGuiWindowFlags_::ImGuiWindowFlags_NoNav |
        ImGuiWindowFlags_::ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_::ImGuiWindowFlags_NoResize
    );

    ImGui::Text("Session:");
    ImGui::SameLine();
    ImGui::Combo("##session", selected, sessions, 2);

    // Remote Connection
    if(*selected == 0)
    {
        ImGui::SeparatorText("Connection Configuration");
        ImGui::Text("URL: ");
        ImGui::SameLine();
        ImGui::InputText("##remote_session_url", server_url, 80);
        ImGui::Text("Username: ");
        ImGui::SameLine();
        ImGui::InputText("##remote_session_user", server_user, 80);
        ImGui::Text("Password: ");
        ImGui::SameLine();
        ImGui::InputText("##remote_session_passw", server_pass, 80, ImGuiInputTextFlags_::ImGuiInputTextFlags_Password);
    }
    else
    {

    }

    ImGui::Button("Connect");

    ImGui::Checkbox("Show Demo Window", &show_demo_window);
    ImGui::End();

    if(show_demo_window)
    {
        ImGui::ShowDemoWindow(&show_demo_window);
    }
}

void SessionSelectorLayer::OnUpdate(double delta)
{

}

void SessionSelectorLayer::OnShutdown()
{
    TRX_TRC("APP", "Shutting down layer `Session Selector`...");
}

void SessionSelectorLayer::OnWindowResize(Event* event)
{
    const WindowResizeEvent* win_event = event->ToType<WindowResizeEvent>();

    const WindowResizeEventData* win_size_data = event->GetEventData()->ToType<WindowResizeEventData>();

    // LogManager::Get().GetDefaultLogger().info("MenuOverlay~OnWindowResize: {0} - {1}", win_size_data->GetWidth(), win_size_data->GetHeight());

    m_selectorWinSize.x = (float)win_size_data->GetWidth() / 2;
    m_selectorWinSize.y = (float)win_size_data->GetHeight() / 2;
}

} // ns trx