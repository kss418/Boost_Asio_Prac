#include "../include/Session.hpp"
#include <iostream>

Session::Session(
    boost::asio::io_context& io_object,
    const std::string& ip, 
    unsigned short port
) 
    : socket(io_object), buf(1024),
    endpoint(boost::asio::ip::make_address(ip), port) {    
}

void Session::Write(const std::string& msg){
    boost::asio::async_write(
        socket,
        boost::asio::buffer(msg),
        [this](const boost::system::error_code& ec, std::size_t bytes_transferred){
            Handle_Write(ec, bytes_transferred);
        }
    );
}

void Session::Connect(){
    socket.async_connect(
        endpoint,
        [this](const boost::system::error_code& ec){
            Handle_Connect(ec);
        }
    );
}

void Session::Read(){
    socket.async_read_some(
        boost::asio::buffer(buf),
        [this](const boost::system::error_code& ec, std::size_t bytes_transferred){
            Handle_Read(ec, bytes_transferred);
        }
    );
}

