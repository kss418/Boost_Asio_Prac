#include <iostream>
#include <boost/asio.hpp>
#include "Acceptor.hpp"
#include "Thread_Pool.hpp"

const int buf_size = 1000;
void work(int id){
    printf("%d start \n", id);
}

int main(){
    Thread_Pool Pool(3);
    for(int i = 0;i < 10;++i){
        Pool.Enqueue_Work([i](){
            work(i);
        });
    }

    return 0;
}