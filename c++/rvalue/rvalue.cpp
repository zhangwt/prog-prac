#include <iostream>
using std::cout; using std::endl;

int foo(int& v)
{
    return v;
}

int main()
{
    int a = 10;

    //int &b = foo(a); // wrong, lvalue reference cannot refer to rvalue
    int &&b = foo(a);

    foo(b);
    int &c = b; // rvalue reference can be converted to lvalue reference

    //int &&d = a; // wrong
    int &&d = std::move(a);
    cout << "d: " << d << ", a: " << a << endl;
}
