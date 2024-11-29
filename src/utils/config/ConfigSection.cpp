/* Project Headers */
#include <trx/utils/config/ConfigSection.hpp>

namespace trx
{

ConfigSection::ConfigSection(const std::string& section_key, const std::initializer_list<ConfigEntry>& entries = { })
{
    m_sectionKey = section_key;
    m_entries = ConfigEntryMap(entries.begin(), entries.end());
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

ConfigEntry& ConfigSection::operator[](const std::string& entry_key)
{
    if(m_entries.find(entry_key) == m_entries.end())
    {
        m_entries[entry_key] = ConfigEntry();
    }
    return m_entries.at(entry_key);
}

} // ns trx