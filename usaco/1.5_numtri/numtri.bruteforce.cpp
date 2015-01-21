/*
ID: zhangwt1
PROG: numtri
LANG: C++11
*/

#include <iostream>
#include <fstream>
using namespace std;

unsigned int g_sum = 0;
unsigned int g_max = 0;
unsigned char M[1000][1000];

void tri_path(int i, int j, const int R)
{
    if (i == R) {
        g_max = max(g_sum, g_max);
        return;
    }

    g_sum += M[i][j];

    for (int k = j; k <= j+1; ++k) {
        tri_path(i+1, k, R);
    }

    g_sum -= M[i][j];
}

int main()
{
    ifstream fin {"numtri.in"};
    int R;
    fin >> R;

    for (int i = 0; i != R; ++i) {
        for (int j = 0; j < i+1; ++j) {
            int t;
            fin >> t;
            M[i][j] = t;
        }
    }

    tri_path(0, 0, R);

    ofstream fout {"numtri.out"};
    fout << g_max << endl;
}

