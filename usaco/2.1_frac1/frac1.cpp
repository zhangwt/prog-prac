/*
ID: zhangwt1
PROG: frac1
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

struct Frac 
{
    unsigned char nu;
    unsigned char de;
};

inline bool fracSortingLoose(const Frac& f1, const Frac& f2) {
    return (unsigned)(f1.nu)*(unsigned)(f2.de) <
            (unsigned)(f2.nu)*(unsigned)(f1.de);
}

inline bool fracSorting(const Frac& f1, const Frac& f2) {
    if (fracSortingLoose(f1, f2)) {
        return true;
    }
    if (fracSortingLoose(f2, f1)) {
        return false;
    }
    if (f1.de < f2.de) {
        return true;
    } else {
        return false;
    }
}

inline bool fracEqual(const Frac& f1, const Frac& f2) {
    return (unsigned)(f1.nu)*(unsigned)(f2.de) ==
            (unsigned)(f2.nu)*(unsigned)(f1.de);
}

vector<Frac> orderedFracs(int maxDe) {
    vector<Frac> vf;
    for (int i = 1; i <= maxDe; ++i) {
        for (int j = 0; j <= i; ++j) {
            vf.push_back({(unsigned char)j, (unsigned char)i});
        }
    }
    sort(vf.begin(), vf.end(), fracSorting);
    auto it = unique(vf.begin(), vf.end(), fracEqual);
    vf.resize(it - vf.begin());
    return vf;
}

int main() {
    ifstream fin {"frac1.in"};
    int N;
    fin >> N;

    vector<Frac> vf = orderedFracs(N);
    ofstream fout {"frac1.out"};
    for (auto &v : vf) {
        fout << (unsigned)v.nu << "/" << (unsigned)v.de << endl;
    }

    return 0;
}