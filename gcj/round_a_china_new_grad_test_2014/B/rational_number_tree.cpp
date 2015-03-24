#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdint>
using namespace std;

ifstream fin{"B-small-practice.in"};
ofstream fout{"B-small-practice.out"};

vector<uint64_t> right_most_in_left(64, 0);
vector<uint64_t> left_most_in_left(64, 0);

void findnumber(uint64_t n, uint64_t p, uint64_t q)
{
    //cout << "\nn=" << n << " p=" << p << " q=" << q << endl;
    if (n == 1)
    {
        fout << " " << p << " " << q << endl;
        return;
    }

    int max_height = (upper_bound(right_most_in_left.begin(), right_most_in_left.end(), n)
            - right_most_in_left.begin()) + 1;
    //cout << "max_height=" << max_height << endl;
    int height;
    bool toleft;
    if (n >= left_most_in_left[max_height-1])
    {
        height = max_height;
        toleft = true;
    }
    else
    {
        height = max_height-1;
        if (n == right_most_in_left[height-1])
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
        n -= left_most_in_left[height-2];
    }
    else
    {
        p = p+q;
        n -= left_most_in_left[height-1];
    }

    findnumber(n, p, q);
}

void findposition(uint64_t p, uint64_t q)
{

}

int main()
{
    right_most_in_left[0] = 1;
    right_most_in_left[1] = 2;
    for (int i = 2; i <= 63; ++i)
    {
        right_most_in_left[i] = right_most_in_left[i-1]*2 + 1;
        //cout << right_most_in_left[i] << " ";
    }
    //cout << endl;
    left_most_in_left[0] = 1;
    for (int i = 1; i <= 63; ++i)
    {
        left_most_in_left[i] = 2*left_most_in_left[i-1];
        //cout << left_most_in_left[i] << " ";
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
