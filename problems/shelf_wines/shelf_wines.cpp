#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int wines(int N, int price[])
{
    vector<int> profits1(N, 0);
    vector<int> profits2(N, 0);

    vector<int> *pprofits1 = &profits1, *pprofits2 = &profits2;

    for (int i = 0; i != N; ++i)
    {
        (*pprofits1)[i] = price[i]*(N-1+1);
    }

    for (int nw = 2; nw <= N; ++nw)
    {
        int year = N-nw+1;
        for (int start = 0; start <= N-nw; ++start)
        {
            (*pprofits2)[start] = max(
                    year*price[start] + (*pprofits1)[start+1],
                    year*price[start+nw-1] + (*pprofits1)[start]);
        }
        swap(pprofits1, pprofits2);
    }

    return (*pprofits1)[0];
}

int main()
{
    int price[] = {2, 3, 5, 1, 4};
    int N = sizeof(price)/sizeof(int);
    cout << wines(N, price) << "\n";
    return 0;
}
