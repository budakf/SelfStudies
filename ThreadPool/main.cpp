#include <iostream>
#include <chrono>
#include "threadpool.h"

int task(int c){
    std::cout << "working thread: " << std::this_thread::get_id() << "\tcount: " << c++ << std::endl;
    return c;
}

void anotherTask(std::string s){
    std::cout << "working thread: " << std::this_thread::get_id() << "\tstring: " << s << std::endl;
}

int main(){

    ThreadPool pool{};
    pool.setWorkers(4);

    std::future<int> returnValue0 = pool.pushTask(&task, 0);
    std::future<void> returnValue1 = pool.pushTask(&anotherTask, "Bir");
    std::future<void> returnValue2 = pool.pushTask(&anotherTask, "Iki");
    std::future<int> returnValue3 = pool.pushTask(&task, 3);

    std::this_thread::sleep_for(std::chrono::seconds(6));
    std::future<int> returnValue4 = pool.pushTask(&task, 4);
    std::this_thread::sleep_for(std::chrono::seconds(3));

    std::cout<<"returnValue4: " << returnValue4.get()<<std::endl;

    return 0;
}
