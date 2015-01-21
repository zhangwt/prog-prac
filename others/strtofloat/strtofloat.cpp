#include <iostream>
#include <string>
using namespace std;

struct Ret {
    bool ok;
    string reason;
};

Ret valid_float(const string& str) {
    if (str.length() == 0)
        return Ret {false, "string length should be greater than 0."};

    size_t i = 0;
    if (str[0] == '-') {
        if (str.length() == 1)
            return Ret {false, "number length should be greater than 0."};
        i = 1;
    }

    if (str.length()-i >= 2 && str[i] == '0' && str[i+1] != '.')
        return Ret {false, "leading 0 is not allowed."};

    int dot_cnt = 0;
    for (; i < str.length(); ++i) {
        if ('0'<=str[i] && str[i]<='9')
            continue;
        if (str[i] == '.' && ++dot_cnt == 1)
            continue;
        return Ret {false, "invalid character at pos "};
    }
    if (str[str.length()-1] == '.')
        return Ret {false, "'.' can't be at the end of the string."};

    //XXX '.' at str[0] is allowed
    return Ret {true, ""};
}

double strtofloat(const string& str) {
    Ret ret = valid_float(str);
    if (!ret.ok) {
        cerr << ret.reason << endl;
        throw ret.reason;
    }

    size_t dot = str.find(".");
    if (dot == string::npos)
        dot = str.length();

    int begin = 0, sign = 1;
    if (str[0] == '-') {
        begin = 1;
        sign = -1;
    }

    double ipart = 0, iweight = 1, ifactor = 10;
    //XXX 'i' eventually would be less than 0 if begin == 0,
    // thus 'i' cann't be of type 'size_t',
    // because then 'i' would be >= begin forever.
    for (int i = dot-1; i >= begin; --i) {
        ipart += (str[i] - '0')*iweight;
        iweight *= ifactor;
    }

    double fpart = 0, fweight = 0.1, fweight_factor = 0.1;
    for (size_t i = dot+1; i < str.length(); ++i) {
        fpart += (str[i] - '0')*fweight;
        fweight *= fweight_factor;
    }

    return sign*(ipart + fpart);
}

int main(int argc, char** argv) {
    if (argc == 1) {
        cerr << "you could specify a string to be parsed as float." << endl;
        return 0;
    }

    float f = .1;

    string str {argv[1]};
    cout << strtofloat(str) << endl;
}
