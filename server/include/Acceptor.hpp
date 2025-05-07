#pragma once
#include <boost/asio.hpp>
#include <vector>
#include <mutex>

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

    void Handle_Aceept(
        const boost::system::error_code& ec,
        std::shared_ptr<boost::asio::ip::tcp::socket> socket
    );
};