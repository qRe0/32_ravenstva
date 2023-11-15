#include <iostream>
#include <vector>

using namespace std;


// int a[100001], b[100001];
// char type[100001];

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

    void Union(int x, int y) {
        int temp_x = FindSet(x), temp_y = FindSet(y);
        if (temp_x == temp_y)
            return;
        if (dim[temp_x] < dim[temp_y]) {
            parent[temp_x] = temp_y;
            dim[temp_y] += dim[temp_x];
        }
        else {
            parent[temp_y] = temp_x;
            dim[temp_y] += dim[temp_x];
        }
    }

    bool isConnected(int x, int y) {
        return FindSet(x) == FindSet(y);
    }
};

int main() {
    FILE* f;
    fopen_s(&f, "equal-not-equal.in", "r");
    freopen("equal-not-equal.out", "w", stdout);

    int n, m;
    fscanf(f, "%d", &n);
    fscanf(f, "%*c%d", &m);

    const char equal = '=';
    const char some = ' ';
    DSU dsu(n + 2);
    for (int i = 0; i < m; i++) {
        fscanf(f, "\n", some);
        fscanf(f, "%*c %d", &a[i]);
        fscanf(f, "%c", &some);
        fscanf(f, "%c ", &type[i]);
        fscanf(f, "%c", &some);
        fscanf(f, "%c", &some);
        fscanf(f, "%c", &some);
        fscanf(f, "%d", &b[i]);

        if (type[i] == equal) {
            dsu.Union(b[i], a[i]);
            dsu.Union(a[i], b[i]);
        }
    }

    bool result = true;
    for (int i = 0; i < m; i++) {

        if (type[i] == equal) {
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

    cout << (result ? "Yes" : "No") << endl;

    return 0;
}
