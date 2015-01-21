#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> v {1,2,3,4};
    if (v.end()+1 > v.end())
        cout << "v.end()+1 > v.end()" << endl;
    if (v.end()+1 > v.end()-2)
        cout << "v.end()+1 > v.end()-2" << endl;
    if (v.end()+1 > v.begin())
        cout << "v.end()+1 > v.begin()" << endl;
    if (v.begin()-1 < v.begin())
        cout << "v.begin()-1 < v.begin()" << endl;
    if (v.begin()-1 < v.begin()+1)
        cout << "v.begin()-1 < v.begin()+1" << endl;
    if (v.begin()-1 < v.end())
        cout << "v.begin()-1 < v.end()" << endl;
    if (v.begin()-1 < v.end()+1)
        cout << "v.begin()-1 < v.end()+1" << endl;

    cout << endl;
    if (v.rbegin() > v.rend())
        cout << "" << endl;
    else if (v.rbegin() == v.rend())
        cout << "v.rbegin() == v.rend()" << endl;
    else
        cout << "v.rbegin() < v.rend()" << endl;
    if (v.rbegin()-1 < v.rend()+1)
        cout << "v.rbegin()-1 < v.rend()+1" << endl;
    if (v.rbegin()+1 < v.rend()-1)
        cout << "v.rbegin()+1 < v.rend()-1" << endl;

    cout << endl;
    for (vector<int>::reverse_iterator ri = v.rbegin();
            ri != v.rend();
            ri++)
    {
        cout << *ri << endl;
    }
}
