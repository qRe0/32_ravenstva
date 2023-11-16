#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include <string>

using namespace std;

vector<int> a(100001);
vector<int> b(100001);
vector<char> type(100001);

class DSU {

private:
    vector<int> dim;
    vector<int> parent;

public:

    DSU(int n) {
        for (int i = 0; i < n; i++) {
            parent.push_back(i);
            dim.push_back(1);
        }
    }

    int FindSet(int x) {
        if (x == parent[x])
            return x;
        parent[x] = FindSet(parent[x]);
        return parent[x];
    }

    void Union(int x, int y) {
        int buff_x = FindSet(x);
        int buff_y = FindSet(y);

        if (buff_x == buff_y)
            return;
        if (dim[buff_x] < dim[buff_y]) {
            parent[buff_x] = buff_y;
            dim[buff_y] += dim[buff_x];
        } else {
            parent[buff_y] = buff_x;
            dim[buff_y] += dim[buff_x];
        }
    }

    bool isConnected(int x, int y) {
        return FindSet(x) == FindSet(y);
    }

};

int main() {
    ifstream in("equal-not-equal.in");
    ofstream out("equal-not-equal.out");

    int n, m;
    in >> n >> m;

    DSU dsu(n + 2);

    for (int i = 0; i < m; i++) {

        char c;
        in >> c >> a[i] >> type[i] >> c >> c >> b[i];

        if (type[i] == '=') {
            dsu.Union(b[i], a[i]);
            dsu.Union(a[i], b[i]);
        }
    }

    bool result = true;
    for (int i = 0; i < m; i++) {

        if (type[i] == '=') {
            if (!dsu.isConnected(a[i], b[i]) || !dsu.isConnected(b[i], a[i])) {
                result = false;
                break;
            }
        } else if (type[i] == '!') {
            if (dsu.isConnected(a[i], b[i]) || dsu.isConnected(b[i], a[i])) {
                result = false;
                break;
            }
        }
    }

    out << (result ? "Yes" : "No") << endl;

    return 0;
}
