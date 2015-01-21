/*
ID: zhangwt1
PROG: pprime
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

const bool D = false;

bool is_prime(int n);

bool palindrome(const int N, int cur_digit_idx,
        int lower_limit, int upper_limit, ofstream& fout)
{
    static int digits[20] = {};

    if (cur_digit_idx >= (N+1)/2)
    {
        int sum = 0;
        for (int i = N-1, factor = 1; i >= 0; --i) {
            sum += digits[i]*factor;
            factor *= 10;
        }
        if (lower_limit <= sum && sum <= upper_limit) {
            if (is_prime(sum)) {
                fout << sum << endl;
            }
            return false;
        } else if (sum > upper_limit) {
            return true;
        } else {
            return false;
        }
    }

    int start = 0, step = 1;
    if (cur_digit_idx == 0) {
        // Frist digit couldn't be zero
        start = 1;
        // Even number couldn't be a prime
        step = 2;
    }

    for (int i = start; i <= 9; i += step) {
        digits[cur_digit_idx] = i;
        digits[N-1-cur_digit_idx] = i;
        if (palindrome(N, cur_digit_idx+1, lower_limit, upper_limit, fout))
            return true;
    }

    return false;
}

bool is_prime(int n)
{
    if (n <= 1)
        return false;
    int stop = min((int)sqrt(n) + 1, n-1);
    for (int i = 2; i <= stop; ++i) {
        if (n % i == 0)
            return false;
    }
    return true;
}

int digits_of(int n)
{
    int digits = 0;
    do {
        n /= 10;
        digits += 1;
    } while (n);
    return digits;
}

int main()
{
    ifstream fin {"pprime.in"};
    int lower_limit, upper_limit;
    fin >> lower_limit >> upper_limit;

    ofstream fout {"pprime.out"};
    for (int i = digits_of(lower_limit); i <= digits_of(upper_limit); ++i)
        palindrome(i, 0, lower_limit, upper_limit, fout);
}

