#include <iostream>
#include <boost/asio.hpp>
#include "Acceptor.hpp"

const int buf_size = 1000;

int main(){
    boost::asio::io_context io_object;
    Acceptor acceptor(io_object, 3333);
    acceptor.Accept();

    io_object.run();

    return 0;
}