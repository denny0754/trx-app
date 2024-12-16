/* Project Headers */
#include <trx/ui/AboutLayer.hpp>
#include <trx/ev/MiddlewareFw.hpp>
#include <trx/ev/LayerEvent.hpp>
#include <trx/Application.hpp>

/* External Headers */
#include <imgui.h>

namespace trx::ui
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
	auto mw_fw = Application::Get().GetFw("_APP_MIDDLEWARE")->ToType<ev::MiddlewareFw*>();
	if (!m_isWindowOpen)
	{
		mw_fw->PushEvent(
			new ev::LayerEvent(new ev::LayerEventData(nullptr, "ABOUT_LAYER"), ev::EventKey::POP_LAYER_DEFERRED)
		);
	}
}

void AboutLayer::OnShutdown()
{

}

} // ns trx::ui