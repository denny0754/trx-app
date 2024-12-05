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
    std::ifstream ifapp_config("./cfg/app.json");
	if(ifapp_config)
	{
		m_appConfig = nlohmann::json::parse(ifapp_config);
	}

	if(m_appConfig.empty())
	{
		m_appConfig = nlohmann::json::parse(R"(
			{
				"appearance": {
					"font": "",
					"width": 1280,
					"height": 720
				},
				"log": {
					"level": 2
				}
			}
		)");
		std::ofstream ofapp_config("./cfg/app.json");
		ofapp_config << std::setw(4) << m_appConfig << std::endl;
	}
}

void RTAppConfig::Destroy()
{
    std::ofstream ofapp_config("./cfg/app.json");
    ofapp_config << std::setw(4) << m_appConfig << std::endl;
}

nlohmann::json& RTAppConfig::GetConfig()
{
    return m_appConfig;
}

}