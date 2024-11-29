/* Project Headers */
#include <trx/utils/config/ConfigEntry.hpp>

namespace trx
{

ConfigEntry::ConfigEntry(const std::string& key, const std::string& value)
{
    m_key = key;
    m_value = value;
}

ConfigEntry::ConfigEntry(ConfigEntry& entry)
{
    m_key = entry.m_key;
    m_value = entry.m_value;
}

ConfigEntry::ConfigEntry(ConfigEntry&& entry)
{
    m_key = std::move(entry.m_key);
    m_value = std::move(entry.m_value);
}

void ConfigEntry::SetKey(const std::string& key)
{
    m_key = key;
}

const std::string& ConfigEntry::GetKey() const
{
    return m_key;
}

void ConfigEntry::SetValue(const std::string& value)
{
    m_value = value;
}

const std::string& ConfigEntry::GetValue() const
{
    return m_value;
}

ConfigEntry& ConfigEntry::operator=(ConfigEntry& entry)
{
    m_key = entry.m_key;
    m_value = entry.m_value;
    return *this;
}

bool ConfigEntry::operator==(ConfigEntry& entry)
{
    return (entry.m_key == m_key);
}

bool ConfigEntry::operator!=(ConfigEntry& entry)
{
    return !(entry == *this);
}


} // ns trx