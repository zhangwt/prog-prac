/*
ID: zhangwt1
PROG: prefix
LANG: C++11
*/

// runs for 0.472 sec for seq.length()=200k

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>
using namespace std;

int main()
{
    ifstream fin{"prefix.in"};
    unordered_set<string> dict;
    string s;
    int max_word_len = 0;
    while(true) {
        fin >> s;
        if (s != ".") {
            dict.insert(s);
            max_word_len = max((size_t)max_word_len, s.length());
        }
        else {
            break;
        }
    }

    string seq;
    for(string s; fin >> s;) {
        seq += s;
    }
    //cout << "seq: " << seq << endl;

    vector<int> ans(seq.length()+1, 0);

    for (int i = seq.length()-1; i != -1; --i) {
        int n = seq.length() - i;
        int max_match_len = min(max_word_len, n);
        int n_max_ans = 0;
        for (int j = 1; j <= max_match_len; ++j) {
            string prefix = seq.substr(i, j);
            unordered_set<string>::iterator it = dict.find(prefix);
            if (it == dict.end()) {
                continue;
            }
            int t_ans = j + ans[n-j];
            if (t_ans > n_max_ans) {
                n_max_ans = t_ans;
            }
        }
        ans[n] = n_max_ans;
        //cout << n << ", " << ans[n] << endl;
    }

    ofstream fout {"prefix.out"};
    fout << *(ans.end()-1) << endl;

    return 0;
}
