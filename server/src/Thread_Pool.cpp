#include "../include/Thread_Pool.hpp"
#include <boost/bind/bind.hpp>

Thread_Pool::Thread_Pool(std::size_t capacity)
    : capacity(capacity) {
    for(size_t idx = 0;idx < capacity;++idx){
        worker_thread.emplace_back(
            boost::bind(
                &Thread_Pool::Work,
                this
            )
        );
    }
};

void Thread_Pool::Work(){
    while(1){
        std::unique_lock<std::mutex> lock(work_lock);
        work_cv.wait(lock, [this](){
            return !work_q.empty() || !run;
        });

        if(!run && work_q.empty()){
            return;
        }

        std::function<void()> current_work = std::move(work_q.front());
        work_q.pop();
        lock.unlock();

        current_work();
    }
}

void Thread_Pool::Enqueue_Work(std::function<void()> work){
    if(!run){
        throw std::runtime_error("Thread Pool 종료");
    }

    {
        std::lock_guard<std::mutex> lock(work_lock);
        work_q.push(std::move(work));
    }
    work_cv.notify_one();
}

Thread_Pool::~Thread_Pool(){
    run = 0;
    work_cv.notify_all();

    for(auto& t : worker_thread){
        t.join();
    }
}