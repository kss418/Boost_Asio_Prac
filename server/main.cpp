#include <iostream>
#include <boost/asio.hpp>
#include "Acceptor.hpp"
#include "Thread_Pool.hpp"

const int buf_size = 1000;

int main(){
    Thread_Pool Pool(4);
    boost::asio::io_context io_object;
    Acceptor acceptor(io_object, 3333);
    acceptor.Accept();
    

    return 0;
}