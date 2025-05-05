#include "../include/Session.hpp"
#include <boost/bind/bind.hpp>
#include <iostream>

void Session::Handle_Connect(const boost::system::error_code& ec){
    if(!ec){
        std::cout << "Connected" << std::endl;
    }
    else{
        std::cout << "Error Message : " << ec.what() << std::endl;
    }
}

void Session::Handle_Write(const boost::system::error_code& ec, std::size_t bytes_transffered){
    if(!ec){
        std::cout << "Send " << bytes_transffered << "Bytes" << std::endl;
    }
    else{
        std::cout << "Error Message : " << ec.what() << std::endl;
    }
}