#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Node
{
    string value;
    Node** next; 
    Node(int R) : value(""), next(new Node*[R]) {
        for (int i = 0; i < R; ++i) {
            next[i] = NULL;
        }
    }
    ~Node() {
        delete[] next;
    }
};

class Trie
{
public:
    Trie(int R) : R_(R), root_(NULL) {}
    ~Trie() {}

    void put(const string& key, const string& value);
    pair<bool, int> get(const string& key);
    vector<pair<string, string>> keyValues();
private:
    int R_;
    Node* root_;
    void collect(Node* x, string& pre, vector<pair<string, string>>& v); 
    
};

void Trie::put(const string& key, const string& value) {
    if(value == "") {
        cerr << "value must be non-empty string" << endl;
        return;
    }
    Node** p = &root_;
    // For each char in key, we get the address of
    // the link that represents this char.
    // Initially, the address of link that represents
    // nothing is NULL.
    for (int i = 0; i < key.length(); ++i) {
        if (*p == NULL) {
            *p = new Node(R_);
        }
        p = (*p)->next + (unsigned)(key[i]);
    }
    // Now i == key.length(), we've got the address the
    // link that represents the last char in key.
    // We set the value of the node refered by the link
    // to @value.
    if (*p == NULL) {
        *p = new Node(R_);
    }
    (*p)->value = value;
}

vector<pair<string, string>> Trie::keyValues() {
    vector<pair<string, string>> v;
    string pre = "";
    collect(root_, pre, v);
    return v;
}

void Trie::collect(Node* x, string& pre, vector<pair<string, string>>& v) {
    if (x == NULL) {
        return;
    }
    if (x->value != "") {
        v.push_back(make_pair(pre, x->value));
    }
    for (int i = 0; i < R_; ++i) {
        pre.push_back((unsigned char)i);
        collect(x->next[i], pre, v);
        pre.erase(pre.end()-1, pre.end());
    }
    return;
}

int main() {
    vector<string> keys     = {"she", "sells", "sea", "shells", "by", "the", "sea", "shore"};
    vector<string> values   = {"0",   "1",     "2",   "3",       "4",  "5",  "6",   "7"};

    Trie t(256);
    for (int i = 0; i < keys.size(); ++i) {
        t.put(keys[i], values[i]);
    }

    vector<pair<string, string>> tkeys = t.keyValues();
    for (auto p : tkeys) {
        cout << "(" << p.first << ", " + p.second + ") ";
    }
    cout << endl;

    return 0;
}








