/* Project Headers */
#include <trx/http/SSLCertificate.hpp>

/* External Headers */
#include <openssl/core.h>

/* Standard Headers */
#include <fstream>
#include <sstream>

namespace trx::http
{

SSLCertificate::SSLCertificate()
{
    m_certificateChain = std::string("");
    m_certificateKey = std::string("");
}

SSLCertificate::SSLCertificate(const std::filesystem::path& cert_chain, const std::filesystem::path& cert_key)
{
    std::ifstream ca_fhndl(cert_chain);
    std::ifstream ck_fhndl(cert_key);

    if(ca_fhndl && ck_fhndl)
    {
        // Reading the Certificate Chain
        std::stringstream buffer;
        buffer << ca_fhndl.rdbuf();
        m_certificateChain = buffer.str();

        buffer.str(std::string());

        // Reading the Certificate Private Key
        buffer << ck_fhndl.rdbuf();
        m_certificateKey = buffer.str();

        // Closing certificates files
        ca_fhndl.close();
        ck_fhndl.close();
    }
}

SSLCertificate::SSLCertificate(const std::string& cert_chain, const std::string& cert_key)
{
    m_certificateChain = cert_chain;
    m_certificateKey = cert_key;
}

void SSLCertificate::GenerateCertificate()
{
    
}


} // ns trx::http