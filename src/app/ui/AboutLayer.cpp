/* Project Headers */
#include <trx/app/ui/AboutLayer.hpp>
#include <trx/core/Middleware.hpp>
#include <trx/app/event/LayerEvent.hpp>

/* External Headers */
#include <imgui.h>

namespace trx
{

AboutLayer::AboutLayer()
	: Layer("ABOUT_LAYER")
{
	m_isWindowOpen = true;
}

void AboutLayer::OnInitialize()
{
	m_isWindowOpen = true;
}

void AboutLayer::OnRender()
{
	ImGui::Begin("About Transaction-X", &m_isWindowOpen, ImGuiWindowFlags_::ImGuiWindowFlags_NoSavedSettings);
	ImGui::Text("Transaction-X - Personal Finance Management");
	ImGui::Separator();
	ImGui::Text("Website: ");
	ImGui::SameLine();
	ImGui::TextLinkOpenURL("TrX", "https::/trx.com");
	ImGui::End();
}

void AboutLayer::OnUpdate(double delta_time)
{
	if (!m_isWindowOpen)
	{
		Middleware::Get().PushEvent(
			new LayerEvent(new LayerEventData(nullptr, "ABOUT_LAYER"), EventKey::POP_LAYER_DEFERRED)
		);
	}
}

void AboutLayer::OnShutdown()
{

}

} // ns trx