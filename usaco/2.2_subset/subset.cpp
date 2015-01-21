/*
ID: zhangwt1
PROG: subset
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct PackGrid
{
    int maxnet;
    long long paths;
};

vector<PackGrid> packing(int volume, vector<int>& items)
{
    int cols = volume + 1, rows = items.size() + 1;
    vector<PackGrid> matrix(rows*cols, {0, 1});
    for (int i = 1; i <= items.size(); ++i) {
        for (int vol = 0; vol <= volume; ++vol) {
            PackGrid taken = {0, 0};
            if (vol >= items[i-1]) {
                PackGrid& pre = matrix[(i-1)*cols+(vol-items[i-1])];
                taken.maxnet = items[i-1] + pre.maxnet;
                taken.paths = pre.paths;
            }
            PackGrid nottaken = matrix[(i-1)*cols+vol];
            if (vol < items[i-1] || taken.maxnet < nottaken.maxnet) {
                matrix[i*cols+vol] = nottaken;
            }
            else if (taken.maxnet == nottaken.maxnet) {
                matrix[i*cols+vol].maxnet = taken.maxnet;
                matrix[i*cols+vol].paths = taken.paths + nottaken.paths;
            }
            else {
                matrix[i*cols+vol] = taken;
            }
        }
    }
    return matrix;
}

int optimalPackings(int vol, int i, int volume, vector<int>& items, vector<int>& matrix)
{
    cout << vol << " " << i << endl;
    static int cnt = 1;
    if (i == 1 || vol == 0) {
        return 0;
    }
    int cols = volume + 1;
    int taken = 0;
    if (vol >= items[i-1]) {
        taken = items[i-1] + matrix[(i-1)*cols+(vol-items[i-1])];
    }
    int nottaken = matrix[(i-1)*cols+vol];
    if (vol < items[i-1] || taken < nottaken) {
        optimalPackings(vol, i-1, volume, items, matrix);
    }
    else if (taken == nottaken) {
        cnt += 1;
        optimalPackings(vol, i-1, volume, items, matrix);
        optimalPackings(vol-items[i-1], i-1, volume, items, matrix);
    }
    else {
        optimalPackings(vol-items[i-1], i-1, volume, items, matrix);
    }
    return cnt;
}

int main()
{
    int N;
    ifstream fin {"subset.in"};
    fin >> N;

    int sum = N*(N+1)/2;
    ofstream fout {"subset.out"};
    if (sum % 2 == 1) {
        fout << 0 << endl;
    }
    else {
        int volume = sum/2;
        vector<int> items(N, 0);
        for (int i = 1; i <= N; ++i) {
            items[i-1] = i;
        }
        vector<PackGrid> matrix = packing(volume, items);
        //cout << "max net: " << (matrix.end()-1)->maxnet << endl;
        if ((matrix.end()-1)->maxnet == volume) {
            fout << (matrix.end()-1)->paths/2 << endl;
        }
        else {
            fout << 0 << endl;
        }
    }

    return 0;
}