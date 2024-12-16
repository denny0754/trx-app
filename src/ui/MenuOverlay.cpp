/* Project Headesr */
#include <trx/ui/MenuOverlay.hpp>
#include <trx/ev/MiddlewareFw.hpp>
#include <trx/util/logging/LogManager.hpp>
#include <trx/ev/LayerEvent.hpp>

#include <trx/ui/SessionSelectorLayer.hpp>
#include <trx/ui/AppSettingsLayer.hpp>
#include <trx/ui/AboutLayer.hpp>
#include <trx/Application.hpp>

/* External Headers */
#include <imgui.h>

namespace trx::ui
{

MenuOverlay::MenuOverlay()
    : Layer("MAIN_MENU_OVERLAY")
{
    
}

void MenuOverlay::OnInitialize()
{

}

void MenuOverlay::OnRender()
{
    if(ImGui::BeginMainMenuBar())
    {
        // `File` Menu
        if(ImGui::BeginMenu("Session"))
        {

            m_menuRefData.M_I_NewSessionClicked = ImGui::MenuItem("New session");
            m_menuRefData.M_I_CloseCurrentSessionClicked = ImGui::MenuItem("Close current session");
            m_menuRefData.M_I_ExitClicked = ImGui::MenuItem("Exit...");
            ImGui::EndMenu();
        }

        if(ImGui::BeginMenu("Tools"))
        {
            m_menuRefData.M_I_SettingsClicked = ImGui::MenuItem("Settings");
            ImGui::EndMenu();
        }

        if(ImGui::BeginMenu("View"))
        {
            ImGui::EndMenu();
        }

        if(ImGui::BeginMenu("Help"))
        {
            m_menuRefData.M_I_AboutClicked = ImGui::MenuItem("About...");
            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }
}

void MenuOverlay::OnUpdate(double delta)
{
    auto mw_fw = Application::Get().GetTypedFw<ev::MiddlewareFw>("_APP_MIDDLEWARE");
    if(m_menuRefData.M_I_ExitClicked)
    {
        mw_fw->PushEvent(new ev::Event(nullptr, ev::EventKey::APPLICATION_SHOULD_CLOSE));
    }
    if(m_menuRefData.M_I_NewSessionClicked)
    {
        mw_fw->PushEvent(
            new ev::LayerEvent(new ev::LayerEventData(new SessionSelectorLayer()), ev::EventKey::PUSH_LAYER_DEFERRED)
        );
        m_menuRefData.M_I_NewSessionClicked = false;
    }
    if(m_menuRefData.M_I_SettingsClicked)
    {
        TRX_TRC("APP", "Fulfilling the request to open the settings menu...");
        mw_fw->PushEvent(
            new ev::LayerEvent(new ev::LayerEventData(new AppSettingsLayer()), ev::EventKey::PUSH_LAYER_DEFERRED)
        );
        m_menuRefData.M_I_SettingsClicked = false;
    }
    if (m_menuRefData.M_I_AboutClicked)
    {
        mw_fw->PushEvent(
            new ev::LayerEvent(new ev::LayerEventData(new AboutLayer()), ev::EventKey::PUSH_LAYER_DEFERRED)
        );
        m_menuRefData.M_I_AboutClicked = false;
    }
}

void MenuOverlay::OnShutdown()
{

}

} // ns trx::ui