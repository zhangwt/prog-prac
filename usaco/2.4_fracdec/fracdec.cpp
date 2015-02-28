/*
ID: zhangwt1
PROG: fracdec
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAX_FRAC_LEN = 658*76*3;

string fracdec(int N, int D)
{
    string s;
    int r = N;
    int frac_start = -1;

    int t = r/D;
    vector<char> ts;
    do {
        ts.push_back('0' + (t%10));
        t /= 10;
    } while (t);
    for (int i = ts.size()-1; i >= 0; --i) {
        s.push_back(ts[i]);
    }
    s.push_back('.');
    frac_start = s.size();
    r = (r%D)*10;

    while (r && s.size()-frac_start < MAX_FRAC_LEN) {
        if (r < D) {
            s.push_back('0');
            r *= 10;
        }
        else {
            s.push_back('0' + (r/D));
            r = (r%D)*10;
        }
    }

    if (r == 0) {
        if (frac_start == s.size()) {
            s.push_back('0');
        }
        return s;
    }

    for (int segstart = frac_start; segstart < s.size(); ++segstart) {
        for (int len = 1; len <= s.size()-segstart; ++len) {
            int next_segstart = segstart + len;
            int repeat = 0;
            while (next_segstart + len <= s.size()) {
                if (strncmp(s.c_str()+segstart, s.c_str()+next_segstart, len) == 0) {
                    repeat += 1;
                    next_segstart += len;
                }
                else {
                    break;
                }
            }
            if (next_segstart + len > s.size() && repeat >= 2) {
                return s.substr(0, segstart) + "(" + s.substr(segstart, len) + ")";
            }
        }
    }

    return s;
}

int main()
{
    int N, D;
    ifstream fin{"fracdec.in"};
    fin >> N >> D;

    ofstream fout{"fracdec.out"};
    string s = fracdec(N, D);
    int pos = 0;
    while (pos < s.size()) {
        int maxlen = min(76, (int)(s.size()-pos));
        fout << s.substr(pos, maxlen) << endl;
        pos += maxlen;
    }

    return 0;
}