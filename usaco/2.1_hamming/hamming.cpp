/*
ID: zhangwt1
PROG: hamming
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int distance(int a, int b)
{
    int xornum = a ^ b;
    int ones = 0;
    while (xornum != 0) {
        xornum = xornum & (xornum-1);
        ones += 1;
    }
    //cout << "distance(" << a << ", " << b << ") = " << ones << endl;
    return ones;
}

int main()
{
    int N, B, D;

    ifstream fin {"hamming.in"};
    fin >> N >> B >> D;

    int maxint = (1 << B) - 1; 

    vector<int> codewords(N, 0);
    int nextword = 1;
    int found;
    for (found = 1; found != N;) {
        if (nextword > maxint) {
            cerr << "There isn't enough codewords." << endl;
            break;
        }
        int w;
        for (w = nextword; w <= maxint; ++w) {
            int idx;
            for (idx = 0; idx != found; ++idx) {
                if (distance(codewords[idx], w) < D) {
                    break;
                }
            }
            if (idx == found) {
                codewords[found++] = w++;
                //cout << "found " << codewords[found-1] << endl;
                break;
            }
        }
        nextword = w;
    }

    ofstream fout {"hamming.out"};
    for (int k = 0; k != found; ++k) {
        fout << codewords[k];
        if (k%10 == 9) {
            fout << endl;
        } else if (k != found-1) {
            fout << " ";
        }
    }
    if (found%10 != 0) {
        fout << endl;
    }

    return 0;
}
