/* Project Headers */
#include <trx/net/RESTServerFw.hpp>

namespace trx::net
{

RESTServerFw::RESTServerFw(const std::string& address, uint16_t port)
    : Framework(), m_address(address), m_port(port)
{
    m_fwId = "_APP_REST_SRV";
    m_isDetached = true;
    m_registerOnce = true;
}

void RESTServerFw::Initialize()
{

}

void RESTServerFw::Update()
{

}

void RESTServerFw::Shutdown()
{

}

void RESTServerFw::Restart()
{
    
}

} // ns trx::net