#include <bonefish/rawsocket/tcp_listener.hpp>
#include <bonefish/rawsocket/tcp_connection.hpp>

namespace bonefish {

tcp_listener::tcp_listener(
        boost::asio::io_service& io_service,
        const boost::asio::ip::address& ip_address,
        uint16_t port)
    : rawsocket_listener()
    , m_socket(io_service)
    , m_acceptor(io_service,
            boost::asio::ip::tcp::endpoint(ip_address, port))
{
}

tcp_listener::~tcp_listener()
{
}

void tcp_listener::start_listening()
{
    assert(get_accept_handler());
    set_listening(true);
    async_accept();
}

void tcp_listener::stop_listening()
{
    m_acceptor.cancel();
    set_listening(false);
}

void tcp_listener::handle_accept(const boost::system::error_code &error_code)
{
    if (error_code) {
        return;
    }

    auto connection = std::make_shared<tcp_connection>(std::move(m_socket));
    const auto& accept_handler = get_accept_handler();
    assert(accept_handler);
    accept_handler(connection);

    async_accept();
}

void tcp_listener::async_accept()
{
    m_acceptor.async_accept(m_socket,
            std::bind(&tcp_listener::handle_accept, shared_from_this(),
            std::placeholders::_1));
}

} // namespace bonefish