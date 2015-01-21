/*
ID: zhangwt1
PROG: holstein
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

vector<int> requires;
vector<int> feedtype_supplies;
int vita_num;
int feedtype_num;

bool fixednum_scoop_combination(vector<int>& feedtypes, int start_feedtype, int scoop_num)
{
    if (scoop_num == 0) {
        // Check if @feedtypes satisfies by adding them up and comparing with @requires
        vector<int> sums(vita_num, 0);
        for (auto feed_idx : feedtypes) {
            for (int i = 0; i != vita_num; ++i) {
                sums[i] += feedtype_supplies[feed_idx*vita_num+i];
            }
        }
        for (int i = 0; i != vita_num; ++i) {
            if (sums[i] < requires[i]) {
                return false;
            }
        }
        return true;
    }

    for (int i = start_feedtype; i <= feedtype_num - scoop_num; ++i) {
        feedtypes.push_back(i);
        if (fixednum_scoop_combination(feedtypes, i+1, scoop_num-1)) {
            return true;
        }
        feedtypes.erase(feedtypes.end()-1);
    }

    return false;
}

vector<int> min_scoop_combination()
{
    for (int i = 1; i <= feedtype_num; ++i) {
        vector<int> comb;
        if (fixednum_scoop_combination(comb, 0, i)) {
            return comb;
        }
    }
    return vector<int>{};
}

int main()
{
    ifstream fin {"holstein.in"};

    fin >> vita_num;
    requires.resize(vita_num);
    for (int i = 0; i != vita_num; ++i) {
        fin >> requires[i];
    }

    fin >> feedtype_num;
    feedtype_supplies.resize(feedtype_num*vita_num);
    for (int i = 0; i != feedtype_num; ++i) {
        for (int j = 0; j != vita_num; ++j) {
            fin >> feedtype_supplies[i*vita_num+j];
        }
    }

    vector<int> comb = min_scoop_combination();

    ofstream fout {"holstein.out"};
    fout << comb.size();
    for (auto v : comb) {
        fout << " " << (v+1);
    }
    fout << endl;

    return 0;
}

// I pride myself on having the code work on the first time :)
