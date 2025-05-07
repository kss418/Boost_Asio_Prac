#pragma once
#include <boost/asio.hpp>
#include <memory>

class Session{
public:
    Session(std::shared_ptr<boost::asio::ip::tcp::socket> socket);
private:
    std::shared_ptr<boost::asio::ip::tcp::socket> socket;
};