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
    template <typename F, typename... Args>
    std::future<typename std::result_of<F(Args...)>::type> Enqueue_Work(
        F&& f, Args&&... args
    );

private:
    size_t capacity;
    std::vector<std::thread> worker_thread;
    std::queue<std::function<void()>> work_q;
    std::condition_variable work_cv;
    std::mutex work_lock;
    bool run = 1;

    void Work();
};

template <typename F, typename... Args>
std::future<typename std::result_of<F(Args...)>::type> Thread_Pool::Enqueue_Work(
    F&& f, Args&&... args
){
    if(!run){
        throw std::runtime_error("Thread Pool 종료");
    }

    using return_type = typename std::result_of<F(Args...)>::type;
    auto work = std::make_shared<std::packaged_task<return_type()>>(
        std::bind(std::forward<F>(f), std::forward<Args>(args)...)
    );

    std::future<return_type> ret = work->get_future();
    {
        std::lock_guard<std::mutex> lock(work_lock);
        work_q.emplace([work](){
            (*work)();
        });
    }
    work_cv.notify_one();

    return ret;
}
