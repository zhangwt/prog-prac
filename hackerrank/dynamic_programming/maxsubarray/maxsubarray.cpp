#include <iostream>
#include <algorithm>
using namespace std;

void maxsubarray()
{
    int N;
    cin >> N;

    int ele;
    cin >> ele;

    int csum_max = ele;
    int csum_pre = ele;

    int max_negtive_ele;
    int ncsum;
    if (ele >= 0)
    {
        ncsum = ele;
        max_negtive_ele = 0;
    }
    else
    {
        ncsum = 0;
        max_negtive_ele = ele;
    }

    for (int i = 1; i != N; ++i)
    {
        cin >> ele;

        int csum = ele;
        if (csum_pre > 0)
        {
            csum = csum_pre + ele;
        }
        csum_max = max(csum_max, csum);
        csum_pre = csum;

        if (ele >= 0)
        {
            ncsum += ele;
            max_negtive_ele = 0;
        }
        else
        {
            if (max_negtive_ele < 0)
            {
                max_negtive_ele = max(max_negtive_ele, ele);
            }
        }
    }

    ncsum = max_negtive_ele < 0 ? max_negtive_ele : ncsum;
    cout << csum_max << " " << ncsum << "\n";
}

int main()
{
    int T;
    cin >> T;
    for (int i = 0; i != T; ++i)
    {
        maxsubarray();
    }
    return 0;
}