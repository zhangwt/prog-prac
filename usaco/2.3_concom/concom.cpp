/*
ID: zhangwt1
PROG: concom
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main()
{
    int x, i, j, p;
    ifstream fin{"concom.in"};
    fin >> x;

    vector<int> coms((100+1)*(100+1), 0);
    vector<int> coms_itered((100+1)*(100+1), 0);
    vector<bool> new_con((100+1)*(100+1), false);
    int com_num = 0;
    int new_cons = 0;
    int cols = 100+1;

    for (int k = 0; k != x; ++k) {
        fin >> i >> j >> p;
        coms[i*cols+j] = p;
        coms_itered[i*cols+j] = p;
        if (p > 50) {
            new_con[i*cols+j] = true;
            new_cons += 1;
        }
        com_num = max(com_num, max(i, j));
    }

    while (new_cons) {
        new_cons = 0;
        for (int row = 1; row <= com_num; ++row) {
            for (int col = 1; col <= com_num; ++col) {
                if (row == col || !new_con[row*cols+col]) {
                    continue;
                }
                new_con[row*cols+col] = false;
                for (int col2 = 1; col2 <= com_num; ++col2) {
                    if (col2 == col || col2 == row) {
                        continue;
                    }
                    if (coms_itered[row*cols+col2] <= 50) {
                        coms_itered[row*cols+col2] += coms[col*cols+col2];
                        if (coms_itered[row*cols+col2] > 50) {
                            new_con[row*cols+col2] = true;
                            new_cons += 1;
                        }
                    }
                }
            }
        }
    }

    //ofstream fout{"concom.out"};
    for (int i = 1; i <= com_num; ++i) {
        for (int j = 1; j <= com_num; ++j) {
            if (i != j && coms_itered[i*cols+j] > 50) {
                //fout << i << " " << j << endl;
                cout << i << " " << j << endl;
            }
        }
    }

    return 0;
}