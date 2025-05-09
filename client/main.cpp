#include <iostream>
#include <boost/asio.hpp>
#include <Session.hpp>
#include <thread>

int main(){
    std::string ip = "127.0.0.1";
    boost::asio::io_context io_object;
    auto work_guard = boost::asio::make_work_guard(io_object);

    std::thread io_thread([&]{
        io_object.run();
    });

    Session session(io_object, ip, 3333);
    session.Connect();

    while(1){
        std::string s; std::cin >> s;
        session.Write(s);
    }

    work_guard.reset();
    io_thread.join();

    return 0;
}