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

/* External Headers */
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/strand.hpp>

/* Standard Headers */
#include <string>
#include <unordered_map>
#include <functional>

/* Namespaces Abbreviations */
namespace bbeast = boost::beast;
namespace basio = boost::asio;

namespace trx::http
{

class HTTPServer
{
public:
    using HTTPListenerFnc = std::function<bbeast::http::response<bbeast::http::string_body>(const bbeast::http::request<bbeast::http::string_body>)>;

    HTTPServer(const std::string& bind_address, uint16_t bind_port);

    void SubscribeRequest(bbeast::http::verb method, const std::string& target_path, const HTTPListenerFnc& target_listener);

protected:
    bbeast::http::response<bbeast::http::string_body> HandleRequest(const bbeast::http::request<bbeast::http::string_body>& request);

private:
    std::string m_address;

    uint16_t m_port;

    std::unordered_map<bbeast::http::verb, std::unordered_map<std::string, HTTPListenerFnc>> m_listeners;
};

} // ns trx::http