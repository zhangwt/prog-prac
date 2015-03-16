//
//  main.cpp
//  cpp11try
//
//  Created by zhangwt on 15/3/6.
//  Copyright (c) 2015年 rocketgofree. All rights reserved.
//

#include "unique_pointer.h"
#include "shared_pointer.h"
#include "cond_variable_spsc.h"
#include "cond_variable_spsc_v2.h"

#include <iostream>
using namespace std;

int main(int argc, const char * argv[]) {
    
    //unique_pointer_try();
    
    //shared_pointer_try();
    
    //cond_variable_spsc::spsc_try();
    
    cond_variable_spsc_v2::spsc_v2_try();
    
    return 0;
}
