/*
ID: zhangwt1
PROG: milk3
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

int NET[3];
int g_water[3];
/* mistaken by 20*20*20 at first.
 * we are storing the state of WATER, NOT NET.
 * NET[i] is [1, 20], but g_water[i] could be 0,
 * thus there is 21 possibilities
 */
bool g_state[21*21*21] = {};

vector<int> g_target_c;

inline void set_state();
inline bool encountered_state();

void dump()
{
    if (encountered_state()) {
        return;
    } else {
        set_state();
        if (g_water[0] == 0)
            g_target_c.push_back(g_water[2]);
    }

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (i == j) continue;

            if (g_water[i] == 0 || g_water[j] == NET[j])
                continue;

            int trans = min(g_water[i], NET[j]-g_water[j]);
            if (trans == 0) continue;

            g_water[i] -= trans;
            g_water[j] += trans;
            dump();
            g_water[i] += trans;
            g_water[j] -= trans;
        }
    }
}

inline void set_state()
{
    g_state[g_water[0] + g_water[1]*21 + g_water[2]*21*21] = true;
}

inline bool encountered_state()
{
    return g_state[g_water[0] + g_water[1]*21 + g_water[2]*21*21];
}

int main()
{
    ifstream fin {"milk3.in"};
    for (int i = 0; i < 3; ++i) {
        fin >> NET[i];
    }

    g_water[0] = g_water[1] = 0;
    g_water[2] = NET[2];

    dump();
    sort(g_target_c.begin(), g_target_c.end());

    ofstream fout {"milk3.out"};
    size_t i;
    for (i = 0; i < g_target_c.size()-1; ++i)
        fout << g_target_c[i] << " ";
    fout << g_target_c[i] << endl;
}
