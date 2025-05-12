#include "Acceptor.hpp"
#include <iostream>
#include <boost/bind/bind.hpp>
#include <syncstream>

Acceptor::Acceptor(
    boost::asio::io_context& io_object,
    unsigned short port
) : 
    io_object(io_object),
    endpoint(boost::asio::ip::address_v4::any(), port),
    acceptor(io_object, endpoint) { 
        acceptor.listen();
}

void Acceptor::Accept(){
    auto socket = std::make_shared<boost::asio::ip::tcp::socket>(io_object);
    acceptor.async_accept(
        *socket, 
        [this, socket](const boost::system::error_code& ec){
            this->Handle_Aceept(ec, socket);
        }
    );
}

void Acceptor::Handle_Aceept(
    const boost::system::error_code& ec,
    std::shared_ptr<boost::asio::ip::tcp::socket> socket
){
    if(!ec){
        ++count;
        auto session = std::make_shared<Session>(count, std::move(socket));

        {
            std::lock_guard<std::mutex> lock(session_map_mutex);
            session_map[session->id] = session;
        }

        std::osyncstream out(std::cout);
        out << "연결 완료, id = " << session->id << std::endl;
        out << "현재 접속 " << session_map.size() << std::endl;

        session->Set_Handle_Close(
            [this](std::shared_ptr<Session> s){
                std::size_t map_size;
                {
                    std::lock_guard<std::mutex> lock(session_map_mutex);
                    auto it = session_map.find(s->id);
                    if(it != session_map.end()) session_map.erase(it);
                    map_size = session_map.size();
                }       

                std::osyncstream out(std::cout);
                out << "연결 종료, id = " << s->id << std::endl;
                out << "현재 접속 " << map_size << std::endl;
            }
        );

        session->Read();
        Accept();
    }
    else{
        std::osyncstream out(std::cout);
        out << "Error Message : " << ec.what() << std::endl;
    }
}


