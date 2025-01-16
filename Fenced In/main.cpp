#include <fstream>
#include <algorithm>
#include <vector>
#include <cassert>

#define ll long long

using namespace std;

ifstream cin("fencedin.in");
ofstream cout("fencedin.out");

const int NMAX = 2000;

struct Edge {
    int x, y, cost;
    bool operator < (const Edge &other) const {
        return cost < other.cost;
    }
};

struct DSU {
    int sz[(NMAX + 1) * (NMAX + 1) + 1];
    int parent[(NMAX + 1) * (NMAX + 1) + 1];
    
    void Initialize(int n) {
        for(int i = 1; i <= n; i++) {
            parent[i] = i;
            sz[i] = 1;
        }
    }

    int GetRoot(int node) {
        return parent[node] = (parent[node] == node ? node : GetRoot(parent[node]));
    }

    bool Unite(int x, int y) {
        int root_x = GetRoot(x);
        int root_y = GetRoot(y);
        if(root_x == root_y) {
            return false;
        }

        if(sz[root_x] > sz[root_y]) {
            swap(root_x, root_y);
        }
        sz[root_y] += sz[root_x];
        parent[root_x] = root_y;
        return true;
    }
}dsu;

int A, B, n, m;
ll min_cost;
int a[NMAX + 1];
int b[NMAX + 1];
vector<Edge> edges;

int GetNode(int i, int j) {
    assert(i > 0 && j > 0);
    return (j - 1) * (n + 1) + i;
}

int main() {
    cin >> A >> B >> n >> m;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int i = 1; i <= m; i++) {
        cin >> b[i];
    }
    sort(a + 1, a + n + 1);
    sort(b + 1, b + m + 1);

    a[0] = b[0] = 0;
    a[n + 1] = A;
    b[m + 1] = B;
    for(int j = 1; j <= m + 1; j++) {
        int dist = b[j] - b[j - 1];
        for(int i = 1; i <= n; i++) {
            int node1 = GetNode(i, j);
            int node2 = GetNode(i + 1, j);
            // cout << node1 << ' ' << node2 << ' ' << dist << '\n';
            edges.push_back({node1, node2, dist});
        }
    }

    for(int i = 1; i <= n + 1; i++) {
        int dist = a[i] - a[i - 1];
        for(int j = 1; j <= m; j++) {
            int node1 = GetNode(i, j);
            int node2 = GetNode(i, j + 1);
            edges.push_back({node1, node2, dist});
        }
    }

    sort(edges.begin(), edges.end());
    dsu.Initialize((n + 1) * (m + 1));
    for(auto [x, y, cost] : edges) {
        // cout << x << ' ' << y << ' ' << cost << '\n';
        if(dsu.Unite(x, y)) {
            min_cost += cost;
        }
    }
    cout << min_cost << '\n';    
    // cout << '\n';
    // for(int i = 1; i <= (n + 1) * (m + 1); i++) {
    //     cout << dsu.GetRoot(i) << ' ';
    // }

    return 0;
}