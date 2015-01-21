/*
ID: zhangwt1
PROG: ariprog
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

struct Tuple
{
    int a;
    int b;

    Tuple(int a, int b) : a(a), b(b) {}
    bool operator<(const Tuple& other) const {
        return this->b < other.b ||
            (this->b == other.b && this->a < other.a);
    }
};

int main()
{
    ifstream fin {"ariprog.in"};
    int N, M;
    fin >> N >> M;
    //cout << "N=" << N << ", M=" << M << endl;

    // Construce bisquares set
    set<int> bisquares;
    for (int i = 0; i <= M; ++i) //XXX <= here, not <
        for (int j = i; j <= M; ++j) //XXX j should start from i, not 0
            bisquares.insert(i*i + j*j);

    //cout << "bisquares.size() = " << bisquares.size() << endl;
    //for (auto v : bisquares)
    //    cout << v << "\t";
    //cout << endl;

    const int MAX_BIS = 2*250*250;
    //XXX local array needs explictly INITIALIZATION
    bool bis_arr[MAX_BIS+1] = {};
    for (auto &v : bisquares)
        bis_arr[v] = true;

    vector<Tuple> results;

    // Scan bisquares to test all (a, b) possibilities
    for (auto i = bisquares.begin(); i != bisquares.end(); ++i) {
        auto j = i;
        ++j;
        for (; j != bisquares.end(); ++j)
        {
            int a = *i, b = *j - a;

            int seq_max = a + (N-1)*b;
            if (seq_max > MAX_BIS) {
                //XXX This is a VITAL OPTIMIZATION
                break;
            }

            if (!bis_arr[seq_max])
                continue;

            int k;
            for (k = 2; k != N; ++k) {
                int v = a + k*b;
                if (!bis_arr[v])
                    break;
            }
            if (k == N) {
                results.push_back(Tuple(a, b));
            }
        }
    }

    std::sort(results.begin(), results.end());
    //cout << "find " << results.size() << " sequences" << endl;

    // Output the results
    ofstream fout {"ariprog.out"};
    if (results.size() == 0)
        fout << "NONE" << endl;
    else
        for (auto &v : results) {
            fout << v.a << " " << v.b << endl;
            //cout << v.a << " " << v.b << endl;
        }

    return 0;
}
