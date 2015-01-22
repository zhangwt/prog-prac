/*
ID: zhangwt1
PROG: money
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

typedef long long llong;

int main()
{
    int V, N;
    ifstream fin{"money.in"};
    fin >> V >> N;
    vector<llong> vals(V+1, 0);
    for (int v = 1; v <= V; ++v) {
        fin >> vals[v];
    }

    vector<llong> dp((V+1)*(N+1), 0);
    int cols = N+1;

    for (int n = 1; n <= N; ++n) {
        dp[0*cols+n] = 0;
    }
    for (int v = 0; v <= V; ++v) {
        dp[v*cols+0] = 1;
    }

    for (int v = 1; v <= V; ++v) {
        for (int n = 1; n <= N; ++n) {
            if (n < vals[v]) {
                dp[v*cols+n] = dp[(v-1)*cols+n];
            }
            else {
                dp[v*cols+n] = dp[(v-1)*cols+n] + dp[v*cols+(n-vals[v])];
            }
        }
    }

    ofstream fout{"money.out"};
    fout << dp[V*cols+N] << endl;
}