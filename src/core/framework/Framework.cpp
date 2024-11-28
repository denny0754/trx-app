/* Project Headers */
#include <trx/core/framework/Framework.hpp>

namespace trx
{

Framework::Framework()
{
    m_isReady = false;
}

bool Framework::IsReady() const
{
    return m_isReady;
}

}