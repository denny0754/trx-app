/* Project Headers */
#include <trx/utils/config/ConfigIO.hpp>

/* Standard Headers */
#include <sstream>
#include <string>
#include <fstream>

namespace trx
{

bool ConfigIO::IsEntry(const std::string& buf)
{
    //!TODO: Regex matching for entries
    return false;
}

bool ConfigIO::IsSection(const std::string& buf)
{
    //!TODO: Regex matching for sections
    return false;
}

bool ConfigIO::IsComment(const std::string& buf)
{
    //!TODO: Regex matching for comments
    return false;
}

ConfigEntry ConfigIO::ParseEntry(const std::string& entry_str)
{
    ConfigEntry entry = ConfigEntry();

    std::string entry_key = std::string();
    std::string entry_value = std::string();

    //!TODO: Remove spaces before and after the '=' delimiter.
    //!TODO: Remove spaces on the key value.
    entry_key = entry_str.substr(0, entry_str.find_first_of('='));
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
    //! TODO: Open the file and write `config_stream` to it in truncate mode. 
}

} // ns trx