/*
ID: zhangwt1
PROG: wormhole
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <algorithm>
using namespace std;

const bool D = false;
const bool E = false;

struct Point {
    int x;
    int y;
    Point(int x, int y) : x(x), y(y) {}
    bool operator <(const Point& other) const {
        if (y != other.y)
            return y < other.y;
        else
            return x < other.x;
    }
};

vector<Point> points;

bool has_cycle(const vector<int>& pids)
{
    vector<int> paired_pids(pids.size());
    for (size_t i = 0; i < pids.size()/2; ++i) {
        paired_pids[pids[2*i]] = pids[2*i+1];
        paired_pids[pids[2*i+1]] = pids[2*i];
    }

    vector<bool> g_visited(points.size());
    size_t idx = 0;
    while (true) {
        while (idx < points.size() && (points[idx].x == 0 || g_visited[idx]))
            ++idx;
        if (idx == points.size()) return false;

        //XXX we have to use two vector of visited[],
        // because g_visited[idx]=true in a certain path
        // doesn't indicate that there is a cycle,
        // thus we have to have a fresh visited[] on each path
        vector<bool> visited(points.size());
        if (E) cout << "enter: " << idx << endl;
        visited[idx] = g_visited[idx] = true;
        size_t idx_c = idx;

        while (true) {
            int another_pid = paired_pids[idx];
            if (E) cout << "exit: " << another_pid << endl;
            if (another_pid == int(points.size())
                    || points[another_pid+1].y != points[another_pid].y)
                break;

            idx = another_pid+1;
            if (E) cout << "enter: " << idx << endl;
            if (visited[idx]) return true;
            if (g_visited[idx]) break;
            visited[idx] = g_visited[idx] = true;
        }

        idx = idx_c + 1;
    }
}

int solu_num = 0;

unordered_set<int> g_bag;
vector<int> g_array;

void hole_combinations(int set_size)
{
    if (set_size == 0) {
        if (E) {
            for (int v:g_array)
                cout << v << "\t";
            cout << endl;
        }
        if (has_cycle(g_array))
            solu_num += 1;
        return;
    }

    int first = *g_bag.begin();
    g_array.push_back(*g_bag.begin());
    g_bag.erase(g_bag.begin());

    if (D) {
        cout << "first: " << first << endl;
        cout << "g_bag after erase() begin: ";
        for (auto it = g_bag.begin(); it != g_bag.end(); ++it)
            cout << *it << "\t";
        cout << endl;
    }

    vector<int> anothers;
    for (auto it = g_bag.begin(); it != g_bag.end(); ++it)
        anothers.push_back(*it);

    if (D) {
        cout << "anothers[]: ";
        for (int v:anothers)
            cout << v << "\t";
        cout << endl;
    }

    for (size_t i = 0; i != anothers.size(); ++i) {
        if (D) cout << "second: " << anothers[i] << endl;

        g_array.push_back(anothers[i]);
        g_bag.erase(anothers[i]);

        hole_combinations(set_size-2);

        g_bag.insert(anothers[i]);
        g_array.pop_back();
    }

    g_bag.insert(first);
    g_array.pop_back();
}

int main()
{
    ifstream fin {"wormhole.in"};
    ofstream fout {"wormhole.out"};

    int N;
    fin >> N;
    for (int i = 0; i < N; ++i) {
        int x,y;
        fin >> x >> y;
        points.emplace_back(x, y);
    }
    sort(points.begin(), points.end());

    if (E) {
        for (size_t i = 0; i < points.size(); ++i)
            cout << i << "-(" << points[i].x << "," << points[i].y << ") ";
        cout << endl;
    }

    for (int i = 0; i < N; ++i)
        g_bag.insert(i);
    hole_combinations(N);

    fout << solu_num << endl;
}
