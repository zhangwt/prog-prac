/*
ID: zhangwt1
PROG: palsquare
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

bool is_palindromic(string& s) {
    int len = s.length();
    for (int i = 0, j = len-1;
            i < j;
            ++i, --j)
    {
        if (s[i] != s[j]) return false;
    }
    return true;
}

int main() {
    ifstream fin {"palsquare.in"};
    ofstream fout {"palsquare.out"};

    int base;
    fin >> base;

    for (int n = 1; n <= 300; ++n) {
        string s = int2str(base, n*n);
        if (is_palindromic(s))
            fout << int2str(base, n) << " " << s << endl;
    }
}

