#include <iostream>
using std::cout; using std::endl;

class My_class
{
    public:
        My_class()
        { cout << "default constructor" << endl; }
        ~My_class()
        {}

        My_class(My_class const& other) : a_(other.a_)
        { cout << "copy constructor" << endl; }

        My_class& operator=(My_class const& other)
        { cout << "copy assignment" << endl; a_ = other.a_; }

        int a_;
};

My_class getobj(int i)
{
    My_class local;
    local.a_ = i;
    return local;
}


int main()
{
    My_class obj = getobj(1);
    return 0;
}


