/* Project Headesr */
#include <trx/app/ui/MenuOverlay.hpp>
#include <trx/core/Middleware.hpp>
#include <trx/utils/logging/LogManager.hpp>
#include <trx/app/event/LayerEvent.hpp>

#include <trx/app/ui/SessionSelectorLayer.hpp>
#include <trx/app/ui/AppSettingsLayer.hpp>

/* External Headers */
#include <imgui.h>

namespace trx
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

        // `About` Menu
        if(ImGui::BeginMenu("About"))
        {
            ImGui::EndMenu();
        }

        if(ImGui::BeginMenu("Help"))
        {
            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }
}

void MenuOverlay::OnUpdate(double delta)
{
    if(m_menuRefData.M_I_ExitClicked)
    {
        Middleware::Get().PushEvent(new Event(nullptr, EventKey::APPLICATION_SHOULD_CLOSE));
    }
    if(m_menuRefData.M_I_NewSessionClicked)
    {
        Middleware::Get().PushEvent(
            new LayerEvent(new LayerEventData(new SessionSelectorLayer()), EventKey::PUSH_LAYER_DEFERRED)
        );
        m_menuRefData.M_I_NewSessionClicked = false;
    }
    if(m_menuRefData.M_I_SettingsClicked)
    {
        TRX_TRC("APP", "Fulfilling the request to open the settings menu...");
        Middleware::Get().PushEvent(
            new LayerEvent(new LayerEventData(new AppSettingsLayer()), EventKey::PUSH_LAYER_DEFERRED)
        );
        m_menuRefData.M_I_SettingsClicked = false;
    }
}

void MenuOverlay::OnShutdown()
{

}

} // ns trx