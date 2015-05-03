#include <iostream>
#include <vector>
using namespace std;

void sum_composition(const vector<int>& nums, const int targetsum,
        int start, vector<int>& comps, int nowsum)
{
    if (nowsum == targetsum) {
        for (int comp: comps) {
            cout << comp << " ";
        }
        cout << endl;
        return;
    }
    if (nowsum > targetsum) return;
    if (start == nums.size()) return;

    comps.push_back(nums[start]);
    sum_composition(nums, targetsum, start+1, comps, nowsum+nums[start]);
    comps.erase(comps.end()-1);

    sum_composition(nums, targetsum, start+1, comps, nowsum);
}

void sum_composition_wrapper(const vector<int>& nums, const int targetsum)
{
    vector<int> comps;
    sum_composition(nums, targetsum, 0, comps, 0);
}

int main()
{
    vector<int> nums {3,9,8,4,5,7,10};
    int targetsum = 15;

    sum_composition_wrapper(nums, targetsum);
    return 0;
}
