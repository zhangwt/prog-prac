/*
ID: zhangwt1
PROG: dualpal
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

string int2str(int base, int num) {
    string s;
    do {
        int r = num % base;
        char c;
        if (r < 10)
            c = r + '0';
        else
            c = r-10 + 'A';
        s.push_back(c);
        num /= base;
    } while (num);
    reverse(s.begin(), s.end());
    return s;
}

bool is_palindromic(string&& s) {
    int len = s.length();
    for (int i = 0, j = len-1;
            i < j;
            ++i, --j)
    {
        if (s[i] != s[j]) return false;
    }
    return true;
}

bool is_dualpal(int num) {
    int pal_cnt = 0;
    for(int base = 2; base <= 10; ++base) {
        if (is_palindromic(int2str(base, num))) {
            pal_cnt += 1;
            if (pal_cnt >= 2)
                return true;
        }
    }
    return false;
}

int main() {
    ifstream fin {"dualpal.in"};
    ofstream fout {"dualpal.out"};

    int N, S;
    fin >> N >> S;

    for (int i = 0; i < N; ++i) {
        while (!is_dualpal(++S));
        fout << S << endl;
    }
}
