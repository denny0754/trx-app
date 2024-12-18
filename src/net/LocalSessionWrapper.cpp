/* Project Headers */
#include <trx/net/LocalSessionWrapper.hpp>

namespace trx::net
{

LocalSessionWrapper::LocalSessionWrapper(const std::string& db_file)
{
    m_databaseFile = db_file;
    std::unique_ptr<Wt::Dbo::backend::Sqlite3> db_backend = std::make_unique<Wt::Dbo::backend::Sqlite3>(m_databaseFile);
    m_session.setConnection(std::move(db_backend));
}

std::shared_ptr<intf::SessionResource> LocalSessionWrapper::ReadResource(std::weak_ptr<intf::SessionRequest> request)
{
    return nullptr;    
}

std::shared_ptr<intf::SessionResource> LocalSessionWrapper::WriteResource(std::weak_ptr<intf::SessionRequest> request)
{
    return nullptr;
}

} // ns trx::net