/*
ID: zhangwt1
PROG: sort3
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

int exchangeCount(int N, vector<int>& numbers)
{
    vector<int> malpos(N*N, 0);
    vector<int> numCounts(N, 0);
    for (int i = 0; i < numbers.size(); ++i) {
        numCounts[numbers[i]] += 1;
    }
    vector<int> numSegStart(N, 0);
    for (int i = 1; i < N; ++i) {
        numSegStart[i] = numSegStart[i-1] + numCounts[i-1];
    }
    for (int i = 0; i < numbers.size(); ++i) {
        vector<int>::iterator it = upper_bound(numSegStart.begin(), numSegStart.end(), i);
        int segNum = it - numSegStart.begin() - 1;
        if (numbers[i] != segNum) {
            malpos[numbers[i]*N + segNum] += 1;
        }
    }
    int coupleCount = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = i+1; j < N; ++j) {
            int coupleMal = min(malpos[i*N+j], malpos[j*N+i]);
            malpos[i*N+j] -= coupleMal;
            malpos[j*N+i] -= coupleMal;
            coupleCount += coupleMal;
        }
    }
    //XXX Notice that there could be several{permNum}
    // identical permutations of length{permLen}.
    // We can assert that non-zero elements of malpos[]
    // are of the same value, i.e. {permNum}.
    int permLen = 0, permNum = 0;
    for (int i = 0; i < malpos.size(); ++i) {
        if (malpos[i] != 0) {
            permNum = malpos[i];
            permLen += 1;
        }
    }
    return coupleCount + permNum*(permLen-1);
}

int main() 
{
    ifstream fin {"sort3.in"};
    int n;
    fin >> n;
    vector<int> numbers(n, 0);
    for (int i = 0; i < n; ++i) {
        fin >> numbers[i];
        //XXX Remember that integers start from 0 here
        numbers[i] -= 1;
    }

    ofstream fout {"sort3.out"};
    fout << exchangeCount(3, numbers) << endl;
    return 0;
}

