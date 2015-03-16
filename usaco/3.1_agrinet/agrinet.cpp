/*
ID: zhangwt
PROG: agrinet
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <assert.h>
using namespace std;

int primMsp(int N, const vector<int>& adj)
{
    vector<int> min_edges(N, -1); // Use -1 for infinity
    vector<int> min_edge_srcs(N, -1);
    vector<bool> in_tree(N, false);

    in_tree[0] = true;
    for (int i = 0; i != N; ++i) {
        min_edges[i] = adj[0*N+i];
        min_edge_srcs[i] = 0;
    }

    int msp_cost = 0;
    for (int treesize = 1; treesize != N; ++treesize) {
        int min_dist = -1;
        int min_dst = -1;
        for (int i = 0; i != N; ++i) {
            if (!in_tree[i] && min_edges[i] != -1
                    && (min_dist == -1 || min_edges[i] < min_dist))
            {
                min_dist = min_edges[i];
                min_dst = i;
            }
        }
        //cout << "min_dst:" << min_dst << ", min_dist:" << min_dist << endl;
        assert(min_dst != -1);
        in_tree[min_dst] = true;
        msp_cost += min_dist;
        for (int i = 0; i != N; ++i) {
            if (!in_tree[i] && adj[min_dst*N+i] != -1
                    && (min_edges[i] == -1 || adj[min_dst*N+i] < min_edges[i]))
            {
                min_edges[i] = adj[min_dst*N+i];
                min_edge_srcs[i] = min_dst;
                //cout << "update min_edges[" << i << "] to adj[" << min_dst << "][" << i << "]:" << adj[min_dst*N+i] << endl;
            }
        }
    }
    return msp_cost;
}

int main()
{
    int N;
    vector<int> adj;

    ifstream fin{"agrinet.in"};
    fin >> N;
    adj.resize(N*N);
    for (int i = 0; i != N; ++i) {
        for (int j = 0; j != N; ++j) {
            fin >> adj[i*N+j];
        }
    }

    ofstream fout{"agrinet.out"};
    fout << primMsp(N, adj) << endl;

    return 0;
}