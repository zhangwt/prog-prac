/*
ID: zhangwt1
PROG: beads
LANG: C++11
*/

#include <fstream>
#include <iostream>
#include <string>
using namespace std;

struct Seg
{
    int start;
    int colorend;
    int end;
    bool empty;

    int len(int seglen)
    {
        if(end == start)
        {
            if(empty) return 0;
            else return seglen;
        }
        else if(end >start)
            return end - start;
        else
            return seglen - start + end; 
    }
};

int solve(string &str)
{
    int k;
    for(k = 0; k != str.size() && str[k] == 'w'; k++);
    if(k == str.size()) return str.size();

    int maxlen = 0;
    Seg markx{-1, -1, -1};
    int markcnt = 0;

    Seg x{k, k, k, true};
    while(true)
    {
        Seg y{x.end, 0, 0, true};
        int i = y.start;
        for(int cnt = 0; cnt != str.size() - x.len(str.size()); ++cnt) 
        {
            y.empty = false;
            if(str[i] == str[y.start])
                y.colorend = (i+1)%str.size();
            else if(str[i] != 'w')
                break;
            i = (i+1)%str.size();
        }
        y.end = i;

#ifdef DEBUG
        cout << "xlen: " << x.len(str.size())
             << ", ylen: " << y.len(str.size())
             << endl;
#endif

        maxlen = max(maxlen, x.len(str.size()) + y.len(str.size())); 

        if(x.end == markx.end && x.empty == markx.empty)
            markcnt++;
        if(markcnt == 2)
            return maxlen;

        x = Seg{x.colorend, y.colorend, y.end, y.empty && x.end == x.colorend};
        if(markx.start == -1)
            markx = x;
    }
}

int main()
{
    ifstream fin("beads.in");
    ofstream fout("beads.out");

    int strlen;
    string str;
    fin >> strlen >> str;

    int maxlen = solve(str);
    fout << maxlen << endl;
    return 0;
}
