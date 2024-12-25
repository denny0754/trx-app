/* Project Headers */
#include <trx/http/HTTPServer.hpp>

namespace trx::http
{

HTTPServer::HTTPServer(const std::string& bind_address, uint16_t bind_port)
    : m_address(bind_address), m_port(bind_port)
{

}

void HTTPServer::SubscribeRequest(bbeast::http::verb method, const std::string& target_path, const HTTPListenerFnc& target_listener)
{
    m_listeners[method][target_path] = target_listener;
}

bbeast::http::response<bbeast::http::string_body> HTTPServer::HandleRequest(const bbeast::http::request<bbeast::http::string_body>& request)
{
    if(m_listeners.find(request.method()) != m_listeners.end())
    {
        auto& method_listeners = m_listeners.at(request.method());
        if(method_listeners.find(request.target()) != method_listeners.end())
        {
            auto handler = method_listeners.at(request.target());
            return handler(request);
        }
    }
}

} // ns trx::http