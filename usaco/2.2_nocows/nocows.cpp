/*
ID: zhangwt1
PROG: nocows
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

const int R = 9901;

int main()
{
    int N, K;
    ifstream fin{"nocows.in"};
    fin >> N >> K;
    int cols = K+1;

    vector<int> nums((N+1)*cols, 0);
    for (int k = 1; k <= K; ++k) {
        nums[1*cols+k] = 1;
    }
    for (int n = 3; n <= N; n+=2) {
        nums[n*cols+1] = 0;
    }

    for (int n = 3; n <= N; n+=2) {
        cout << "(n=" << n << ") ";
        for (int k = 2; k <= K; k+=1) {
            //int min_n = 2*k-1;
            //int max_n = (1>>k)-1;
            //if (n < min_n || max_n < n) {
            //    nums[n*cols+k] = nums[n*cols+(k-1)];
            //    continue;
            //}

            int k_left = k-1;
            int num = 0;
            for (int n_left = 1; n_left <= n-1-1; n_left+=2) {
                int num_left = nums[n_left*cols+k_left] - nums[n_left*cols+(k_left-1)];
                int num_right_diff_k = nums[(n-1-n_left)*cols+k_left-1];
                num = (num + num_left*num_right_diff_k*2) % R;
                int num_right_same_k = nums[(n-1-n_left)*cols+k_left] - nums[(n-1-n_left)*cols+k_left-1];
                num = (num + num_left*num_right_same_k) % R;
            }
            nums[n*cols+k] = (nums[n*cols+k-1] + num) % R;
            cout << "<k=" << k << ">" << nums[n*cols+k] << " ";
        }
        cout << endl;
    }

    ofstream fout {"nocows.out"};
    fout << ((nums[N*cols+K] - nums[N*cols+K-1] + R) % R) << endl;

    return 0;
}