//
//  String.h
//  cpp11try
//
//  Created by zhangwt on 15/4/6.
//  Copyright (c) 2015年 zhangwt. All rights reserved.
//

#ifndef __cpp11try__String__
#define __cpp11try__String__

#include <iostream>

class String
{
public:
    String();
    String(const char*);
    String(const String&);
    String(String&&);
    String& operator=(const String&);
    String& operator=(String&&);
    ~String();
    
    char& operator[](int idx);
    int length();
    
    String& operator+=(const String&);
    
    friend bool operator<(const String&, const String&); //sort() without specifying comparator
    friend bool operator==(const String&, const String&);
    friend String operator+(const String&, const String&);
    
    friend std::ostream& operator<<(std::ostream&, const String& s);
    static bool less(const String&, const String&);
    
private:
    int n_;
    char* buf_;
};

namespace string_try {
    void string_try();
}

#endif /* defined(__cpp11try__String__) */
