//
//  classsimple.h
//  cpp11try
//
//  Created by zhangwt on 15/3/7.
//  Copyright (c) 2015 rocketgofree. All rights reserved.
//

#ifndef __cpp11try__simple__
#define __cpp11try__simple__

#include <iostream>
#include <string>
using namespace std;

class Simple
{
public:
    Simple(string name, int num);
    ~Simple();
    
    int getNum();
    
    static void setshowlog(bool show);
    static int w;
        
    friend ostream& operator<<(ostream& os, const Simple& s);
    
private:
    string name_;
    int num_;
    static bool showlog_;
};

#endif /* defined(__cpp11try__simple__) */
