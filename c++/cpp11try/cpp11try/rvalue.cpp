//
//  rvalue.cpp
//  cpp11try
//
//  Created by zhangwt on 15/4/5.
//  Copyright (c) 2015年 zhangwt. All rights reserved.
//

#include "rvalue.h"
#include "simple.h"
#include <iostream>

namespace rvalue {
    void foo(Simple&& s)
    {
        std::cout << s << "\n";
    };
    
    void rvalue_try()
    {
        Simple s("simple", 1);
        // foo(s); // Wrong: no matching function
        foo(std::move(s));
        foo(Simple("simple", 1));
    }
}
