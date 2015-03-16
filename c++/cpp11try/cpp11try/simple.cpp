//
//  classsimple.cpp
//  cpp11try
//
//  Created by zhangwt on 15/3/7.
//  Copyright (c) 2015年 rocketgofree. All rights reserved.
//

#include "simple.h"

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

bool Simple::showlog_ = false;
int Simple::w = 4;

void Simple::setshowlog(bool show)
{
    showlog_ = show;
}

Simple::Simple(const string& name, int num)
    : name_{name}, num_{num}
{
    if (showlog_)
        cout << "CTOR: " << "('" << name_ << "', " << num_ << ")\n";
}
    
Simple::~Simple()
{
    if (showlog_)
        cout << "DTOR: " << "('" << name_ << "', " << num_ << ")\n";
}
    
int Simple::getNum()
{
    return num_;
}

ostream& operator<<(ostream& os, const Simple& s)
{
    os << "('" << s.name_ << "', " << setw(Simple::w) << s.num_ << ")";
    return os;
}
    
    