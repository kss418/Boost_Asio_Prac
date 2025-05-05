#include <iostream>
#include <boost/asio.hpp>
#include <Session.hpp>

int main(){
    std::string ip = "127.0.0.1";
    boost::asio::io_context io_object;
    Session session(io_object, ip, 3333);

    session.Connect();
    io_object.run();
    while(1){
        std::string s; std::cin >> s;
        session.Write(s);
    }

    return 0;
}