#include <iostream>
#include <memory>
using std::cout; using std::endl;

class My_class 
{
    public:
        My_class(unsigned n = 0) : n_(n), ele_(n ? new int[n] : nullptr)
        {}
        ~My_class()
        { if(n_) delete[] ele_; } 

        My_class(My_class const& other) : n_(other.n_), ele_(new int[other.n_])
        { 
            std::uninitialized_copy(other.ele_, other.ele_ + other.n_, ele_); 
        }
#ifdef MOVE
        My_class(My_class&& other) : n_(other.n_), ele_(other.ele_)
        {
            other.n_ = 0; other.ele_ = nullptr;
        }
#endif

        My_class& operator=(My_class const& other)
        {
            if(&other != this)
            {
                delete[] ele_;
                n_ = other.n_;
                ele_ = new int[other.n_];
                std::uninitialized_copy(other.ele_, other.ele_ + other.n_, ele_); 
            }
                
        }
        My_class& operator=(My_class&& other)
        {
            std::swap(n_, other.n_);
            std::swap(ele_, other.ele_);
            // n_ = other.n_; ele_ = other.ele_; other.n_ = 0; other.ele_ = std::nullptr;
        }

    private:
        unsigned n_;
        int* ele_;
};

My_class getobj(int i)
{
    if(i >= 100)
    {
        My_class local(1000000);
        return local;
    }
    else
    {
        My_class local2(1000000);
        return local2;
    }

}

int main(int argc, char** argv)
{
    for(int i = 0; i < 1000; ++i)
    {
        My_class obj = getobj(1);
    }
    return 0;
}
