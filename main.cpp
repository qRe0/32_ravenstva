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

    vector<int> parent;
    vector<int> dim;

public:

    DSU(int n) {
        for (int i = 0; i < n; i++) {
            parent.push_back(i);
            dim.push_back(1);
        }
    }

    int FindSet(int x) {
        if (parent[x] == x)
            return x;
        return parent[x] = FindSet(parent[x]);
    }

    void UnionSet(int x, int y) {
        int buff_x = FindSet(x), buff_y = FindSet(y);
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

    void processInput(const string &line) {
        regex pattern(R"(x(\d+)\s*([=!]+)\s*x(\d+))");
        smatch matches;
        if (regex_match(line, matches, pattern)) {
            int x1 = stoi(matches[1]);
            char op = matches[2].str()[0];
            int x2 = stoi(matches[3]);
        }
    }

};

int main() {
    FILE *f;
    fopen_s(&f, "equal-not-equal.in", "r");
    ofstream out("equal-not-equal.out", ios_base::out);

    int n, m;

    fscanf(f, "%d", &n);
    fscanf(f, "%*c%d", &m);

    DSU dsu(n + 2);

    for (int i = 0; i < m; i++) {

        //Format: x1 == x2
        fscanf(f, "\n%*c %d%*c", &a[i]);    // ignore "\n" and "x", then read "1" and ignore space
        fscanf(f, "%c %*c%*c", &type[i]);   // read "=", then ignore second char from expression and space
        fscanf(f, "%*c %d", &b[i]);         // ignore "x" and read "2"

        if (type[i] == '=') {
            dsu.UnionSet(b[i], a[i]);
            dsu.UnionSet(a[i], b[i]);
        }
    }

    bool result = true;
    for (int i = 0; i < m; i++) {

        if (type[i] == '=') {
            if (!dsu.isConnected(a[i], b[i]) || !dsu.isConnected(b[i], a[i])) {
                result = false;
                break;
            }
        } else {
            if (dsu.isConnected(a[i], b[i]) || dsu.isConnected(b[i], a[i])) {
                result = false;
                break;
            }
        }
    }

    out << (result ? "Yes" : "No") << endl;

    out.close();
    return 0;
}