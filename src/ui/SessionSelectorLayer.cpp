/* Project Headers */
#include <trx/ui/SessionSelectorLayer.hpp>
#include <trx/ev/MiddlewareFw.hpp>
#include <trx/util/logging/LogManager.hpp>
#include <trx/ev/FrameworkEvent.hpp>
#include <trx/net/SessionFw.hpp>
#include <trx/Application.hpp>

/* External Headers */
#include <imgui.h>
#include <GLFW/glfw3.h>

/* Standard Headers */
#include <iostream>

namespace trx::ui
{

SessionSelectorLayer::SessionSelectorLayer()
    : Layer("SESSION_SELECTOR_LAYER")
{

}

void SessionSelectorLayer::OnInitialize()
{
    auto mw_fw = Application::Get().GetFw("_APP_MIDDLEWARE")->ToType<ev::MiddlewareFw*>();
    mw_fw->Subscribe(
        ev::EventKey::WINDOW_RESIZE_EVENT,
        std::bind(&SessionSelectorLayer::OnWindowResize, this, std::placeholders::_1)
    );
}

void SessionSelectorLayer::OnRender()
{
    ImGuiIO& imgui_io = ImGui::GetIO();
    
    auto win_size = imgui_io.DisplaySize;
    m_selectorWinSize.x = (float)win_size.x / 2;
    m_selectorWinSize.y = (float)win_size.y / 2;

    ImGui::SetNextWindowSize(m_selectorWinSize);
    ImGui::Begin(
        "Session Selector",
        nullptr,
        ImGuiWindowFlags_::ImGuiWindowFlags_NoSavedSettings |
        ImGuiWindowFlags_::ImGuiWindowFlags_NoNav |
        ImGuiWindowFlags_::ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_::ImGuiWindowFlags_NoResize
    );

    ImGui::Text("Connection Type:");
    ImGui::SameLine();
    ImGui::Combo(
        "##connection_type",
        &m_sessionDataRef.ConnectionTypeSelected,
        m_sessionDataRef.ConnectionType,
        IM_ARRAYSIZE(m_sessionDataRef.ConnectionType)
    );

    ImGui::Text("Username:");
    ImGui::SameLine();
    ImGui::InputText("##session_user", m_sessionDataRef.ServerUSR, 255);
    
    ImGui::Text("Password:");
    ImGui::SameLine();
    ImGui::InputText("##session_pass", m_sessionDataRef.ServerPWD, 255, ImGuiInputTextFlags_::ImGuiInputTextFlags_Password);

    // If we select the Remote connection type, we should display the URL input.
    if(m_sessionDataRef.ConnectionTypeSelected == 0)
    {
        ImGui::Text("Server URL:");
        ImGui::SameLine();
        ImGui::InputText("##session_url", m_sessionDataRef.ServerURL, 255);
    }

    m_sessionDataRef.OpenSession = ImGui::Button("Connect...");

    ImGui::End();

    // static bool show_demo_window = false;
    // ImGui::Checkbox("Show Demo Window", &show_demo_window);
    //if (show_demo_window)
    //{
    //    ImGui::ShowDemoWindow(&show_demo_window);
    //}

}

void SessionSelectorLayer::OnUpdate(double delta)
{
    auto mw_fw = Application::Get().GetFw("_APP_MIDDLEWARE")->ToType<ev::MiddlewareFw*>();

    if (m_sessionDataRef.OpenSession)
    {
        // Remote Session
        if (m_sessionDataRef.ConnectionTypeSelected == 0)
        {
            TRX_TRC("APP", "Remote Session has been selected and it's going to  be bootstrapped soon...");
            mw_fw->PushEvent(
                new ev::FrameworkEvent(
                    new ev::FrameworkEventData(
                        new net::SessionFw(
                            net::SessionType::REMOTE_SESSION,
                            fmt::format("{0};{1};{2}", m_sessionDataRef.ServerURL, m_sessionDataRef.ServerUSR, m_sessionDataRef.ServerPWD)
                        )
                    ),
                    ev::EventKey::BOOTSTRAP_FRAMEWORK
                )
            );
        }
        // Local Session
        else if (m_sessionDataRef.ConnectionTypeSelected == 1)
        {
            TRX_TRC("APP", "Local Session has been selected and it's going to be bootstrapped soon...");
            mw_fw->PushEvent(
                new ev::FrameworkEvent(
                    new ev::FrameworkEventData(
                        new net::SessionFw(
                            net::SessionType::LOCAL_SESSION,
                            fmt::format("127.0.0.1:8888;{1};{2}", m_sessionDataRef.ServerUSR, m_sessionDataRef.ServerPWD)
                        )
                    ),
                    ev::EventKey::BOOTSTRAP_FRAMEWORK
                )
            );
        }
    }
}

void SessionSelectorLayer::OnShutdown()
{
    TRX_TRC("APP", "Shutting down layer `Session Selector`...");

    auto mw_fw = Application::Get().GetFw("_APP_MIDDLEWARE")->ToType<ev::MiddlewareFw*>();
    mw_fw->Unsubscribe(std::bind(&SessionSelectorLayer::OnWindowResize, this, std::placeholders::_1));
}

void SessionSelectorLayer::OnWindowResize(ev::Event* event)
{
    const ev::WindowResizeEvent* win_event = event->ToType<ev::WindowResizeEvent>();

    const ev::WindowResizeEventData* win_size_data = event->GetEventData()->ToType<ev::WindowResizeEventData>();

    // LogManager::Get().GetDefaultLogger().info("MenuOverlay~OnWindowResize: {0} - {1}", win_size_data->GetWidth(), win_size_data->GetHeight());

    m_selectorWinSize.x = (float)win_size_data->GetWidth() / 2;
    m_selectorWinSize.y = (float)win_size_data->GetHeight() / 2;
}

} // ns trx::ui