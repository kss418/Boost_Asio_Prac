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
        Read();
    }
    else{
        std::osyncstream out(std::cout);
        out << "Error Message : " << ec.what() << std::endl;
    }
}

void Session::Handle_Read(const boost::system::error_code& ec, std::size_t bytes_transffered){
    if(!ec){
        std::osyncstream out(std::cout);
        out << std::string(buf.data(), bytes_transffered) << std::endl;
        Read();
    }
    else{
        std::osyncstream out(std::cout);
        out << "Error Message : " << ec.what() << std::endl;
    }
}