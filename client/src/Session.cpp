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

void Session::Read(){
    socket.async_read_some(
        boost::asio::buffer(buf),
        boost::bind(
            &Session::Handle_Read,
            this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred
        )
    );
}

