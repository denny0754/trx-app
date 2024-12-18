/* Project Headers*/
#include <trx/net/SessionFw.hpp>
#include <trx/net/LocalSessionWrapper.hpp>
#include <trx/net/RemoteSessionWrapper.hpp>
#include <trx/util/logging/LogManager.hpp>

namespace trx::net
{

SessionFw::SessionFw(SessionType stype, const std::string& conn_string)
{
    m_fwId = "_APP_SESSION";
    m_sessionType = stype;
    m_connString = conn_string;
}

void SessionFw::Initialize()
{
    TRX_TRC("APP", "Creating a new session and initializing it with connection string: {0}", m_connString);
    if(m_sessionType == SessionType::LOCAL_SESSION)
    {
        InitializeLocalSession();
    }
    else if(m_sessionType == SessionType::REMOTE_SESSION)
    {
        InitializeRemoteSession();
    }
}

void SessionFw::Update()
{

}

void SessionFw::Shutdown()
{

}

void SessionFw::Restart()
{
    
}

void SessionFw::InitializeRemoteSession()
{
    m_sessionWrapper = std::make_unique<LocalSessionWrapper>();
}

void SessionFw::InitializeLocalSession()
{
    m_sessionWrapper = std::make_unique<RemoteSessionWrapper>();
}

} // ns trx::net