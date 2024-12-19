/*
	`transaction-x` allows users to manage their personal expenses.
	Copyright (C) 2024  Diego Vaccher

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#pragma once

/* Standard Headers */
#include <string>
#include <filesystem>

namespace trx::http
{

class SSLCertificate
{
public:
    SSLCertificate();

    SSLCertificate(const std::string& cert_chain, const std::string& cert_key);

    SSLCertificate(const std::filesystem::path& cert_chain, const std::filesystem::path& cert_key);

    inline const std::string& GetCertificateChain() const
    {
        return m_certificateChain;
    }

    inline const std::string& GetCertificateKey() const
    {
        return m_certificateKey;
    }

    void GenerateCertificate();

    void GenerateKeyPair(const std::filesystem::path& pkey_path, const std::filesystem::path& pubk_path);

private:
    std::string m_certificateChain;

    std::string m_certificateKey;
};

} // ns trx::http