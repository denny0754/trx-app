/* Project Headers */
#include <trx/util/config/Config.hpp>

namespace trx::util
{

Config::Config(std::initializer_list<ConfigSection> sections)
{
    for(auto section : sections)
    {
        m_sections[section.GetKey()] = section;
    }
}

bool Config::exist(const std::string& section_key)
{
    return m_sections.find(section_key) != m_sections.end();
}

ConfigSection& Config::get(std::string key, const ConfigSection& fallback_section)
{
    if(m_sections.find(key) == m_sections.end())
    {
        m_sections[key] = ConfigSection(fallback_section);
    }
    return m_sections.at(key);
}

ConfigSection& Config::at(const std::string& section_key)
{
    return m_sections.at(section_key);
}

Config::iterator Config::find(const std::string& section_key)
{
    return m_sections.find(section_key);
}

Config::iterator Config::begin()
{
    return m_sections.begin();
}

Config::iterator Config::begin(size_t i)
{
    return m_sections.begin(i);
}

Config::const_iterator Config::begin() const
{
        return m_sections.begin();
}

Config::iterator Config::end()
{
    return m_sections.end();
}

Config::const_iterator Config::end() const
{
    return m_sections.end();
}

Config::const_iterator Config::cbegin() const
{
    return m_sections.cbegin();
}

Config::const_iterator Config::cend() const
{
    return m_sections.cend();
}

ConfigSection& Config::operator[](const std::string& section_key)
{
    if(m_sections.find(section_key) == m_sections.end())
    {
        m_sections[section_key] = ConfigSection();
    }
    return m_sections.at(section_key);
}

} // ns trx::util