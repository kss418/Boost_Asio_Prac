#include "Acceptor.hpp"
#include "Session.hpp"

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
    acceptor.async_accept(*socket, 
        boost::bind(
            &Acceptor::Handle_Aceept, 
            this, 
            boost::asio::placeholders::error,
            socket
        )
    );
}

void Acceptor::Handle_Aceept(
    const boost::system::error_code& ec,
    std::shared_ptr<boost::asio::ip::tcp::socket> socket
){
    if(!ec){
        std::cout << "연결 완료" << std::endl;
        Session session(std::move(socket));
        Accept();
    }
    else{
        std::cout << "Error Message : " << ec.what() << std::endl;
    }
}


