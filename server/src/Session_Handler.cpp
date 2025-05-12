#include "Session.hpp"
#include <iostream>
#include <syncstream>

void Session::Handle_Read(
    const boost::system::error_code& ec,
    std::size_t bytes_transferred
){
    if(!ec){
        std::osyncstream out(std::cout);
        // out << "Receive " << bytes_transferred << " Bytes" << std::endl;
        Write(std::string(buf.data(), bytes_transferred));
        Read();
    }
    else if(ec == boost::asio::error::eof || ec == boost::asio::error::connection_reset){
        Handle_Close(shared_from_this());
    }
    else{
        std::osyncstream out(std::cout);
        out << "Error Message : " << ec.what() << std::endl;
    }
}

void Session::Handle_Write(
    const boost::system::error_code& ec,
    std::size_t bytes_transferred
){
    if(!ec){
        std::osyncstream out(std::cout);
        // out << "Send " << bytes_transferred << " Bytes" << std::endl;
    }
    else if(ec == boost::asio::error::eof || ec == boost::asio::error::connection_reset){
        Handle_Close(shared_from_this());
    }
    else{
        std::osyncstream out(std::cout);
        out << "Error Message : " << ec.what() << std::endl;
    }
}