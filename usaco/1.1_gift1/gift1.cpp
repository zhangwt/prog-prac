/*
ID: zhangwt1
PROG: gift1
LANG: C++11
*/

#include <fstream>
#include <vector>
#include <unordered_map>
using namespace std;

struct Note
{
    int origin;
    int now;
};

int main()
{
    ifstream fin {"gift1.in"};
    ofstream fout {"gift1.out"};

    unordered_map<string, Note> res;
    vector<string> names;

    int number;
    fin >> number;

    for(int i = 0; i != number; ++i)
    {
        string name;
        fin >> name;
        names.push_back(name);
        res[name] = Note{0, 0};
    }

    for(int i = 0; i != number; ++i)
    {
        string name;
        fin >> name;

        int money, divide;
        fin >> money >> divide;
        // give the variables a valide value
        // or there might be more logic path needed
        int gift = divide ? money/divide : 0;
        int left = money - gift*divide;

        res[name].origin = money;
        res[name].now += left;
        for(int j = 0; j != divide; ++j)
        {
            string receiver;
            fin >> receiver;
            res[receiver].now += gift;
        }
    }

    for(auto &name : names)
    {
        Note& note = res[name];
        fout << name << " " << (note.now - note.origin) << endl;
    }

    return 0;
}

