#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int next_higher_num(int num)
{
    string ns = to_string(num);

    int left = -1, pos;
    for (int i = ns.length()-1; i > 0; --i)
    {
        int j;
        for (j = i-1; j >= 0 && ns[j] >= ns[i]; --j)
        {}
        if (j >= 0 && j > left)
        {
            left = j;
            pos = i;
        }
    }

    if (left == -1) return num;
    swap(ns[left], ns[pos]);
    sort(ns.begin()+left+1, ns.end());
    return stoi(ns);
}

int main()
{
    int num = 12345, next;
    cout << num << endl;
    while ((next = next_higher_num(num)) > num)
    {
        cout << next << endl;
        num = next;
    }
    return 0;
}