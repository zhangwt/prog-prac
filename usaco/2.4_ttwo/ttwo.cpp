/*
ID: zhangwt1
PROG: ttwo
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

const int N = 10;
char map[N*N] = {};

bool onestep(int& i, int& j, int& facing)
{
    int nexti = i, nextj = j;
    if (facing == 0) {
        nexti -=1;
    }
    else if (facing == 1) {
        nextj += 1;
    }
    else if (facing == 2) {
        nexti += 1;
    }
    else if (facing == 3) {
        nextj -= 1;
    }
    else {
        cerr << "invalid facing " << (int)facing << endl;
        return false;
    }

    if (nexti < 0 || nexti >= N || nextj < 0 || nextj >= N
            || map[nexti*N+nextj] == '*')
    {
        facing = (facing+1)%4;
        return false;
    }
    else {
        i = nexti; j = nextj;
        return true;
    }
}

int main()
{
    int cowi, cowj, cowfacing;
    int farmeri, farmerj, farmerfacing;
    bool footprint[4*N*N*4*N*N] = {false};

    ifstream fin{"ttwo.in"};
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            fin >> map[i*N+j];
            if (map[i*N+j] == 'C') {
                cowi = i; cowj = j; cowfacing = 0;
            }
            if (map[i*N+j] == 'F') {
                farmeri = i; farmerj = j; farmerfacing = 0;
            }
        }
    }

    int steps = 0;
    while(true) {
        if (cowi == farmeri && cowj == farmerj) {
            break;
        }

        int fpi = (cowi*N+cowj)*4+cowfacing;
        int fpj = (farmeri*N+farmerj)*4+farmerfacing;
        //cout << "cowi:" << cowi << ", cowj:" << cowj << ", cowfacing:" << cowfacing << endl;
        //cout << "farmeri:" << farmeri << ", farmerj:" << farmerj << ", farmerfacing:" << farmerfacing << endl;
        //cout << "fpi:" << fpi << ", fpj:" << fpj << endl;
        //cout << "fpi*4*N*N+fpj:" << (fpi*4*N*N+fpj) << endl << endl;
        if (footprint[fpi*4*N*N+fpj]) {
            cout << "steps=" << steps << endl;
            steps = 0;
            break;
        }
        footprint[fpi*4*N*N+fpj] = true;

        onestep(cowi, cowj, cowfacing);
        onestep(farmeri, farmerj, farmerfacing);
        steps += 1;
    }

    ofstream fout{"ttwo.out"};
    fout << steps << endl;

    return 0;
}
