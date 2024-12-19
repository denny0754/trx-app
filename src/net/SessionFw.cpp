/* Project Headers*/
#include <trx/net/SessionFw.hpp>
#include <trx/Application.hpp>
#include <trx/ev/MiddlewareFw.hpp>
#include <trx/util/logging/LogManager.hpp>
#include <trx/net/RESTServerFw.hpp>
#include <trx/ev/FrameworkEvent.hpp>
#include <trx/ev/FrameworkEventData.hpp>

namespace trx::net
{

SessionFw::SessionFw(SessionType stype, const std::string& address, const std::string& user, const std::string& pwd)
{
    m_fwId = "_APP_SESSION";
    m_sessionType = stype;
    m_srvAddress = address;
    m_srvUser = user;
    m_srvPass = pwd;
}

void SessionFw::Initialize()
{
    TRX_TRC("APP", "Creating a new session and initializing it with connection string: {0};{1};{2}", m_srvAddress, m_srvUser, m_srvPass);
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
    
}

void SessionFw::InitializeLocalSession()
{
    TRX_TRC("APP", "Initializing a local session by creating a local API Server...");

    auto mw_fw = Application::Get().GetFw("_APP_MIDDLEWARE")->ToType<ev::MiddlewareFw*>();

    mw_fw->PushEvent(
        new ev::FrameworkEvent(
            new ev::FrameworkEventData(
                new net::RESTServerFw("127.0.0.1", 8888)
            ),
            ev::EventKey::BOOTSTRAP_FRAMEWORK
        )
    );
}

} // ns trx::net