/*
ID: zhangwt1
PROG: humble
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> merge_candidates(const vector<int>& candis1,
                             const vector<int>& candis2,
                             int size_limit)
{
    vector<int> candis;
    int k1 = 0, k2 = 0, size = 0;
    while (size < size_limit
            && (k1 != candis1.size() || k2 != candis2.size()))
    {
        int c;
        if (k1 == candis1.size())            c = candis2[k2++];
        else if (k2 == candis2.size())       c = candis1[k1++];
        else if (candis1[k1] < candis2[k2])  c = candis1[k1++];
        else if (candis2[k2] < candis1[k1])  c = candis2[k2++];
        else                                 { c = candis1[k1++]; k2++; }
        candis.push_back(c);
        size += 1;
    }
    return candis;
}

void print_vector(const vector<int>& vec)
{
    for (auto v: vec) cout << v << " ";
    cout << endl;
}

int main()
{
    int prime_size, N;
    ifstream fin{"humble.in"};
    fin >> prime_size >> N;

    vector<int> primes(prime_size, 0);
    for (auto& p: primes)
    {
        fin >> p;
    }
    sort(primes.begin(), primes.end());

    int MAX_INT = 0x7FFFFFFF;
    vector<int> candidates(1, 1);
    //print_vector(candidates);

    for (int prime: primes)
    {
        for (int factor = prime; MAX_INT/factor >= prime; factor*=prime)
        {
            vector<int> multips;
            for (int c: candidates)
            {
                if (MAX_INT/c >= factor) multips.push_back(c*factor);
                else break;
            }
            //cout << endl;
            //print_vector(multips);
            candidates = merge_candidates(candidates, multips, N+1);
            //print_vector(candidates);
        }
    }

    ofstream fout{"humble.out"};
    fout << candidates[N] << endl;
    
    return 0;
}
