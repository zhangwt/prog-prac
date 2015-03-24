#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <assert.h>
using namespace std;

vector<string> digits{"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
vector<string> dupnames{"", "", "double", "triple", "quadruple", "quintuple", "sextuple", 
        "septuple", "octuple", "nonuple", "decuple"};

int main()
{
    ifstream fin{"A-small-practice.in"};
    ofstream fout{"A-small-practice.out"};
    int T;
    fin >> T;

    for (int caseid = 1; caseid <= T; ++caseid)
    {
        string phone, format;
        fin >> phone >> format;
        fout << "Case #" << caseid << ": ";

        int pstart = 0;
        bool firstprint = true; //XXX what to use as flag
        for (int f = 0; f != format.length();)
        {
            if (f != 0) f += 1; //skip the '-'
            string seglen;
            seglen.push_back(format[f++]);
            //XXX remember to test f != format.length()
            if (f != format.length() && format[f] != '-') seglen.push_back(format[f++]);

            int len = stoi(seglen);
            int pend = pstart + len;
            for (int i = pstart; i != pend;)
            {
                int j = i + 1;
                int dup = 1;
                while (j != pend && phone[j] == phone[i])
                {
                    dup += 1;
                    j += 1;
                }
                assert(dup >= 1);
                if (!firstprint) fout << " ";
                if (firstprint) firstprint = !firstprint;
                if (dup == 1)
                {
                    fout << digits[phone[i]-'0'];
                }
                else if (1 < dup && dup <= 10)
                {
                    fout << dupnames[dup] << " ";
                    fout << digits[phone[i]-'0'];
                }
                else
                {
                    for (int k = 0; k != dup; ++k) 
                    {
                        if (k != 0) fout << " ";
                        fout << digits[phone[i]-'0'];
                    }
                }

                i = j;
            }

            pstart = pend; //XXX don't miss this
        }

        fout << endl; //XXX don't miss this
    }

    return 0;
}