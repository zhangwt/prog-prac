/*
ID: zhangwt1
PROG: numtri
LANG: C++11
*/

#include <iostream>
#include <fstream>
using namespace std;


int main()
{
    ifstream fin {"numtri.in"};
    int R;
    fin >> R;

    int t;
    fin >> t;

    int row1[1000], row2[1000];

    int *last_row = row1;
    last_row[0] = t;
    int max_sum = t;

    int *this_row = row2;

    for (int i = 1; i < R; ++i) {
        for (int j = 0; j <= i; ++j) {
            fin >> t;

            int sum;
            if (j == 0)
                sum = t + last_row[j];
            else if (j == i)
                sum = t + last_row[j-1];
            else
                sum = t + max(last_row[j-1], last_row[j]);

            this_row[j] = sum;
            //cout << sum << " ";
            max_sum = max(max_sum, sum);
        }
        //cout << endl;
        swap(this_row, last_row);
    }

    ofstream fout {"numtri.out"};
    fout << max_sum << endl;
}

