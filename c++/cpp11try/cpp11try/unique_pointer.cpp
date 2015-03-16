//
//  unique_pointer.cpp
//  cpp11try
//
//  Created by zhangwt on 15/3/6.
//  Copyright (c) 2015 rocketgofree. All rights reserved.
//

#include "unique_pointer.h"
#include "simple.h"
#include "util.h"

#include <iostream>
#include <memory>
using namespace std;


int unique_pointer_try()
{
    Simple::setshowlog(true);
    print_sec_header();
    
    unique_ptr<int> up{new int{3}};
    cout << "*up = " << *up << endl;
    
    //up = new int{4}; // no viable overloaded '='
    
    //unique_ptr<int> up2{up}; // call to implicitly-deleted copy constructor of 'unique_prt<int>'
    unique_ptr<int> up3{nullptr};
    //up3 = up; // copy assignment operator is implicityly deleted
    
    unique_ptr<int> up4{move(up)};
    cout << "*up4 = " << *up4 << endl;
    //cout << "*up = " << *up << endl; // EXC_BAD_ACCESS
    cout << endl;
    
    unique_ptr<int> up5{nullptr};
    up5 = move(up);
    //cout << "*up5 = " << *up5 << endl; // EXC_BAD_ACCESS
    
    
    unique_ptr<Simple> up6{new Simple{"up6", 6}}; // CTOR: 6
    unique_ptr<Simple> up7{new Simple{"up7", 7}}; // CTOR: 7
    up7 = move(up6); // DTOR: 7. The object referenced by up7 (Simple{7}) is destructed, and up7 points to Simple{6},
                     // up6 points to NULL
    
    cout << "*up7 = " << *up7 << endl; // up7: 6
    //cout << "up6: " << *up6 << endl; // EXC_BAD_ACCESS(code=1, address=0), 'address=0' might mean NULL address.
    
    return 0;
}
// DTOR: 6