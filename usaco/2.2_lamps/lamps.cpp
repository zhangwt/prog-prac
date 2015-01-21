/*
ID: zhangwt1
PROG: lamps
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int N;
vector<string> states[5];
vector<int> ons;
vector<int> offs;

void combination(int start, int end, int comb_len, vector<int>& res,
        void(*callback)(vector<int>& res))
{
    if (comb_len == 0) {
        callback(res);
        return;
    }

    for (int i = start; i <= end-comb_len; ++i) {
        *(res.end()-comb_len) = i;
        combination(i+1, end, comb_len-1, res, callback);
    }
}

void callback(vector<int>& buttons)
{
    cout << "buttons: ";
    for (auto v: buttons) {
        cout << v << " ";
    }
    cout << endl;
    string state(N, '1');
    for (int button: buttons) {
        switch (button) {
            case 0: {
                for (int i = 0; i != state.length(); ++i) {
                    state[i] = '0' + ('1'-state[i]);
                }
                break;
            }
            case 1: {
                for (int i = 0; i <= N-1-(1-(N&1)); i+=2) {
                    state[i] = '0' + ('1'-state[i]); 
                }
                break;
            }
            case 2: {
                for (int i = 1; i <= N-1-(N&1); i+=2) {
                    state[i] = '0' + ('1'-state[i]); 
                }
                break;
            }
            case 3: {
                for (int i = 0; i != state.length(); ++i) {
                    if (i%3 == 0) {
                        state[i] = '0' + ('1'-state[i]); 
                    }
                }
                break;
            }
            default:
                break;
        }
    }
    states[buttons.size()].push_back(state);
    cout << "state: " << state << endl;
}

void calc_states()
{
    for (int count = 0; count <= 4; ++count) {
        vector<int> seq(count, 0);
        combination(0, 4, count, seq, callback);
    }
}

vector<string> check_count(vector<int> counts)
{
    vector<string> valids;
    for (int count: counts) {
        cout << "check count " << count << endl;
        for(string& state: states[count]) {
            cout << state << " ";
            bool valid = true;
            for (int v: ons) {
                valid = valid && (state[v] == '1');
            }
            for (int v: offs) {
                valid = valid && (state[v] == '0');
            }
            if (valid) {
                cout << "checked";
                valids.push_back(state);
            }
            cout << endl;
        }
    }
    return valids;
}

int main()
{
    ifstream fin{"lamps.in"};
    int C;
    fin >> N >> C;
    int idx;
    while(true) {
        fin >> idx;
        if (idx != -1) {
            ons.push_back(idx-1);
        }
        else {
            break;
        }
    }
    while(true) {
        fin >> idx;
        if (idx != -1) {
            offs.push_back(idx-1);
        }
        else {
            break;
        }
    }

    calc_states();

    int reduced_c = C % 4;
    vector<string> valids;
    if (C >= 4) {
        if (reduced_c % 2 == 0) {
           valids = check_count({0, 2, 4}); 
        }
        else {
            valids = check_count({1, 3});
        }
    }
    else {
        if (reduced_c == 0 || reduced_c == 1) {
            valids = check_count({reduced_c});
        }
        else {
            valids = check_count({reduced_c-2, reduced_c});
        }
    }

    sort(valids.begin(), valids.end());
    unique(valids.begin(), valids.end());

    ofstream fout{"lamps.out"};
    for (string& v: valids) {
        fout << v << endl;
    }
    if (valids.size() == 0) {
        fout << "IMPOSSIBLE" << endl;
    }

    return 0;
}