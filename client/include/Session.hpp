#pragma once
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>

class Session{
public:
    Session(
        boost::asio::io_context& io_object,
        const std::string& ip,
        unsigned short port
    );

    void Connect();
    void Write(const std::string& msg);
    void Read();

private:
    boost::asio::ip::tcp::socket socket;
    boost::asio::ip::tcp::endpoint endpoint;

    void Handle_Connect(const boost::system::error_code& ec);
    void Handle_Write(const boost::system::error_code& ec, std::size_t bytes_transffered);
};