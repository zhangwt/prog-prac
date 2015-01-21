#include <iostream>
#include <vector>
using std::cout; using std::endl;
using std::vector;

int main()
{
    vector<int> v {0, 1, 2, 3};
    cout << "v: " << v.size() << endl;

    vector<int> v2 = v;
    cout << "v: " << v.size() 
         << ", v2: " << v2.size()
         << endl;

    vector<int> v3 = std::move(v);
    cout << "v: " << v.size()
         << ", v2: " << v2.size()
         << ", v3: " << v3.size()
         << endl;

    return 0;
}


