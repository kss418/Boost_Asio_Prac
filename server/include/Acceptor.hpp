#pragma once
#include "Session.hpp"
#include <boost/asio.hpp>
#include <vector>
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
    std::vector <std::shared_ptr<Session>> session_list;

    void Handle_Aceept(
        const boost::system::error_code& ec,
        std::shared_ptr<boost::asio::ip::tcp::socket> socket
    );
};