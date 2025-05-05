#include "../include/Session.hpp"
#include <boost/bind/bind.hpp>
#include <iostream>

Session::Session(
    boost::asio::io_context& io_object,
    const std::string& ip, 
    unsigned short port
) : socket(io_object), endpoint(boost::asio::ip::make_address(ip), port) {}

void Session::Write(const std::string& msg){
    boost::asio::async_write(
        socket,
        boost::asio::buffer(msg),
        boost::bind(&Session::Handle_Write,
            this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred
        )
    );
}

void Session::Connect(){
    socket.async_connect(endpoint,
        boost::bind(&Session::Handle_Connect,
            this,
            boost::asio::placeholders::error
        )
    );
}

