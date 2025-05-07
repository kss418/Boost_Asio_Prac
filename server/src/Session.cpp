#include "Session.hpp"
#include <iostream>
#include <syncstream>
#include <boost/bind/bind.hpp>

Session::Session(std::shared_ptr<boost::asio::ip::tcp::socket> socket)
    : socket(std::move(socket)), buf(1024){
}

void Session::Read(){
    auto self = shared_from_this();
    socket->async_read_some(
        boost::asio::buffer(buf),
        boost::bind(
            &Session::Handle_Read,
            self,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred
        )
    );
}

void Session::Handle_Read(
    const boost::system::error_code& ec,
    std::size_t bytes_transferred
){
    if(!ec){
        std::osyncstream out(std::cout);
        out << bytes_transferred << std::endl;
        Read();
    }
    else{
        std::osyncstream out(std::cout);
        out << "Error Message : " << ec.what() << std::endl;
    }
}