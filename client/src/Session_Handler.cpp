#include "../include/Session.hpp"
#include <iostream>
#include <syncstream>

void Session::Handle_Connect(const boost::system::error_code& ec){
    if(!ec){
        std::osyncstream out(std::cout);
        out << "Connected" << std::endl;
    }
    else{
        std::osyncstream out(std::cout);
        out << "Error Message : " << ec.what() << std::endl;
    }
}

void Session::Handle_Write(const boost::system::error_code& ec, std::size_t bytes_transffered){
    if(!ec){
        std::osyncstream out(std::cout);
        out << "Send " << bytes_transffered << " Bytes" << std::endl;
    }
    else{
        std::osyncstream out(std::cout);
        out << "Error Message : " << ec.what() << std::endl;
    }
}

void Session::Handle_Read(const boost::system::error_code& ec, std::size_t bytes_transffered){
    if(!ec){
        std::osyncstream out(std::cout);
        out << "Receive " << bytes_transffered << " Bytes" << std::endl;
        Read();
    }
    else{
        std::osyncstream out(std::cout);
        out << "Error Message : " << ec.what() << std::endl;
    }
}