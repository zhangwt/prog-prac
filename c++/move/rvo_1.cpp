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

void getobj(My_class* _hidden, int i)
{
    My_class local;
    local.a_ = i;
    *_hidden = local;
}


int main()
{
    My_class _hidden;
    getobj(&_hidden, 1);

    My_class obj = _hidden;
    return 0;
}



