#include "Session.hpp"

Session::Session(std::shared_ptr<boost::asio::ip::tcp::socket> socket)
    : socket(std::move(socket)){
}