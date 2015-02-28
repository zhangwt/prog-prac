/*
ID: zhangwt1
PROG: comehome
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

void dijkstra(const int src, const vector<int>& mat, vector<int>& dist)
{
    int N = dist.size();
    for (int i = 0; i != N; ++i) {
        dist[i] = -1; // infinity distance
    }
    dist[src] = 0;
    vector<bool> collected(N, false);

    while (true) {
        int mindist = -1;
        int minnode = -1;
        for (int i = 0; i != N; ++i) {
            if (!collected[i] && dist[i] != -1
                    && (mindist == -1 || dist[i] < mindist))
            {
                mindist = dist[i];
                minnode = i;
            }
        }
        if (minnode == -1) break;
        collected[minnode] = true;

        for (int i = 0; i != N; ++i) {
            if (mat[minnode*N+i] != -1 && (dist[i] == -1
                    || mindist + mat[minnode*N+i] < dist[i]))
            {
                dist[i] = mindist + mat[minnode*N+i];
            }
            
        }
    }
}

int node_symtoidx(char c)
{
    return ('a' <= c && c <= 'z') ? c-'a' : c-'A'+26;
}

char node_idxtosym(int idx)
{
    return (idx < 26) ? 'a'+idx : 'A'+(idx-26);
}

int main()
{
    vector<int> mat(52*52, -1);
    ifstream fin{"comehome.in"};
    int edge_num;
    fin >> edge_num;
    for (int i = 0; i != edge_num; ++i) {
        string sc, sd;
        fin >> sc >> sd;
        int c = node_symtoidx(sc[0]), d = node_symtoidx(sd[0]);
        int dist;
        fin >> dist;
        if (mat[c*52+d] == -1 || mat[c*52+d] > dist) {
            mat[c*52+d] = mat[d*52+c] = dist;
        }
    }

    vector<int> dist(52, -1);
    int src = node_symtoidx('Z');
    dijkstra(src, mat, dist);

    int minnode = -1, mindist = -1;
    for (int i = 0; i != dist.size(); ++i) {
        if (i != src && 26 <= i && i < 51 && dist[i] != -1 
                && (mindist == -1 || dist[i] < mindist)) 
        {
            mindist = dist[i];
            minnode = i;
        }
    }
    if (minnode == -1) {
        cerr << "no path" << endl;
        return 1;
    }

    ofstream fout{"comehome.out"};
    fout << node_idxtosym(minnode) << " " << mindist << endl;
    return 0;
}
