/*
ID: zhangwt1
PROG: cowtour
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <array>
#include <string>
#include <algorithm>
#include <cmath>
using namespace std;

int N;
vector<array<int, 2>> coord;
vector<double> adjmat;

void floyd_warshall()
{
    for (int k = 0; k != N; ++k) {
        for (int i = 0; i != N; ++i) {
            for (int j = 0; j != N; ++j) {
                if (adjmat[i*N+k] != -1 && adjmat[k*N+j] != -1) {
                    double n = adjmat[i*N+k] + adjmat[k*N+j];
                    if (adjmat[i*N+j] == -1) {
                        adjmat[i*N+j] = n;
                    } else {
                        adjmat[i*N+j] = min(adjmat[i*N+j], n);
                    }
                }
            }
        }
    }
}

void find_compo(int src, vector<bool>& visited, vector<int>& compo)
{
    visited[src] = true;
    compo.push_back(src);
    for (int i = 0; i != N; ++i) {
        if (i != src && !visited[i] && adjmat[i*N+src] != -1) {
            find_compo(i, visited, compo);
        }
    }
}

void find_compos(vector<vector<int>>& compos)
{
    vector<bool> visited(N, false);
    for (int i = 0; i != N; ++i) {
        if (!visited[i]) {
            compos.emplace_back();
            find_compo(i, visited, *compos.rbegin());
        }
    }
}

double dist(int i, int j)
{
    return sqrt((coord[i][0]-coord[j][0])*(coord[i][0]-coord[j][0])
            + (coord[i][1]-coord[j][1])*(coord[i][1]-coord[j][1]));
}

double compo_diameter(vector<int>& ca)
{
    double d = 0;
    for (int i = 0; i != ca.size(); ++i) {
        for (int j = i+1; j < ca.size(); ++j) {
            d = max(d, adjmat[ca[i]*N+ca[j]]);
        }
    }
    return d;
}

double max_new_path(vector<int>& ca, vector<int>& cb, int i, int j)
{
    double maxi = 0;
    for (auto v: ca) {
        if (v != i) {
            maxi = max(maxi, adjmat[v*N+i]);
        }
    }
    double maxj = 0;
    for (auto v: cb) {
        if (v != j) {
            maxj = max(maxj, adjmat[v*N+j]);
        }
    }
    //cout << "\tmaxi:" << maxi << " maxj:" << maxj 
    //        << " dist(" << i << "," << j << "):" << dist(i, j) << endl;
    return maxi + dist(i, j) + maxj;
}

double min_diameter(vector<int>& ca, vector<int>& cb)
{
    double da = compo_diameter(ca), db = compo_diameter(cb);
    //cout << "da=" << da << ", db=" << db << endl;
    double maxab = max(da, db);
    double mind = -1;
    for (auto i: ca) {
        for (auto j: cb) {
            double m = max_new_path(ca, cb, i, j);
            double d = max(maxab, m);
            //cout << "\tconnect node(" << i << "," << j << "): m=" << m << ", d=" << d;
            if (mind == -1) {
                mind = d;
            } else {
                mind = min(mind, d);
            }
            //cout << ", mind=" << mind << endl;
        }
    }
    return mind;
}

int main()
{
    ifstream fin{"cowtour.in"};
    fin >> N;

    coord.resize(N);
    for (int i = 0; i != N; ++i) {
        fin >> coord[i][0] >> coord[i][1];
    }

    adjmat.resize(N*N);
    for (int i = 0; i != N; ++i) {
        string s;
        fin >> s;
        for (int j = 0; j != N; ++j) {
            if (i == j) {
                adjmat[i*N+j] = 0;
            }
            else if (s[j] == '1') {
                adjmat[i*N+j] = dist(i, j);
            }
            else {
                adjmat[i*N+j] = -1;
            }
        }
    }
    floyd_warshall();
    //cout << "all source shortest path:" << endl;
    //for (int i = 0; i != N; ++i) {
    //    for (int j = 0; j != N; ++j) {
    //        cout << setw(10) << adjmat[i*N+j] << " ";
    //    }
    //    cout << endl;
    //}
    //cout << endl;

    vector<vector<int>> compos;
    find_compos(compos);
    //cout << "compos:" << endl;
    //for (auto v: compos) {
    //    for (auto e: v) {
    //        cout << e << " ";
    //    }
    //    cout << endl;
    //}
    //cout << endl;

    double gmind = -1;
    for (int i = 0; i < compos.size(); ++i) {
        for (int j = i+1; j < compos.size(); ++j) {
            //cout << "connecting compos (" << i << ", " << j << "):" << endl;
            double mind = min_diameter(compos[i], compos[j]);
            //cout << "min diameter: " << mind << endl;
            if (gmind == -1) {
                gmind = mind;
            } else {
                gmind = min(gmind, mind);
            }
        }
    }

    ofstream fout{"cowtour.out"};
    fout << fixed << setprecision(6) << gmind << endl;

    return 0;
}