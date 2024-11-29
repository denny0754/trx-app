/* Project Headers */
#include <trx/utils/config/ConfigReader.hpp>

/* Standard Headers */
#include <fstream>

namespace trx
{
    
ConfigReader::ConfigReader(const std::filesystem::path& file)
{
    m_fileBuffer = std::ifstream(file);
}

ConfigReader::~ConfigReader()
{
    if(m_fileBuffer)
    {
        m_fileBuffer.close();
    }
}

const std::istream& ConfigReader::ReadLine(std::string& sbuf)
{
    return std::getline(m_buffer, sbuf);
}

} // ns trx