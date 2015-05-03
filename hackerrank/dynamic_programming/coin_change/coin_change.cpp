#include <iostream>
#include <memory>
#include <vector>
#include <cstdint>
using namespace std;

int main()
{
    int amount, types;
    cin >> amount >> types;
    vector<int> coins(types, 0);
    for (auto &v: coins)
    {
        cin >> v;
    }

    unique_ptr<vector<uint64_t>> arr1(new vector<uint64_t>(amount+1, 0));
    unique_ptr<vector<uint64_t>> arr2(new vector<uint64_t>(amount+1, 0));

    for (int tid = 1; tid <= types; ++tid)
    {
        (*arr2)[0] = 1;
        for (int amo = 1; amo <= amount; ++amo)
        {
            uint64_t nouse = (*arr1)[amo];
            uint64_t use = (amo >= coins[tid-1]) ? (*arr2)[amo-coins[tid-1]] : 0;
            (*arr2)[amo] = nouse + use;
        }
        swap(arr1, arr2);
    }

    cout << (*arr1)[amount] << "\n";
}