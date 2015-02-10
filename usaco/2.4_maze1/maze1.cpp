/*
ID: zhangwt1
PROG: maze1
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX_W = 38;
const int MAX_H = 100;
const int infinity = numeric_limits<int>::max();

char map[2*MAX_H+1][2*MAX_W+1]; // 0-indexed
int W, H;
int step[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

void dijkstra(int src, vector<int>& ssp, vector<int>& pa)
{
    for (int i = 0; i < ssp.size(); ++i) {
        ssp[i] = infinity;
        pa[i] = -1;
    }
    ssp[src] = 0;

    // find sp to one more node until all sps are found
    vector<bool> found(ssp.size(), false);
    while (true) {
        int min_node=-1, min_sp = infinity;
        for (int i = 0; i < ssp.size(); ++i) {
            if (!found[i] && ssp[i] < min_sp) {
                min_sp = ssp[i];
                min_node = i;
            }
        }
        if (min_node == -1) {
            break;
        }
        found[min_node] = true;
        ssp[min_node] = min_sp;

        int mi = min_node / W, mj = min_node % W;
        int mi_map = 2*mi+1, mj_map = 2*mj+1;
        for (int k = 0; k < 4; ++k) {
            int ni = mi+step[k][0];
            int nj = mj+step[k][1];
            if (0 <= ni && ni < H && 0 <= nj && nj < W) {
                int ni_map = mi_map+step[k][0];
                int nj_map = mj_map+step[k][1];
                if (map[ni_map][nj_map] == ' ' && min_sp+1 < ssp[ni*W+nj]) {
                    ssp[ni*W+nj] = min_sp+1;
                    pa[ni*W+nj] = min_node;
                }
            }
        }
    }
}

int main()
{
    ifstream fin {"maze1.in"};
    fin >> W >> H;

    int exits[2];
    int exit_cnt = 0;
    for (int i = 0; i < 2*H+1; ++i) {
        for (int j = 0; j < 2*W+1; ++j) {
            while ((map[i][j] = fin.get()) == '\n');
            //cout << "(" << map[i][j] << ")" << endl;
            if (map[i][j] == ' ' && (i == 0 || i == 2*H || j == 0 || j == 2*W)) {
                exits[exit_cnt++] = (i-1)/2*W+(j-1)/2;
            }
        }
    }

    vector<int> ssp0(W*H, 0), ssp1(W*H, 0);
    vector<int> pa0(W*H, 0), pa1(W*H, 0);
    dijkstra(exits[0], ssp0, pa0);
    dijkstra(exits[1], ssp1, pa1);
    int maxsteps = 0;
    for (int i = 0; i < ssp0.size(); ++i) {
        int dist = min(ssp0[i], ssp1[i]);
        maxsteps = max(maxsteps, dist);
    }

    ofstream fout {"maze1.out"};
    fout << (maxsteps+1) << endl;

    return 0;
}
