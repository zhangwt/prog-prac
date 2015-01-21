/*
ID: zhangwt1
PROG: skidesign
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <limits>
#define optimizar_io ios_base::sync_with_stdio(0);cin.tie(0);
using namespace std;

// Cann't figure it out with an elegent solution,
// neither think up using the brute-force solution,
// get it done by looking at the analysis.
//
// Cann't be sure of the correctness of the brute-force solution
// at first, and maybe this is why I cann't come up with it,
// this is the limitation that should be broken through.
//
// when an smart way isn't available,
// try the brute-force way,
// and advance a little if it's not so intuitive.

int main()
{
    optimizar_io;

    ifstream fin {"skidesign.in"};
    int N;
    fin >> N;

    vector<int> hills;
    for (int i = 0; i != N; ++i){
        int h;
        fin >> h;
        hills.push_back(h);
    }

    int min_cost = numeric_limits<int>::max();
    int max_h = *max_element(hills.begin(), hills.end());
    for (int min = 0; min <= max_h-17; ++min) {
        int max = min+17;
        int cost = 0;
        for (int h : hills) {
            if (h < min)
                cost += (min-h)*(min-h);
            else if (h > max)
                cost += (h-max)*(h-max);
        }
        if (cost < min_cost)
            min_cost = cost;
    }

    ofstream fout {"skidesign.out"};
    fout << min_cost << endl;
}
