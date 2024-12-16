/* Project Headers */
#include <trx/ui/AppSettingsLayer.hpp>
#include <trx/util/logging/LogManager.hpp>
#include <trx/ev/MiddlewareFw.hpp>
#include <trx/ev/LayerEvent.hpp>
#include <trx/Application.hpp>

/* External Headers */
#include <imgui.h>

namespace trx::ui
{

AppSettingsLayer::AppSettingsLayer()
    : Layer("APP_SETTINGS_LAYER")
{
    m_isWindowOpen = true;

    m_settingsDataRef.CurrentLogLevel = new int;
    m_settingsDataRef.PreviousLogLevel = new int;
}

void AppSettingsLayer::OnInitialize()
{
    m_isWindowOpen = true;
    *m_settingsDataRef.CurrentLogLevel = (int)util::LogManager::Get().GetLogger("APP").level();
    *m_settingsDataRef.PreviousLogLevel = *m_settingsDataRef.CurrentLogLevel;
}

void AppSettingsLayer::OnRender()
{
     ImGui::Begin(
         "Application Settings",
         &m_isWindowOpen,
         ImGuiWindowFlags_::ImGuiWindowFlags_NoSavedSettings
     );

     if (ImGui::CollapsingHeader("Logging", ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_DefaultOpen))
     {
         ImGui::Text("Configure the logging settings.");
         ImGui::Combo("Log Level", m_settingsDataRef.CurrentLogLevel, m_logLevels, IM_ARRAYSIZE(m_logLevels));
     }
     if (ImGui::CollapsingHeader("Themes", ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_DefaultOpen))
     {
         ImGui::Text("Set a default theme or create your own.");
     }
     if (ImGui::CollapsingHeader("Connections", ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_DefaultOpen))
     {
         ImGui::Text("Manage Connections or add new ones.");
     }
     if (ImGui::CollapsingHeader("System", ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_DefaultOpen))
     {
         ImGui::Text("System Configuration:");
     }

     m_settingsDataRef.ApplySettingsButton = ImGui::Button("Apply", ImVec2(50, 20));

     ImGui::End();
}

void AppSettingsLayer::OnUpdate(double delta)
{
    auto mw_fw = Application::Get().GetFw("_APP_MIDDLEWARE")->ToType<ev::MiddlewareFw*>();
    if(!m_isWindowOpen)
    {
        TRX_TRC("APP", "App settings has been closed...");
        mw_fw->PushEvent(
            new ev::LayerEvent(new ev::LayerEventData(nullptr, "APP_SETTINGS_LAYER"), ev::EventKey::POP_LAYER_DEFERRED)
        );
    }

    if (m_isWindowOpen && m_settingsDataRef.ApplySettingsButton)
    {
        TRX_TRC("APP", "Applying new settings...");
        if (*m_settingsDataRef.CurrentLogLevel != *m_settingsDataRef.PreviousLogLevel)
        {
            util::LogManager::Get().GetLogger("APP").set_level((spdlog::level::level_enum)*m_settingsDataRef.CurrentLogLevel);
            *m_settingsDataRef.PreviousLogLevel = *m_settingsDataRef.CurrentLogLevel;
        }
    }
}

void AppSettingsLayer::OnShutdown()
{
    delete m_settingsDataRef.CurrentLogLevel;
    delete m_settingsDataRef.PreviousLogLevel;
}

} // ns trx::ui