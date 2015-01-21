/*
ID: zhangwt1
PROG: crypt1
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <algorithm>
using namespace std;

inline int num_digits(int num)
{
    int i = 0;
    do {
        num /= 10;
        i += 1;
    } while (num > 0);
    return i;
}

inline bool digits_of_num_in_set(unordered_set<int> digit_set, int number)
{
    do {
        if (digit_set.find(number%10) == digit_set.end())
            return false;
        //cout << number%10 << endl;
        number /= 10;
    } while (number > 0);
    return true;
}

int crypt1(vector<int>& digits, unordered_set<int>& digit_set)
{
    int cnt = 0;

    // The "***" number, i1 - most significant digit
    for (int i1 = 0; i1 < digits.size(); ++i1) {
        for (int i2 = 0; i2 < digits.size(); ++i2) {
            for (int i3 = 0; i3 < digits.size(); ++i3) {

                bool break_d2 = false;
                int d3 = digits[i1]*100 + digits[i2]*10 + digits[i3];

                // The "**" number, j1 = most significant digit
                for (int j1 = 0; j1 < digits.size() && !break_d2; ++j1) {
                    int res1 = digits[j1] * d3;
                    if (num_digits(res1) > 3)
                        break;
                    if (!digits_of_num_in_set(digit_set, res1))
                        continue;

                    for (int j2 = 0; j2 < digits.size(); ++j2) {
                        int res2 = digits[j2] * d3;
                        if (num_digits(res2) > 3)
                            break;
                        if (!digits_of_num_in_set(digit_set, res2))
                            continue;

                        int res = res1*10 + res2;
                        if (num_digits(res) > 4) {
                            //XXX we SHOULD NOT "return cnt" here
                            break_d2 = true;
                            break;
                        }
                        if (digits_of_num_in_set(digit_set, res)) {
                            cnt += 1;
                        }
                    }
                }

            }
        }
    }

    return cnt;
}

int main()
{
    ifstream fin {"crypt1.in"};
    ofstream fout {"crypt1.out"};

    int N;
    fin >> N;

    // XXX vector<int> digits {N};
    // doesn't reserve N slots in digits,
    // instead putting N initial value (0 if not specified) in digits
    vector<int> digits {};
    for (int i = 0; i < N; ++i) {
        int d;
        fin >> d;
        digits.push_back(d);
    }

    sort(digits.begin(), digits.end());
    unordered_set<int> digit_set {digits.begin(), digits.end(),
        static_cast<unordered_set<int>::size_type>(N)};

    //for (const int &v:digits) {
    //    cout << v << endl;
    //}
    //cout << endl;

    //for(const int &v:digit_set) {
    //    cout << v << endl;
    //}
    //cout << endl;

    fout << crypt1(digits, digit_set) << endl;
}
