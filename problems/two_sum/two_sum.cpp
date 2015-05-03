#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


struct Comp
{
  vector<int>* vec;
  Comp(vector<int>* vec) : vec(vec)
  { }
  bool operator()(int a, int b)
  {
      return (*vec)[a] < (*vec)[b];
  }
};

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> ids(nums.size(), 0);
        for (int i = 0; i < ids.size(); ++i)
        {
            ids[i] = i;
        }
        sort(ids.begin(), ids.end(), Comp{&nums});
        int b = 0, e = ids.size()-1;
        while (b < e)
        {
            int sum = nums[ids[b]] + nums[ids[e]];
            if (sum == target)
            {
                vector<int> r {ids[b]+1, ids[e]+1};
                sort(r.begin(), r.end());
                return r;
            }
            else if (sum < target)
            {
                b += 1;
            }
            else
            {
                e -= 1;
            }
        }
        return {};
    }
};

int main()
{
  vector<int> test {5, 75, 25};
  Solution s;
  vector<int> result = s.twoSum(test, 100);
  for (auto v: result)
  {
    cout << v << " ";
  }
  cout << "\n";
}
