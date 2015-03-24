#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdint>
using namespace std;

ifstream fin{"B-small-practice.in"};
ofstream fout{"B-small-practice.out"};

vector<uint64_t> rmil(64, 0); //ids of right most in left
vector<uint64_t> lmil(64, 0); //ids of left most in left

void findnumber(uint64_t n, uint64_t p, uint64_t q)
{
    //cout << "\nn=" << n << " p=" << p << " q=" << q << endl;
    if (n == 1)
    {
        fout << " " << p << " " << q << endl;
        return;
    }

    int max_height = (upper_bound(rmil.begin(), rmil.end(), n) - rmil.begin()) + 1;
    //cout << "max_height=" << max_height << endl;
    int height;
    bool toleft;
    if (n >= lmil[max_height-1])
    {
        height = max_height;
        toleft = true;
    }
    else
    {
        height = max_height-1;
        if (n == rmil[height-1])
        {
            toleft = true;
        }
        else
        {
            toleft = false;
        }
    }
    //cout << "height=" << height << " toleft=" << toleft << endl;

    if (toleft)
    {
        q = p+q;
        n -= lmil[height-2];
    }
    else
    {
        p = p+q;
        n -= lmil[height-1];
    }

    findnumber(n, p, q);
}

void findposition(uint64_t p, uint64_t q)
{

}

int main()
{
    rmil[0] = 1;
    rmil[1] = 2;
    for (int i = 2; i <= 63; ++i)
    {
        rmil[i] = rmil[i-1]*2 + 1;
        //cout << rmil[i] << " ";
    }
    //cout << endl;
    lmil[0] = 1;
    for (int i = 1; i <= 63; ++i)
    {
        lmil[i] = 2*lmil[i-1];
        //cout << lmil[i] << " ";
    }
    //cout << endl;

    int T;
    fin >> T;

    for (int i = 0; i != T; ++i)
    {
        fout << "Case #" << (i+1) << ":";
        int probid;
        fin >> probid;
        if (probid == 2)
        {
            uint64_t p, q;
            fin >> p >> q;
            findposition(p, q);
        }
        else
        {
            uint64_t n;
            fin >> n;
            findnumber(n, 1, 1);
        }
    }

    return 0;
}
