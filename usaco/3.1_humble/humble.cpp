/*
ID: zhangwt1
PROG: humble
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main()
{
    int K, N;
    ifstream fin{"humble.in.2"};
    fin >> K >> N;

    vector<int> primes(K, 0);
    for (auto& p: primes)
    {
        fin >> p;
    }

    vector<bool> ishumble(1, true); // for value == 1
    int humbles = 0, value;
    for (value = 2; humbles != N; ++value)
    {
        bool h = false;
        for (int k = 0; k != K && !h; ++k)
        {
            if (value % primes[k] != 0) h = false;
            else h = ishumble[value/primes[k]-1];
        }
        ishumble.push_back(h);
        humbles += (int)(h);
    }

    ofstream fout{"humble.out"};
    fout << (value-1) << endl;

    return 0;
}
