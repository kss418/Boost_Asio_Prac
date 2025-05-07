#pragma once
#include <boost/asio.hpp>
#include <memory>
#include <functional>
#include <vector>

class Session : public std::enable_shared_from_this<Session> {
public:
    Session(int32_t id, std::shared_ptr<boost::asio::ip::tcp::socket> socket);
    int32_t id;

    void Read();
    void Handle_Read(
        const boost::system::error_code& ec,
        std::size_t bytes_transferred
    );
    void Set_Handle_Close(std::function<void(std::shared_ptr<Session>)> f);

private:
    std::shared_ptr<boost::asio::ip::tcp::socket> socket;
    std::vector<char> buf;

    std::function<void(std::shared_ptr<Session>)> Handle_Close;
};