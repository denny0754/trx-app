/* Project Headers */
#include <trx/rsrc/RTResourceManagerFw.hpp>
#include <trx/util/logging/LogManager.hpp>

namespace trx::rsrc
{

RTResourceManagerFw::RTResourceManagerFw()
    : Framework()
{
    m_fwId = "_APP_RT_RSRC_MANAGER";
}

void RTResourceManagerFw::Initialize()
{

}

void RTResourceManagerFw::Shutdown()
{
    for(auto [rsrc_key, rsrc] : m_resources)
    {
        rsrc->Destroy();
    }
}

void RTResourceManagerFw::Update()
{

}

void RTResourceManagerFw::Restart()
{

}

void RTResourceManagerFw::PushResource(const std::string& rsrc_key, std::shared_ptr<RTResource> rsrc)
{
    std::lock_guard<std::mutex> lock_guard(m_mtMutex);

    if(m_resources.find(rsrc_key) != m_resources.end())
    {
        m_resources.erase(rsrc_key);
    }

    m_resources[rsrc_key] = rsrc;

    m_resources.at(rsrc_key)->Initialize();
}

void RTResourceManagerFw::PushResource(const std::string& rsrc_key, RTResource* rsrc)
{
    std::lock_guard<std::mutex> lock_guard(m_mtMutex);

    std::shared_ptr<RTResource> resource(rsrc);

    PushResource(rsrc_key, std::move(resource));
}

std::shared_ptr<RTResource> RTResourceManagerFw::GetResource(const std::string& rsrc_key)
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

void RTResourceManagerFw::PopResource(const std::string& rsrc_key)
{
    std::lock_guard<std::mutex> lock_guard(m_mtMutex);

    if(m_resources.find(rsrc_key) != m_resources.end())
    {
        m_resources.erase(rsrc_key);
    }
}

} // ns trx::rsrc