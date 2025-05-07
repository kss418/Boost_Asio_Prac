#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <iostream>
#include "Acceptor.hpp"

Acceptor::Acceptor(
    boost::asio::io_context& io_object,
    unsigned short port
) : 
    socket(io_object), 
    endpoint(boost::asio::ip::address_v4::any(), port),
    acceptor(io_object, endpoint),
    buf(1024) { 
        acceptor.listen();
}

void Acceptor::Accept(){
    acceptor.async_accept(socket, boost::bind(
        &Acceptor::Handle_Aceept, 
        this, 
        boost::asio::placeholders::error)
    );
}

void Acceptor::Read(){
    socket.async_read_some(
        boost::asio::buffer(buf),
        boost::bind(&Acceptor::Handle_Read, 
            this, 
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred
        )
    );
}


