#pragma once
#include <boost/asio.hpp>
#include <queue>
#include <functional>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>

class Thread_Pool{
public:
    Thread_Pool(std::size_t capacity);
    ~Thread_Pool();
    void Enqueue_Work(std::function<void()> work);
    
private:
    size_t capacity;
    std::vector<std::thread> worker_thread;
    std::queue<std::function<void()>> work_q;
    std::condition_variable work_cv;
    std::mutex work_lock;
    bool run = 1;

    void Work();
};

