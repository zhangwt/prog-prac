//
//  String.cpp
//  cpp11try
//
//  Created by zhangwt on 15/4/6.
//  Copyright (c) 2015年 zhangwt. All rights reserved.
//

#include "String.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

String::String()
    : n_(0), buf_(new char)
{
    buf_[0] = '\0';
}

String::String(const char* s)
    : n_((int)strlen(s)), buf_(new char[n_+1])
{
    memcpy(buf_, s, n_+1);
}

String::String(const String& other)
    : n_(other.n_), buf_(new char[n_+1])
{
    memcpy(buf_, other.buf_, n_+1);
}

String::String(String&& other)
    : n_(other.n_), buf_(other.buf_)
{
    other.n_ = 0;
    other.buf_ = new char;
    other.buf_[0] = '\0';
}

String::~String()
{
    delete[] buf_;
}

String& String::operator=(const String& other)
{
    if (&other == this) return *this;
    delete[] buf_;
    n_ = other.n_;
    buf_ = new char[n_+1];
    memcpy(buf_, other.buf_, n_+1);
    return *this;
}

String& String::operator=(String&& other)
{
    if (&other == this) return *this;
    delete[] buf_;
    n_ = other.n_;
    buf_ = other.buf_;
    other.n_ = 0;
    other.buf_ = new char;
    other.buf_[0] = '\0';
    return *this;
}

String& String::operator+=(const String& other)
{
    *this = *this + other;
    return *this;
}

char& String::operator[](int idx)
{
    return buf_[idx];
}

int String::length()
{
    return n_;
}

String operator+(const String& s1, const String& s2)
{
    String s;
    delete[] s.buf_;
    s.n_ = s1.n_ + s2.n_;
    s.buf_ = new char[s.n_+1];
    memcpy(s.buf_, s1.buf_, s1.n_);
    memcpy(s.buf_+s1.n_, s2.buf_, s2.n_+1);
    return s;
}

bool operator<(const String& s1, const String& s2)
{
    return strcmp(s1.buf_, s2.buf_) < 0;
}

bool operator==(const String& s1, const String& s2)
{
    return strcmp(s1.buf_, s2.buf_) == 0;
}

ostream& operator<<(ostream& out, const String& s)
{
    out << s.buf_;
    return out;
}

bool String::less(const String& s1, const String& s2)
{
    return strcmp(s1.buf_, s2.buf_) < 0;
}

void string_try::string_try()
{
    String s;
    cout << s << "\n";
    
    String s2("hello");
    cout << s2 << "\n";
    
    String s3(" ");
    String s4 = s2 + s3 + String("world");
    cout << s4 << "\n";
    
    s2 += String(" world");
    cout << s2 << "\n";
    cout << s2.length() << "\n";
    
    char c = s2[2];
    cout << c << "\n";
    
    cout << (s < s2) << "\n";
    cout << (String("h") < s2) << "\n";
    cout << (String("world") < s2) << "\n";
    cout << (s2 == s4) << "\n";
    
    String s5(s2);
    cout << s2 << "\n";
    cout << s5 << "\n";
    
    String s6(std::move(s2));
    cout << s2 << "\n";
    cout << s6 << "\n";
    
    String s7("hello");
    s7 = s5;
    cout << s5 << "\n";
    cout << s7 << "\n";
    s7 = std::move(s5);
    cout << s5 << "\n";
    cout << s7 << "\n";
    
    vector<String> vec {"hello", "world"};
    vec.push_back(String("how"));
    vec.emplace_back("are");
    vec.emplace_back("you");
    for (String& s: vec)
    {
        cout << s << ",";
    }
    cout << endl;
    
    //sort(vec.begin(), vec.end(), String::less);
    sort(vec.begin(), vec.end());
    for (String& s: vec)
    {
        cout << s << ",";
    }
    cout << endl;
    
    cout << (string("hello") < string("world")) << "\n";
    vector<string> vec2 {"hello", "world", "you", "are"};
    sort(vec2.begin(), vec2.end());
    for (string& s: vec2)
    {
        cout << s << ",";
    }
    cout << endl;
}
