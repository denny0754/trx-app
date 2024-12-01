/* Project Headesr */
#include <trx/app/ui/MenuOverlay.hpp>
#include <trx/core/Middleware.hpp>

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
        if(ImGui::BeginMenu("File"))
        {
            // Add functionalities to the menu items.
            if(ImGui::MenuItem("Save")) { }

            m_menuRefData.M_I_ExitClicked = ImGui::MenuItem("Exit...");

            ImGui::EndMenu();
        }

        if(ImGui::BeginMenu("Tools"))
        {
            ImGui::EndMenu();
        }

        if(ImGui::BeginMenu("View"))
        {
            ImGui::EndMenu();
        }

        if(ImGui::BeginMenu("Settings"))
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
}

void MenuOverlay::OnShutdown()
{

}

} // ns trx