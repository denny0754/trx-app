/* Project Headers */
#include <trx/net/RemoteSessionWrapper.hpp>

namespace trx::net
{

std::shared_ptr<intf::SessionResource> RemoteSessionWrapper::ReadResource(std::weak_ptr<intf::SessionRequest> request)
{
    return nullptr;
}

std::shared_ptr<intf::SessionResource> RemoteSessionWrapper::WriteResource(std::weak_ptr<intf::SessionRequest> request)
{
    return nullptr;
}

} // ns trx::net