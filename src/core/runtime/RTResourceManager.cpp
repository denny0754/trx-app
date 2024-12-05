/* Project Headers */
#include <trx/core/runtime/RTResourceManager.hpp>
#include <trx/utils/logging/LogManager.hpp>

namespace trx
{

static RTResourceManager* g_instance = nullptr;

RTResourceManager& RTResourceManager::Get()
{
    if(!g_instance)
    {
        g_instance = new RTResourceManager(); 
    }
    return *g_instance;
}

void RTResourceManager::Initialize()
{
    TRX_DBG("APP", "Runtime Resource Manager has been initialized...");
}

void RTResourceManager::Shutdown()
{
    for(auto [rsrc_key, rsrc] : m_resources)
    {
        rsrc->Destroy();
    }
}

void RTResourceManager::PushResource(const std::string& rsrc_key, std::shared_ptr<RTResource> rsrc)
{
    std::lock_guard<std::mutex> lock_guard(m_mtMutex);

    if(m_resources.find(rsrc_key) != m_resources.end())
    {
        m_resources.erase(rsrc_key);
    }

    m_resources[rsrc_key] = rsrc;

    m_resources.at(rsrc_key)->Initialize();
}

void RTResourceManager::PushResource(const std::string& rsrc_key, RTResource* rsrc)
{
    std::lock_guard<std::mutex> lock_guard(m_mtMutex);

    std::shared_ptr<RTResource> resource(rsrc);

    PushResource(rsrc_key, std::move(resource));
}

std::shared_ptr<RTResource> RTResourceManager::GetResource(const std::string& rsrc_key)
{
    std::lock_guard<std::mutex> lock_guard(m_mtMutex);

    if(m_resources.find(rsrc_key) == m_resources.end())
    {
        return nullptr;
    }
    else
    {
        return m_resources.at(rsrc_key);
    }
}

void RTResourceManager::PopResource(const std::string& rsrc_key)
{
    std::lock_guard<std::mutex> lock_guard(m_mtMutex);

    if(m_resources.find(rsrc_key) != m_resources.end())
    {
        m_resources.erase(rsrc_key);
    }
}

}