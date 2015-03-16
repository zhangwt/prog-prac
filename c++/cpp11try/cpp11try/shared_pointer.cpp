//
//  shared_pointer.cpp
//  cpp11try
//
//  Created by zhangwt on 15/3/7.
//  Copyright (c) 2015 rocketgofree. All rights reserved.
//

#include "shared_pointer.h"
#include "simple.h"
#include "util.h"

#include <iostream>
#include <string>
#include <memory>
using namespace std;

template <class T>
void print_sharedptr_info(const string& name, const shared_ptr<T>& sp)
{
    cout << "*" << name << " = " << *sp << ", "
         << name << ".get() = " << sp.get() << ", "
         << name << ".use_count = " << sp.use_count() << "\n";
}


int shared_pointer_try()
{
    Simple::setshowlog(true);
    print_sec_header();
    
    shared_ptr<Simple> sp{new Simple{"sp", 0}};
    print_sharedptr_info("sp", sp);
    
    shared_ptr<Simple> sp2 = make_shared<Simple>("sp2", 2);
    print_sharedptr_info("sp2", sp2);
    
    shared_ptr<Simple> sp3 = sp2;
    print_sharedptr_info("sp3", sp3);
    print_sharedptr_info("sp2", sp2);
    
    
    return 0;
}
