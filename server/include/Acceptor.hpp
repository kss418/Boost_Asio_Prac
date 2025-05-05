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

    boost::asio::ip::tcp::socket socket;
    boost::asio::ip::tcp::endpoint endpoint;
    boost::asio::ip::tcp::acceptor acceptor;
    std::vector <char> buf;

    void Accept();
    void Read();

    void Handle_Aceept(const boost::system::error_code& ec);
    void Handle_Read(const boost::system::error_code& ec, std::size_t bytes_transferred);
};