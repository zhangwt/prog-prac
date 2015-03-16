//
//  cond_variable_spsc_v2.cpp
//  cpp11try
//
//  Created by zhangwt on 15/3/8.
//  Copyright (c) 2015年 rocketgofree. All rights reserved.
//

#include "cond_variable_spsc_v2.h"
#include "simple.h"

#include <iostream>
#include <iomanip>
#include <condition_variable>
#include <thread>
#include <mutex>
#include <vector>
#include <string>
#include <chrono>


namespace cond_variable_spsc_v2 {
    
    
std::mutex g_mut;
std::condition_variable g_cv; // ?? seperate or one global cv for put() and get()

std::vector<Simple> buf(10, {"", 0});
int entries;
int head, tail; // head -> first element, tail -> one past the last element

int cnt;

void sleepp(int ms)
{
    if (ms <=  0) return;
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

Simple fetchdata()
{
    sleepp(10);
    return Simple{"", cnt++};
}

void processdata(Simple& item)
{
    sleepp(20);
}

void producer()
{
    while (true) {
        Simple item = fetchdata();
        
        std::unique_lock<std::mutex> lk(g_mut);
        g_cv.wait(lk, []{return entries < buf.size();});
        lk.unlock();
        
        buf[tail] = item;
        tail = (tail+1) % buf.size();
        {
            std::lock_guard<mutex> mlk(g_mut);
            entries += 1;
            std::cout << "put(): " << buf[(tail+buf.size()-1)%buf.size()]
                << " in " << std::setw(Simple::w) << ((tail+buf.size()-1)%buf.size())
                << ", entries: " << std::setw(Simple::w) << entries << " -->\n";
        }
        
        g_cv.notify_one();
        
        if (item.getNum() == 19) break;
    }
}

void consumer()
{
    while (true) {
        std::unique_lock<std::mutex> lk(g_mut);
        g_cv.wait(lk, []{return entries > 0;});
        lk.unlock();
        
        Simple item = buf[head];
        head = (head+1) % buf.size();
        {
            std::lock_guard<mutex> mlk(g_mut);
            entries -= 1;
            std::cout << "get(): " << buf[(head+buf.size()-1)%buf.size()]
                << " in " << std::setw(Simple::w) << ((head+buf.size()-1)%buf.size())
                << ", entries: " << std::setw(Simple::w) << entries << " o\n";
        }
        
        g_cv.notify_one();
        
        if (item.getNum() == 19) break;
        processdata(item);
    }
}

int spsc_v2_try()
{
    cout << __func__ << "():\n\n";
    
    std::thread p(producer);
    std::thread c(consumer);
    
    p.join();
    c.join();
    
    return 0;
}

    
}