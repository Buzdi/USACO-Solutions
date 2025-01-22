#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
 
#define ll long long
#define ld long double

using namespace std;
using namespace __gnu_pbds;

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

const int NMAX = 1e5;

struct Edge {
    int a, b, c;
    bool operator < (const Edge &other) const {
        return c < other.c;
    }
}edges[5 * NMAX + 1];

struct DSU {
    int parent[4 * NMAX + 1];
    int sz[4 * NMAX + 1];

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

int n, ind, answer, apm_size;
int f[2 * NMAX + 1];

void Transform(int &a) {
    if(!f[a]) {
        f[a] = 1;
        return;
    }
    a += 2 * n;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    for(int i = 1; i <= n; i++) {
        int cost, a, b, c, d;
        cin >> cost >> a >> b >> c >> d;
        
        Transform(a);
        Transform(b);
        Transform(c);
        Transform(d);

        edges[++ind] = {a, b, 0};
        edges[++ind] = {c, d, 0};
        edges[++ind] = {a, c, cost};
    }

    for(int i = 1; i <= 2 * n; i++) {
        edges[++ind] = {i, 2 * n + i, 0};
    }
    sort(edges + 1, edges + ind + 1);

    dsu.Initialize(4 * n);
    for(int i = 1; i <= ind; i++) {
        auto [a, b, c] = edges[i];
        if(dsu.Unite(a, b)) {
            apm_size++;
            answer += c;
        }
    }
    cout << answer << '\n';

    return 0;
}