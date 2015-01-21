/*
ID: zhangwt1
PROG: preface
LANG: C++11
*/

#include <iostream>
#include <fstream>
using namespace std;

int cnt[1001] = {};
int chars10[] = {1, 10, 100, 1000};
int chars5[] = {5, 50, 500};

void romanchars(int n)
{
    int digits[4] = {};
    int digit_num = 0;
    while (n) {
        int digit = n % 10;
        digits[digit_num++] = digit;
        n /= 10;
    }
    for (int i = digit_num-1; i != -1; --i) {
        if (0 == digits[i]) {
            continue;
        }
        else if (1 <= digits[i] && digits[i] <= 3) {
            cnt[chars10[i]] += digits[i];
        }
        else if (4 == digits[i]) {
            cnt[chars5[i]] += 1;
            cnt[chars10[i]] += 1;
        }
        else if (5 <= digits[i] && digits[i] <= 8) {
            cnt[chars5[i]] += 1;
            cnt[chars10[i]] += digits[i] - 5;
        }
        else if (9 == digits[i]) {
            cnt[chars10[i+1]] += 1;
            cnt[chars10[i]] += 1;
        }
    }
}

int main()
{
    int N;
    ifstream fin {"preface.in"};
    fin >> N;

    for (int i = 1; i <= N; ++i) {
        romanchars(i);
    }

    char chs[7] = {'I', 'V', 'X', 'L', 'C', 'D', 'M'};
    int nums[7] = {1, 5, 10, 50, 100, 500, 1000};
    ofstream fout {"preface.out"};
    int max_num_used = 0;
    for (int i = 6; i >= 0; --i) {
        if (cnt[nums[i]] != 0) {
            max_num_used = nums[i];
            break;
        }
    }
    for (int i = 0; i != 7; ++i) {
        if (nums[i] > max_num_used) {
            break;
        }
        fout << chs[i] << " " << cnt[nums[i]] << endl;
    }

    return 0;
}