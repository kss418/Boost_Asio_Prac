#include "Session.hpp"
#include <boost/bind/bind.hpp>

Session::Session(int32_t id, std::shared_ptr<boost::asio::ip::tcp::socket> socket)
    : id(id), socket(std::move(socket)), buf(1024){
}

void Session::Read(){
    auto self = shared_from_this();
    socket->async_read_some(
        boost::asio::buffer(buf),
        boost::bind(
            &Session::Handle_Read,
            self,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred
        )
    );
}

void Session::Set_Handle_Close(std::function<void(std::shared_ptr<Session>)> f){
    Handle_Close = std::move(f);
}

void Session::Write(const std::string& msg){

}