/*
ID: zhangwt1
PROG: namenum
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Range
{
    char begin;
    char end;
};

Range digit_ranges[10] = {
    {'0', '0'}, //0
    {'0', '0'}, //1
    {'A', 'C'}, //2
    {'D', 'F'}, //3
    {'G', 'I'}, //4
    {'J', 'L'}, //5
    {'M', 'O'}, //6
    {'P', 'S'}, //7
    {'T', 'V'}, //8
    {'W', 'Y'}  //9
};

bool is_valid_name(const string& digits, const string& name)
{
    if (digits.length() != name.length())
    {
        return false;
    }
    for (string::size_type i = 0; i < digits.length(); ++i)
    {
        int k = digits[i] - '0';
        if (name[i] == 'Q' || name[i] == 'Z'
                || name[i] < digit_ranges[k].begin
                || digit_ranges[k].end < name[i])
        {
            return false;
        }
    }
    return true;
}

int main()
{
    ifstream fin{"namenum.in"};
    ofstream fout{"namenum.out"};

    string digits;
    fin >> digits;

    ifstream dict{"dict.txt"};
    string name;
    bool none = true;
    while (dict.good())
    {
        dict >> name;
        if (is_valid_name(digits, name))
        {
            fout << name << endl;
            none = false;
        }
    }
    if (none)
    {
        fout << "NONE" << endl;
    }
}
