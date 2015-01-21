/*
ID: zhangwt1
PROG: milk
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

struct Milk {
    int price;
    int num;

    Milk(int price, int num) : price(price), num(num) {}

    bool operator < (const Milk& milk) const {
        return this->price < milk.price;
    }
};

int calc_cost(const int demand, const vector<Milk>& milks) {
    int got = 0;
    int cost = 0;
    for (const Milk& milk : milks) {
        if (got < demand) {
            int add = min(demand-got, milk.num);
            got += add;
            cost += add * milk.price;
        } else {
            return cost;
        }
    }
    return cost;
}

int main()
{
    ifstream fin {"milk.in"};
    ofstream fout {"milk.out"};

    int demand, farmer_num;
    fin >> demand >> farmer_num;

    vector<Milk> milks;
    for (int i = 0; i < farmer_num; ++i) {
        int price, available;
        fin >> price >> available;
        milks.emplace_back(price, available);
    }

    sort(milks.begin(), milks.end());

    int cost = calc_cost(demand, milks);
    fout << cost << endl;
}

