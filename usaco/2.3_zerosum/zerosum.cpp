/*
ID: zhangwt1
PROG: zerosum
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <assert.h>
using namespace std;

const int MAX_N = 9;
int N;
char expr[1 + MAX_N + MAX_N-1 + 1] = {};
char signs[3] = {' ', '+', '-'};

void check_expr(ofstream& fout)
{
    int res = 0;
    char sign = '+';
    int next_num = 0;
    for (int i = 1; i != 2*N+1; ++i) {
        if (expr[i] == '+' || expr[i] == '-' || i == 2*N) {
            assert(sign == '+' || sign == '-');
            if (sign == '+') {
                res += next_num;
            }
            else {
                res -= next_num;
            }
            sign = expr[i];
            next_num = 0;
        }
        else if ('1' <= expr[i] && expr[i] <= '9') {
            next_num += (expr[i]-'0');
        }
        else if (expr[i] == ' ') {
            next_num *= 10;
        }
        else {
            cerr << "unexpected character: " << expr[i] << endl;
            return;
        }
    }
    if (res == 0) {
        //cout << (expr+1) << endl;
        fout << (expr+1) << endl;
    }
    return;
}

void enumeration(int expr_start, int left_signs, ofstream& fout)
{
    if (left_signs == 0) {
        check_expr(fout);
        return;
    }

    for (int i = 0; i != 3; ++i) {
        expr[expr_start] = signs[i];
        enumeration(expr_start+2, left_signs-1, fout);
    }
}

int main()
{
    ifstream fin{"zerosum.in"};
    fin >> N;

    for (int i = 1; i <= N; ++i) {
        expr[2*i-1] = '0' + i;
    }

    ofstream fout{"zerosum.out"};
    enumeration(2, N-1, fout);

    return 0;
}