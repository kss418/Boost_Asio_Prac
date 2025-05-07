#pragma once
#include "Session.hpp"
#include <boost/asio.hpp>
#include <unordered_map>
#include <memory>

class Acceptor{
public:
    Acceptor(
        boost::asio::io_context& io_object,
        unsigned short port
    );

    void Accept();
private:
    boost::asio::ip::tcp::endpoint endpoint;
    boost::asio::io_context& io_object;
    boost::asio::ip::tcp::acceptor acceptor;
    std::unordered_map <int32_t, std::shared_ptr<Session>> session_map;
    int32_t count = 0;

    void Handle_Aceept(
        const boost::system::error_code& ec,
        std::shared_ptr<boost::asio::ip::tcp::socket> socket
    );
};