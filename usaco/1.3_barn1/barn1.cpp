/*
ID: zhangwt1
PROG: barn1
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct Stall
{
    bool hascow;
    bool covered;
};

struct Gap
{
    int start;
    int end;
};

bool operator < (const Gap& lhs, const Gap& rhs)
{
    return lhs.end-lhs.start < rhs.end-rhs.start;
}

class GapComp
{
    private:
        bool greater;
    public:
        GapComp(bool greater=false) : greater(greater) {}
        bool operator() (const Gap& lhs, const Gap& rhs) const
        {
            if (greater)
                return rhs < lhs;
            return lhs < rhs;
        }
};

int covered_stalls(const vector<Stall>& stalls)
{
    int i = 0;
    for (const Stall& stall : stalls) {
        if (stall.covered) ++i;
    }
    return i;
}

void cover_hascow(vector<Stall>& stalls)
{
    for (Stall& stall:stalls) {
        if (stall.hascow)
            stall.covered = true;
    }
}

void cover_stall(vector<Stall>& stalls, const Gap& gap)
{
    for (int i = gap.start; i < gap.end; ++i) {
        stalls[i].covered = true;
    }
}

int cover_min_gaps(vector<Stall> &stalls, const int max_segs)
{
    priority_queue<Gap, vector<Gap>, GapComp> gap_pq {GapComp(true)};
    int segs = 0;

    int stall_start = 0, stall_end = stalls.size();
    while (stall_start < stall_end && !stalls[stall_start].hascow) ++stall_start;
    while (stall_end > stall_start && !stalls[stall_end-1].hascow) --stall_end;

    int i = stall_start;
    while (i < stall_end) {
        segs += 1;
        while (i < stall_end && stalls[i].hascow) ++i;

        if (i < stall_end) {
            Gap gap {i, i};
            while (i < stall_end && !stalls[i].hascow) ++i;
            gap.end = i;
            gap_pq.push(gap);
        }
    }

    while (segs > max_segs) {
        cover_stall(stalls, gap_pq.top());
        gap_pq.pop();
        segs -= 1;
    }
    return covered_stalls(stalls);
}

//XXX actually an priority_queue of gap is not necessary
int cover_min_gaps_2(vector<Stall> &stalls, const int max_segs)
{
    vector<Gap> gaps {};
    int segs = 0;

    int stall_start = 0, stall_end = stalls.size();
    while (stall_start < stall_end && !stalls[stall_start].hascow) ++stall_start;
    while (stall_end > stall_start && !stalls[stall_end-1].hascow) --stall_end;

    for (int i = stall_start; i < stall_end;) {
        segs += 1;
        while (i < stall_end && stalls[i].hascow) ++i;

        if (i < stall_end) {
            Gap gap {i, i};
            while (i < stall_end && !stalls[i].hascow) ++i;
            gap.end = i;
            gaps.push_back(gap);
        }
    }

    sort(gaps.begin(), gaps.end(), GapComp(false));

    for (int i = 0; segs > max_segs;) {
        cover_stall(stalls, gaps[i++]);
        segs -= 1;
    }
    return covered_stalls(stalls);
}

int main()
{
    ifstream fin {"barn1.in"};
    ofstream fout {"barn1.out"};

    int max_segs, stall_num, cow_num;
    fin >> max_segs >> stall_num >> cow_num;

    vector<Stall> stalls {static_cast<vector<Stall>::size_type>(stall_num)};
    for (int i = 0; i < cow_num; ++i) {
        int cow_pos;
        fin >> cow_pos;
        //XXX notice that raw input starts from 1,
        //while vector index starts from 0.
        stalls[cow_pos-1].hascow = true;
    }

    cover_hascow(stalls);
    //int length = cover_min_gaps(stalls, max_segs);
    int length = cover_min_gaps_2(stalls, max_segs);

    fout << length << endl;
}
