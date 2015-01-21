/*
ID: zhangwt1
PROG: friday
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

// month idx:              0  1   2   3   4   5   6   7   8   9  10  11
const int month_days[] = {31, 0, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int days_of_month(int year, int month)
{
    if (month != 1)
        return month_days[month];
    if ((year%4 == 0 && year%100 != 0) || year%400 == 0)
        return 29;
    else
        return 28;
}

int main()
{
    ifstream fin{"friday.in"};
    ofstream fout{"friday.out"};

    int n;
    fin >> n;
    int end_year = 1900 + n-1, end_month = 11;

    // freq[0] for monday, freq[6] for sunday
    vector<int> freq(7, 0);

    // the first month
    int last_wday = 0, days = 12;
    int wday = (last_wday + days) % 7;
    freq[wday] += 1;
    last_wday = wday;

    // 0 for Jan, 11 for Dec
    int year = 1900, month = 0;
    while (year != end_year || month != end_month)
    {
        int days = days_of_month(year, month) - 13 + 13;
        int wday = (last_wday + days) % 7;
        freq[wday] += 1;
        last_wday = wday;

        if (month == 11)
            year++;
        month = (month+1) % 12;
    }

    for (int wday = 5, i = 0; i != 7; i++)
    {
        fout << freq[wday];
        wday = (wday+1) % 7;
        if (i != 6)
            fout << " ";
    }
    fout << endl;
}


