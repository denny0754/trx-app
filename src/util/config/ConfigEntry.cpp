/* Project Headers */
#include <trx/util/config/ConfigEntry.hpp>

/* Standard Headers */
#include <cctype>
#include <algorithm>
#include <sstream>

namespace trx::util
{

ConfigEntry::ConfigEntry(const std::string& key, const std::string& value)
{
    m_key = key;
    m_value = value;
}

ConfigEntry::ConfigEntry(const ConfigEntry& entry)
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

ConfigEntry& ConfigEntry::operator=(ConfigEntry entry)
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

ConfigEntry::operator int()
{
    int c_num = 0;
    try {
        c_num = std::atoi(m_value.c_str());
    } catch(std::exception&) { }

    return c_num;
}

ConfigEntry::operator unsigned int()
{
    return (unsigned int)((int)*this);
}

ConfigEntry::operator float()
{
    float c_num = 0;
    try {
        c_num = static_cast<float>(std::atof(m_value.c_str()));
    } catch(std::exception&) { }

    return c_num;
}

ConfigEntry::operator double()
{
    return (double)((float)*this);
}

ConfigEntry::operator bool()
{
    std::string temp_bool_value = m_value;
    std::transform(temp_bool_value.begin(), temp_bool_value.end(), temp_bool_value.begin(), std::tolower);
    std::istringstream is(temp_bool_value);
    bool b;
    is >> std::boolalpha >> b;
    return b;
}

} // ns trx::util