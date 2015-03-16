/*
ID: zhangwt1
PROG: inflate
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    int net, cates;
    ifstream fin{"inflate.in"};
    fin >> net >> cates;

    vector<int> values1(net+1, 0);
    vector<int> values2(net+1, 0);
    vector<int> *pv1 = &values1, *pv2 = &values2;

    for (int row = 1; row <= cates; ++row)
    {
        int c_value, c_net;
        fin >> c_value >> c_net;

        (*pv2)[0] = 0;
        for (int col = 1; col <= net; ++col)
        {
            int v1 = (*pv1)[col];
            int v2 = (col >= c_net) ? (*pv2)[col-c_net] + c_value : 0;
            (*pv2)[col] = max(v1, v2);
        }

        swap(pv1, pv2);
    }

    ofstream fout{"inflate.out"};
    fout << (*pv1)[net] << endl; //XXX it's pv1 here, NOT pv2

    return 0;
}
