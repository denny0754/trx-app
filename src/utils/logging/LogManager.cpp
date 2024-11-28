/* Project Headers */
#include <trx/utils/logging/LogManager.hpp>

/* External Headers */
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace trx
{
    
static LogManager* g_instance = nullptr;

LogManager& LogManager::Get()
{
    if(!g_instance)
    {
        g_instance = new LogManager();
    }
    return *g_instance;
}

void LogManager::Initialize()
{
    LogSettings default_logger_settings;
    default_logger_settings.EnableConsole = true;
    default_logger_settings.EnableFile = false;
    default_logger_settings.MinLevel = spdlog::level::level_enum::info;
    default_logger_settings.Name = "DEFAULT";
    RegisterLogger(default_logger_settings);
}

void LogManager::Shutdown()
{
    if(!g_instance)
    {
        delete g_instance;
        g_instance = nullptr;
    }
}

void LogManager::RegisterLogger(const LogSettings& log_settings)
{
		if (m_loggers.find(log_settings.Name) != m_loggers.end()) {
			return;
		}

		std::vector<spdlog::sink_ptr> sinks;

		if (log_settings.EnableFile) {
			sinks.push_back(
				std::make_shared<spdlog::sinks::basic_file_sink_mt>(log_settings.OutFilePath.string())
			);
		}

		if (log_settings.EnableConsole) {
			sinks.push_back(
				std::make_shared<spdlog::sinks::stdout_color_sink_mt>()
			);
		}

		if (sinks.size() > 0) {
			m_loggers[log_settings.Name] = std::make_unique<spdlog::logger>(log_settings.Name, begin(sinks), end(sinks));
			
			if (m_loggers.find(log_settings.Name) != m_loggers.end()) {
				m_loggers[log_settings.Name]->set_level(log_settings.MinLevel);
				m_loggers[log_settings.Name]->set_pattern(log_settings.LogPattern);
			}
		}
}

void LogManager::UnregisterLogger(const std::string& name)
{
    if(m_loggers.find(name) != m_loggers.end())
    {
        m_loggers.erase(name);
    }
}

spdlog::logger& LogManager::GetLogger(const std::string& name)
{
    if(m_loggers.find(name) == m_loggers.end())
    {
        return *m_loggers.at("DEFAULT");
    }
    return *m_loggers.at(name);
}

spdlog::logger& LogManager::GetDefaultLogger()
{
    return GetLogger("DEFAULT");
}

} // ns trx