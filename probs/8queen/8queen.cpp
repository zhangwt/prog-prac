#include <iostream>
using namespace std;

typedef unsigned long long ullong;

const int d = 8;

void printpos(int row_poses[], int d)
{
    for (int i = 0; i != d; ++i) {
        cout << row_poses[i] << " ";
    }
    cout << endl;
}

ullong queens(int col)
{
    static bool rows_taken[d] = {false};
    static bool lr_diag_taken[2*(d-1)+1] = {false};
    static bool rl_diag_taken[2*(d-1)+1] = {false};
    static int row_poses[d] = {0};
    static ullong cnt = 0;

    if (col == d) {
        cnt += 1;
        printpos(row_poses, d);
        return 0;
    }

    for (int row = 0; row <= d-1; ++row) {
        if (rows_taken[row] || lr_diag_taken[row-col+d-1] || rl_diag_taken[row+col]) {
            continue;
        }
        rows_taken[row] = lr_diag_taken[row-col+d-1] = rl_diag_taken[row+col] = true;
        row_poses[col] = row;
        queens(col+1);
        rows_taken[row] = lr_diag_taken[row-col+d-1] = rl_diag_taken[row+col] = false;
    }

    return cnt;
}

int main()
{
    ullong sols = queens(0);
    cout << "For " << d << "-queen problem, there are " << sols << " solutions." << endl;
    return 0;
}
