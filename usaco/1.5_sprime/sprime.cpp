/*
ID: zhangwt1
PROG: sprime
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <utility>
using namespace std;


bool is_prime(int n)
{
    if (n <= 1)
        return false;
    int stop = min((int)sqrt(n) + 1, n-1);
    for (int i = 2; i <= stop; ++i) {
        if (n % i == 0)
            return false;
    }
    return true;
}

vector<int> sprime(int n_digits)
{
    vector<int> seeds {0};
    for (int i = 0; i < n_digits; ++i) {
        vector<int> new_seeds;
        for (int v : seeds) {
            for (int k = 0; k <= 9; ++k)
                if (is_prime(v*10 + k))
                    new_seeds.push_back(v*10 + k);
        }
        seeds = move(new_seeds);
    }
    return seeds;
}

int main()
{
    ifstream fin {"sprime.in"};
    int n;
    fin >> n;

    ofstream fout {"sprime.out"};
    vector<int> sprimes = sprime(n);
    for (int v : sprimes)
        fout << v << endl;
}
