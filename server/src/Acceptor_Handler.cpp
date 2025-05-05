#include <iostream>
#include "Acceptor.hpp"

void Acceptor::Handle_Aceept(const boost::system::error_code& ec){
    if(!ec){
        std::cout << "연결 완료" << std::endl;
        Read();
    }
    else{
        std::cout << "Error Message : " << ec.what() << std::endl;
    }
}

void Acceptor::Handle_Read(const boost::system::error_code& ec, std::size_t bytes_transferred){
    if(!ec){
        std::cout << bytes_transferred << std::endl;
        Read();
    }
    else{
        std::cout << "Error Message : " << ec.what() << std::endl;
    }
}
