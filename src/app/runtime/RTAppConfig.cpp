/* Project Headers */
#include <trx/app/runtime/RTAppConfig.hpp>

/* Standard Headers */
#include <fstream>
#include <iostream>

namespace trx
{

void RTAppConfig::Initialize()
{
	m_appConfig = nlohmann::json();
}

void RTAppConfig::Load(const std::filesystem::path& file_path)
{
	m_configPath = file_path;
	m_configPath = m_configPath.remove_filename();
	m_configFile = file_path.filename();

	std::ifstream ifapp_config(m_configPath / m_configFile);
	if(ifapp_config)
	{
		m_appConfig = nlohmann::json::parse(ifapp_config);
	}
}

void RTAppConfig::Load(const std::string& json_data)
{
	m_appConfig = nlohmann::json::parse(json_data);
}

void RTAppConfig::LoadOrDefault(const std::filesystem::path& file_path, const std::string& json_data)
{
	m_configPath = file_path;
	m_configPath = m_configPath.remove_filename();
	m_configFile = file_path.filename();

	std::ifstream ifapp_config(m_configPath / m_configFile);
	if(!ifapp_config)
	{
		Load(json_data);
		Save();
	}
	else
	{
		Load(file_path);
	}
}

void RTAppConfig::Reload()
{
	Load(m_configPath);
}

void RTAppConfig::Save()
{
	std::filesystem::create_directories(m_configPath);
	std::ofstream ofapp_config(m_configPath / m_configFile);
	if(ofapp_config)
	{
		ofapp_config << std::setw(4) << m_appConfig << std::endl;
	}
}

void RTAppConfig::Destroy()
{
	Save();
}

nlohmann::json& RTAppConfig::GetConfig()
{
    return m_appConfig;
}

}