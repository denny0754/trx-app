/* Project Headers */
#include <trx/app/ui/SessionSelectorLayer.hpp>

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

}

void SessionSelectorLayer::OnRender()
{
    ImGui::Begin("Session Selector");
    ImGui::Button("Local Session(DB)", ImVec2(150, 50));
    ImGui::Button("Remote Session(DB)", ImVec2(150, 50));
    ImGui::End();
}

void SessionSelectorLayer::OnUpdate(double delta)
{

}

void SessionSelectorLayer::OnShutdown()
{

}

} // ns trx