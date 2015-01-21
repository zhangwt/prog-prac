/*
ID: zhangwt1
PROG: runround
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

unsigned lower;

bool isRunRound(vector<char>& digits)
{
    unsigned num = 0;
    for (auto v: digits) {
        num = num*10 + (v-'0');
    }
    if (num <= lower) {
        return false;
    }

    bool met[10] = {};
    met[digits[0]-'0'] = true;
    int cur = 0;
    for(int round = 0; round != digits.size()-1; ++round) {
        cur = (cur + (digits[cur]-'0')) % digits.size();
        if (met[digits[cur]-'0']) {
            return false;
        }
    }
    cur = (cur + (digits[cur]-'0')) % digits.size();
    if (met[digits[cur]-'0']) {
        return true;
    }
    else {
        return false;
    }
}

bool permutation(vector<char>& digits, vector<char>& perm,
        int perm_len, bool(*callback)(vector<char>&))
{
    if (perm_len == perm.size()) {
        //for (auto v : perm) {
        //    cout << v << " ";
        //}
        //cout << endl;
        return callback(perm);
    }

    for (int i = 0; i != digits.size(); ++i) {
        perm[perm_len++] = digits[i];
        vector<char> left_digits(digits.size()-1, 0);
        for (int k = 0, c = 0; k != digits.size(); ++k) {
            if (k != i) {
                left_digits[c++] = digits[k];
            }
        }
        if (permutation(left_digits, perm, perm_len, callback)) {
            return true;
        }
        --perm_len;
    }

    return false;
}

int main()
{
    ifstream fin {"runround.in"};
    fin >> lower;

    int N = 9;
    vector<char> digits(N, '0');
    for (int i = 0; i != digits.size(); ++i) {
        digits[i] = '1' + i;
    }

    int perm_size = 0;
    int num = lower;
    do {
        ++perm_size;
        num /= 10;
    } while (num);

    bool found = false;
    perm_size -= 1;
    vector<char> perm;
    do {
        perm.resize(++perm_size);
        found = permutation(digits, perm, 0, isRunRound);
    } while (!found && perm_size != 9);

    if (!found) {
        cerr << "cann't find a runround." << endl;
        return 1;
    }

    ofstream fout {"runround.out"};
    for (auto v : perm) {
        fout << v;
    }
    fout << endl;

    return 0;
}

/*
1 2 3 4
1 2 4 3
1 3 2 4
1 3 4 2
1 4 2 3
1 4 3 2
2 1 3 4
2 1 4 3
2 3 1 4
2 3 4 1
2 4 1 3
2 4 3 1
3 1 2 4
3 1 4 2
3 2 1 4
3 2 4 1
3 4 1 2
3 4 2 1
4 1 2 3
4 1 3 2
4 2 1 3
4 2 3 1
4 3 1 2
4 3 2 1
*/