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
    if(i > 100)
    {
        My_class local;
        local.a_ = 100;
        return local;
    }
    else 
    {
        My_class local2;
        local2.a_ = 1;
        return local2;
    }
}


int main()
{
    My_class obj = getobj(1);
    return 0;
}
