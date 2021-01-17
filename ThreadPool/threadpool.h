#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <mutex>
#include <deque>
#include <thread>
#include <vector>
#include <future>
#include <memory>
#include <iostream>
#include <condition_variable>


class ThreadPool{

    using Pool = std::vector<std::unique_ptr<std::thread>>;
    using TaskQueue = std::deque<std::function<void()>>;

    Pool mPool;
    TaskQueue mTasks;
    std::mutex mMutex;
    std::atomic<bool> mIsActive{true};
    std::condition_variable mConditionVar;

    void run();
    void join();

public:
    ThreadPool();
    ThreadPool(unsigned int pPoolSize);
    virtual ~ThreadPool();
    void setWorkers(unsigned int pPoolSize = 1);

    template<class Function, class ...Arguments>
    auto pushTask(Function && f, Arguments &&... args);
};


ThreadPool::ThreadPool(){

}

ThreadPool::ThreadPool(unsigned int pPoolSize){
    this->setWorkers(pPoolSize);
}

ThreadPool::~ThreadPool(){
    mIsActive = false;
    mConditionVar.notify_all();
    join();
}

void ThreadPool::join(){
    for(auto& worker : mPool){
        worker->join();
    }
}

void ThreadPool::setWorkers(unsigned int pPoolSize){
    mPool.resize(pPoolSize);
    for(unsigned int i = 0; i<pPoolSize; ++i ){
        mPool.emplace_back( std::make_unique<std::thread>(&ThreadPool::run, this) );
    }
}

void ThreadPool::run(){
    std::function<void()> task;
    while(mIsActive){
        {
            std::unique_lock<std::mutex> lock{mMutex};
//            std::unique_lock lock{mMutex};  valid for C++17

            mConditionVar.wait(lock, [=]{ return !mTasks.empty() || !mIsActive; } );
            if(!mIsActive){
                break;
            }
            task = std::move(mTasks.front());
            mTasks.pop_front();
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        task();
    }
}

template<class Function, class ...Arguments>
auto ThreadPool::pushTask(Function && f, Arguments &&... arguments){

    using returnType = typename std::result_of<Function(Arguments...)>::type;
    auto packagedTask = std::make_shared< std::packaged_task<returnType()> >(
                std::bind( std::forward<Function>(f), std::forward<Arguments>(arguments)... ) );

// C++20
//    auto packagedTask = std::make_shared< std::packaged_task<returnType()> >(
//                [func = std::forward<Function>(f),
//                 ...args = std::forward<Arguments>(arguments)]{ return func(args); } );

    mTasks.emplace_back([packagedTask]{(*packagedTask)();});
    std::future<returnType> returnValue = packagedTask->get_future();

    mConditionVar.notify_one();

    return returnValue;
}
#endif // THREADPOOL_H
