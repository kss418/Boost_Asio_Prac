#include "Session.hpp"
#include <iostream>
#include <syncstream>

void Session::Handle_Read(
    const boost::system::error_code& ec,
    std::size_t bytes_transferred
){
    if(!ec){
        std::osyncstream out(std::cout);
        out << bytes_transferred << std::endl;
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

}