/*
ID: zhangwt1
PROG: milk2
LANG: C++11
*/

#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

struct Seg
{
    int begin;
    int end;

    Seg(int begin, int end) : begin(begin), end(end) {}

    bool operator < (const Seg& seg) const
    {
        return this->begin < seg.begin;
    }
};

struct Res
{
    int continuous;
    int idle;
};

Res longest_continuous_and_idle(vector<Seg>& vs)
{
    Res res {0, 0};
    if (vs.size() == 0)
    {
        return res;
    }

    int cbegin = vs[0].begin, cend = vs[0].end;
    res.continuous = cend - cbegin;

    for (auto it = vs.begin()+1; it != vs.end(); ++it)
    {
        Seg& seg = *it;
        if (seg.begin > cend)
        {
            int idle = seg.begin - cend;
            res.idle = max(idle, res.idle);

            cbegin = seg.begin;
            cend = seg.end;
            res.continuous = max(cend-cbegin, res.continuous);
        }
        else
        {
            if (seg.end > cend)
            {
                cend = seg.end;
                res.continuous = max(cend-cbegin, res.continuous);
            }
        }
    }

    return res;
}

int main()
{
    ifstream fin {"milk2.in"};
    ofstream fout {"milk2.out"};

    int N;
    fin >> N;

    vector<Seg> vs;

    int begin, end;
    for(int i = 0; i < N; i++)
    {
        fin >> begin >> end;
        vs.emplace_back(begin, end);
    }

    sort(vs.begin(), vs.end());

    Res res = longest_continuous_and_idle(vs);
    fout << res.continuous << " " << res.idle << endl;

    return 0;
}
