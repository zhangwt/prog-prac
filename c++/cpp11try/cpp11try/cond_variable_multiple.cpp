//
//  cond_variable_multiple.cpp
//  cpp11try
//
//  Created by zhangwt on 15/4/5.
//  Copyright (c) 2015年 zhangwt. All rights reserved.
//

#include "cond_variable_multiple.h"
#include <iostream>
#include <mutex>
#include <thread>

namespace cond_variable_multiple {
    
// notify_one() can only notify threads waiting on the same condition_variable

std::condition_variable cv;
std::mutex mut;
bool ready = false;

void notifying()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    {
        std::lock_guard<std::mutex> lk(mut);
        ready = true;
    }
    std::cout << "notifying...\n";
    cv.notify_one();
}
    
void notified()
{
    std::unique_lock<std::mutex> lk(mut);
    std::cout << "waiting...\n";
    cv.wait(lk, []{return ready;});
    std::cout << "notified\n";
}
    
void cond_variable_multiple_try()
{
    std::thread t1(notifying);
    std::thread t2(notified);
    t1.join();
    t2.join();
}
    
}