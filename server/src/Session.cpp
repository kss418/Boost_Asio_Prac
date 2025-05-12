#include "Session.hpp"
#include <boost/bind/bind.hpp>
#include <iostream>

Session::Session(int32_t id, std::shared_ptr<boost::asio::ip::tcp::socket> socket)
    : id(id), socket(std::move(socket)), buf(1024){
}

void Session::Read(){
    socket->async_read_some(
        boost::asio::buffer(buf),
        [self = shared_from_this()](const boost::system::error_code& ec, std::size_t bytes_transffered){
            self->Handle_Read(ec, bytes_transffered);
        }
    );
}

void Session::Set_Handle_Close(std::function<void(std::shared_ptr<Session>)> f){
    Handle_Close = std::move(f);
}

void Session::Write(const std::string& msg){
    boost::asio::async_write(
        *socket,
        boost::asio::buffer(msg),
        [self = shared_from_this()](const boost::system::error_code& ec, std::size_t bytes_transffered){
            self->Handle_Write(ec, bytes_transffered);
        }
    );
}