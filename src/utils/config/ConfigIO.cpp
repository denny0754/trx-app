/* Project Headers */
#include <trx/utils/config/ConfigIO.hpp>

/* External Headers */
#include <boost/regex.hpp>

/* Standard Headers */
#include <sstream>
#include <string>
#include <fstream>

namespace trx
{

const static boost::regex SECTION_RGX("\[[a-zA-Z0-9-_]+\]");
const static boost::regex KEYVALUE_PAIR_RGX("([A-Za-z0-9_]+)\s*=\s*(['\"])* ([A - Za - z0 - 9_]).*\2 + ");
const static boost::regex COMMENT_RGX("^\s*#.*");

bool ConfigIO::IsEntry(const std::string& buf)
{
    return boost::regex_match(buf, KEYVALUE_PAIR_RGX);
}

bool ConfigIO::IsSection(const std::string& buf)
{
    return boost::regex_match(buf, SECTION_RGX);
}

bool ConfigIO::IsComment(const std::string& buf)
{
    return boost::regex_match(buf, COMMENT_RGX);
}

ConfigEntry ConfigIO::ParseEntry(const std::string& entry_str)
{
    ConfigEntry entry = ConfigEntry();

    std::string entry_key = std::string();
    std::string entry_value = std::string();

    entry_key = entry_str.substr(0, entry_str.find_first_of('='));
    entry_key.erase(std::remove(entry_key.begin(), entry_key.end(), ' '), entry_key.end());
    
    entry_value = entry_str.substr(entry_str.find_first_of('=') + 1);

    entry.SetKey(entry_key);
    entry.SetValue(entry_value);    
    return entry;
}

Config ConfigIO::ParseFile(const std::filesystem::path& file)
{
    std::ifstream file_hndl = std::ifstream(file);
    if(!file_hndl)
    {
        return ConfigIO::ParseString("");
    }

    std::stringstream sbuf = std::stringstream();
    sbuf << file_hndl.rdbuf();
    file_hndl.close();

    return ConfigIO::ParseString(sbuf.str());
}

Config ConfigIO::ParseString(const std::string& buf)
{
    Config config = Config();
    if(buf.length() == 0)
    {
        return config;
    }

    std::stringstream sbuf = std::stringstream();
    sbuf << buf;
    std::string line_buf = std::string("");

    std::string curr_section_key = std::string("");

    while(std::getline(sbuf, line_buf))
    {
        if(!ConfigIO::IsComment(line_buf))
        {
            if(ConfigIO::IsSection(line_buf))
            {
                curr_section_key = line_buf.substr(
                    line_buf.find_first_of('[') + 1,
                    line_buf.find_first_of(']') - 1
                );
                if(config.find(curr_section_key) == config.end())
                {
                    config[curr_section_key] = ConfigSection();
                }
            }
            else if(ConfigIO::IsEntry(line_buf))
            {
                ConfigEntry entry = ConfigIO::ParseEntry(line_buf);
                if(config.find(curr_section_key) != config.end())
                {
                    config.at(curr_section_key).emplace(entry);
                }
            }
        }
    }
}

std::string ConfigIO::ConvertToString(const Config& config)
{
    std::stringstream config_stream = std::stringstream("");

    for(auto [section_key, section] : config)
    {
        config_stream << "[" << section_key << "]\n";

        for(auto& [_section_key, entry] : section)
        {
            config_stream << entry.GetKey() << "=" << entry.GetValue() << "\n";
        }
    }
    return config_stream.str();
}

void ConfigIO::WriteFile(const Config& config, const std::filesystem::path& file)
{
    std::string config_stream = ConfigIO::ConvertToString(config);
    std::ofstream file_hndl(file, std::ios::out | std::ios::ate);
    if(!file_hndl)
    {
        return;
    }

    file_hndl << config_stream;

    file_hndl.close();
}

} // ns trx