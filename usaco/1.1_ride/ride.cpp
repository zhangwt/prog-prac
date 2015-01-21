/*
ID: zhangwt1
PROG: ride
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
using std::ifstream; using std::ofstream;
using std::string; using std::endl;

int calc(const string& s)
{
    int prod = 1;
    for(int i = 0; i < s.size(); ++i)
    {
        // (a*b)%n == ((a%n)*b)%n
        // (a*b)%n == ((a%n)*(b%n))%n
        // (a*b)%n != (a%n)*(b%n)
        prod = (prod*(s[i] - 'A' + 1)) % 47;
    }
    return prod;
}

int main()
{
    ifstream fin {"ride.in"};
    ofstream fout {"ride.out"};

    string s1, s2;
    fin >> s1 >> s2;

    if(calc(s1) == calc(s2))
    {
        fout << "GO" << endl;
    }
    else
    {
        fout << "STAY" << endl;
    }

    //you don't have to manually close fstream
    //RAII will handle that for you
    //fin.close();
    //fout.close();

    return 0;
}
