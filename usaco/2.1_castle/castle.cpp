/*
ID: zhangwt1
PROG: castle
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

struct NodeStat
{
    // -1 for not assigned
    int component_id = -1;
    int walls = 0;
};

// {west, north, east, south}
const int DIRECTION_NUM = 4;
const int DIRECTION_OFFSET[][2] = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};
const int DIRECTION_MASK[] = {1, 2, 4, 8};
const char DIRECTION_CHAR[] = {'W', 'N', 'E', 'S'};

int COL_NUM, ROW_NUM;
vector<NodeStat> node_stat;
vector<int> component_size;

void find_component(int i, int j, int component_id)
{
    //cout << "comp_id: " << component_id
    //    << ", (" << i << ", " << j << ")" << endl;

    int node_id = i*COL_NUM+j;
    node_stat[node_id].component_id = component_id;
    component_size[component_id] += 1;

    for (int k = 0; k < DIRECTION_NUM; ++k) {
        int new_i = i+DIRECTION_OFFSET[k][0];
        int new_j = j+DIRECTION_OFFSET[k][1];
        if (0 <= new_i && new_i < ROW_NUM
            && 0 <= new_j && new_j < COL_NUM
            && !(node_stat[node_id].walls & DIRECTION_MASK[k])
            && node_stat[new_i*COL_NUM+new_j].component_id == -1)
        {
            find_component(new_i, new_j, component_id);
        }
    }
}

struct MaxMergedInfo
{
    int size, i, j, direction_id;
    MaxMergedInfo(int size, int i, int j, int direction_id)
        :size(size), i(i), j(j), direction_id(direction_id)
    {}
};

MaxMergedInfo find_max_size_merged_compoment()
{
    MaxMergedInfo mergeinfo {0, 0, 0, 0};

    // XXX 'west' has higher priority than 'south',
    // thus we should loop column by colunm from west to east;
    // then in each colunm loop from south to north
    for (int j = 0; j < COL_NUM; ++j) {
        for (int i = ROW_NUM; i >= 0; --i) {
            int node_id = i*COL_NUM+j;
            int component_id = node_stat[node_id].component_id;

            vector<int> selected_direction_ids = {1, 2};
            for (auto k : selected_direction_ids) {
                //cout << i << " " << j << " " << k << endl;
                // No wall in this direction
                if (!(node_stat[node_id].walls & DIRECTION_MASK[k]))
                    continue;
                // Neighbor node exits the castle
                int new_i = i+DIRECTION_OFFSET[k][0];
                int new_j = j+DIRECTION_OFFSET[k][1];
                if (!(0 <= new_i && new_i < ROW_NUM
                    && 0 <= new_j && new_j < COL_NUM))
                    continue;
                // This is the same room
                int neighbor_comp_id = node_stat[new_i*COL_NUM+new_j].component_id;
                if (neighbor_comp_id == component_id)
                    continue;
                // Test max
                int merged_size = component_size[neighbor_comp_id] + component_size[component_id];
                if (merged_size > mergeinfo.size) {
                    mergeinfo = {merged_size, i, j, k};
                }
            }
        }
    }
    return mergeinfo;
}

int main(int argc, char const *argv[])
{
    ifstream fin {"castle.in"};
    fin >> COL_NUM >> ROW_NUM;

    for (int i = 0; i < ROW_NUM; ++i)
        for (int j = 0; j < COL_NUM; ++j) {
            NodeStat ns;
            fin >> ns.walls;
            node_stat.push_back(ns);
        }

    int component_cnt = 0;
    for (int i = 0; i < ROW_NUM; ++i) {
        for (int j = 0; j < COL_NUM; ++j) {
            if (node_stat[i*COL_NUM+j].component_id == -1) {
                component_size.push_back(0);
                find_component(i, j, component_cnt++);
            }
        }
    }

    ofstream fout {"castle.out"};
    fout << component_cnt << endl;
    fout << *max_element(component_size.begin(), component_size.end()) << endl;

    MaxMergedInfo mergeinfo = find_max_size_merged_compoment();
    fout << mergeinfo.size << endl;
    fout << mergeinfo.i+1 << " " << mergeinfo.j+1
        << " " << DIRECTION_CHAR[mergeinfo.direction_id] << endl;

    return 0;
}
