#pragma once
#include <boost/asio.hpp>
#include <memory>
#include <vector>

class Session : public std::enable_shared_from_this<Session> {
public:
    Session(std::shared_ptr<boost::asio::ip::tcp::socket> socket);
    void Read();
    void Handle_Read(
        const boost::system::error_code& ec,
        std::size_t bytes_transferred
    );

private:
    std::shared_ptr<boost::asio::ip::tcp::socket> socket;
    std::vector<char> buf;
};