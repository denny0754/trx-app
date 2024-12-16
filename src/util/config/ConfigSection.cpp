/* Project Headers */
#include <trx/util/config/ConfigSection.hpp>

namespace trx::util
{

ConfigSection::ConfigSection(const std::string& section_key, std::initializer_list<ConfigEntry> entries)
{
    m_sectionKey = section_key;
    for(auto entry : entries)
    {
        m_entries[entry.GetKey()] = ConfigEntry(entry);   
    }
}

const std::string& ConfigSection::GetKey() const
{
    return m_sectionKey;
}

ConfigEntry& ConfigSection::get(std::string key, ConfigEntry fallback_entry)
{
    if(m_entries.find(key) == m_entries.end())
    {
        m_entries[key] = ConfigEntry(fallback_entry);
    }
    return m_entries.at(key);
}

ConfigEntry& ConfigSection::at(const std::string& entry_key)
{
    return m_entries.at(entry_key);
}

ConfigSection::iterator ConfigSection::find(const std::string& entry_key)
{
    return m_entries.find(entry_key);
}

ConfigSection::iterator ConfigSection::begin()
{
    return m_entries.begin();
}

ConfigSection::iterator ConfigSection::begin(size_t bucket)
{
    return m_entries.begin(bucket);
}

ConfigSection::const_iterator ConfigSection::begin() const
{
    return m_entries.begin();
}

ConfigSection::iterator ConfigSection::end()
{
    return m_entries.end();
}

ConfigSection::const_iterator ConfigSection::end() const
{
    return m_entries.end();
}

ConfigSection::const_iterator ConfigSection::cbegin() const
{
    return m_entries.cbegin();
}

ConfigSection::const_iterator ConfigSection::cend() const
{
    return m_entries.cend();
}

void ConfigSection::emplace(const ConfigEntry& entry)
{
    if(m_entries.find(entry.GetKey()) != m_entries.end())
    {
        m_entries.at(entry.GetKey()) = entry;
    }
    else
    {
        m_entries[entry.GetKey()] = entry;
    }
}


ConfigEntry& ConfigSection::operator[](const std::string& entry_key)
{
    if(m_entries.find(entry_key) == m_entries.end())
    {
        m_entries[entry_key] = ConfigEntry();
    }
    return m_entries.at(entry_key);
}

} // ns trx::util