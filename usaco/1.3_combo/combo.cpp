/*
ID: zhangwt1
PROG: combo
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <set>
using namespace std;

struct Range {
    int begin;
    int len;
};

inline int mod_sub(int k, int N, int dist) {
    return (k+(N-dist))%N;
}

inline int mod_add(int k, int N, int dist) {
    return (k+dist)%N;
}

Range range(int k, int N, int dist) {
    if (2*dist >= N-1)
        return Range{0, N};
    return Range{mod_sub(k, N, dist), 2*dist+1};
}

vector<Range> ranges(int k[3], int N, int dist) {
    vector<Range> rs;
    for (int i = 0; i < 3; ++i) {
        rs.push_back(range(k[i], N, dist));
    }
    return rs;
}

bool in_range(int coor[3], int N, vector<Range>& rs) {
    for (int i = 0; i != 3; ++i) {
        bool res;
        if (rs[i].begin + rs[i].len <= N)
            res = rs[i].begin <= coor[i] && coor[i] <= rs[i].begin+rs[i].len-1;
        else {
            if (coor[i] >= rs[i].begin)
                res = true;
            else
                res = coor[i] <= mod_add(rs[i].begin, N, rs[i].len-1);
        }
        if (!res) return false;
    }
    return true;
}

int close_lock(int lock[3], int N, int dist, vector<Range>&& other_ranges) {
    vector<Range> rs = ranges(lock, N, dist);
    if (other_ranges.size() == 0)
        return rs[0].len * rs[1].len * rs[2].len;
    int cnt = 0;
    for (int i0 = rs[0].begin, id0 = 0; id0 < rs[0].len; ++id0) {
        for (int i1 = rs[1].begin, id1 = 0; id1 < rs[1].len; ++id1) {
            for (int i2 = rs[2].begin, id2 = 0; id2 < rs[2].len; ++id2) {
                int coor[3] = {mod_add(i0, N, id0), mod_add(i1, N, id1), mod_add(i2, N, id2)};
                cnt += in_range(coor, N, other_ranges) ? 0 : 1;
            }
        }
    }
    return cnt;
}

int main() {
    ifstream fin {"combo.in"};
    ofstream fout {"combo.out"};

    int N, dist = 2;
    fin >> N;

    int lock1[3], lock2[3];
    fin >> lock1[0] >> lock1[1] >> lock1[2];
    fin >> lock2[0] >> lock2[1] >> lock2[2];
    for (int &v:lock1) v -= 1;
    for (int &v:lock2) v -= 1;

    int num = close_lock(lock1, N, dist, ranges(lock2, N, dist))
        + close_lock(lock2, N, dist, vector<Range>());
    fout << num << endl;
}

