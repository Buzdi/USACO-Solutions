#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

ifstream cin("mootube.in");
ofstream cout("mootube.out");

const int NMAX = 1e5;

struct Edge {
    int a, b, c;
    bool operator < (const Edge &other) const {
        return c > other.c;
    }
}edges[NMAX + 1];

struct Query {
    int k, start, pos;
    bool operator < (const Query &other) const {
        return k > other.k;
    }
}queries[NMAX + 1];

struct DSU {
    int parent[NMAX + 1];
    int sz[NMAX + 1];

    void Initialize(int n) {
        for(int i = 1; i <= n; i++) {
            parent[i] = i;
            sz[i] = 1;
        }
    }

    int GetRoot(int node) {
        return parent[node] = (node == parent[node] ? node : GetRoot(parent[node]));
    }

    void Unite(int x, int y) {
        int root_x = GetRoot(x);
        int root_y = GetRoot(y);
        if(root_x == root_y) {
            return;
        }

        if(sz[root_x] > sz[root_y]) {
            swap(root_x, root_y);
        }
        parent[root_x] = root_y;
        sz[root_y] += sz[root_x];
    }
}dsu;

int n, q, ind;
int answer[NMAX + 1];

int main()
{
    cin >> n >> q;
    for(int i = 1; i <= n - 1; i++) {
        cin >> edges[i].a >> edges[i].b >> edges[i].c;
    }
    for(int i = 1; i <= q; i++) {
        cin >> queries[i].k >> queries[i].start;
        queries[i].pos = i;
    }

    sort(edges + 1, edges + n - 1 + 1);
    sort(queries + 1, queries + q + 1);

    ind = 1;
    dsu.Initialize(n);
    for(int i = 1; i <= q; i++) {
        while(ind <= n - 1 && edges[ind].c >= queries[i].k) {
            dsu.Unite(edges[ind].a, edges[ind].b);
            ind++;
        }
        answer[queries[i].pos] = dsu.sz[dsu.GetRoot(queries[i].start)];
    }

    for(int i = 1; i <= q; i++) {
        cout << answer[i] - 1 << '\n';
    }

    return 0;
}
