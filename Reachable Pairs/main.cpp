#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int NMAX = 2e5;

int n, m;
ll pairs;
bool a[NMAX + 1];
vector<int> g[NMAX + 1];
ll answer[NMAX + 1];

struct DSU {
    int sz[NMAX + 1];
    int parent[NMAX + 1];
    int active[NMAX + 1];

    void init(int n) {
        for(int i = 1; i <= n; i++) {
            sz[i] = 1;
            parent[i] = i;
            active[i] = 0;
        }
    }

    void add_active(int x) {
        x = get_root(x);
        pairs -= (ll) (active[x] - 1) * active[x] / 2;
        active[x]++;
        pairs += (ll) (active[x] - 1) * active[x] / 2;
    }

    int get_root(int node) {
        return parent[node] = (node == parent[node] ? node : get_root(parent[node]));
    }

    void join(int x, int y) {
        x = get_root(x);
        y = get_root(y);
        if(x == y) {
            return;
        }
        if(sz[x] > sz[y]) {
            swap(x, y);
        }

        pairs -= (ll) (active[x] - 1) * active[x] / 2;
        pairs -= (ll) (active[y] - 1) * active[y] / 2;
        sz[y] += sz[x];
        active[y] += active[x];
        parent[x] = y;
        pairs += (ll) (active[y] - 1) * active[y] / 2;
    }
}dsu;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;
    for(int i = 1; i <= n; i++) {
        char x;
        cin >> x;
        a[i] = x - '0';
    }
    for(int i = 1; i <= m; i++) {
        int x, y;
        cin >> x >> y;
        g[x].push_back(y);
        g[y].push_back(x);
    }

    dsu.init(n);
    for(int i = 1; i <= n; i++) {
            if(a[i]) {
            for(int j : g[i]) {
                if(a[j]) {
                    dsu.join(i, j);
                }
            }
        }
    }

    for(int i = n; i >= 1; i--) {
        dsu.add_active(i);
        for(int j : g[i]) {
            if(j > i || a[j]) {
                dsu.join(i, j);
            }
        }
        answer[i] = pairs;
    }

    for(int i = 1; i <= n; i++) {
        cout << answer[i] << '\n';
    }
    return 0;
}
