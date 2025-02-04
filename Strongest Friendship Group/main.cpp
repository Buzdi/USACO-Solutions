#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define ll long long
#define ld long double

using namespace std;
using namespace __gnu_pbds;

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

const int NMAX = 1e5;
const int MMAX = 2e5;

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
        return parent[node] = (parent[node] == node ? node : GetRoot(parent[node]));
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
        sz[root_y] += sz[root_x];
        parent[root_x] = root_y;
    }
}dsu;

int n, m, ind_order;
ll answer;
vector<pair<int, int>> g[NMAX + 1];
int degree[NMAX + 1];
int order[NMAX + 1];
vector<int> order_g[NMAX + 1];
set<pair<int, int>> s;
char taken[MMAX + 1];
 
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;
    for(int i = 1; i <= m; i++) {
        int a, b;
        cin >> a >> b;

        degree[a]++;
        degree[b]++;
        g[a].emplace_back(b, i);
        g[b].emplace_back(a, i);
    }

    for(int i = 1; i <= n; i++) {
        s.insert({degree[i], i});
    }

    for(int i = 1; i <= n; i++) {
        auto it = s.begin();
        int node = it->second;
        s.erase(it);

        degree[node] = 0;
        order[++ind_order] = node;

        for(auto [next_node, edge] : g[node]) {
            if(!taken[edge]) {
                taken[edge] = 1;
                s.erase({degree[next_node], next_node});
                degree[next_node]--;
                s.insert({degree[next_node], next_node});
                order_g[node].push_back(next_node);
            }
        }
    }

    dsu.Initialize(n);
    for(int i = n; i >= 1; i--) {
        int node = order[i];
        for(int next_node : order_g[node]) {
            dsu.Unite(node, next_node);
            degree[node]++;
            degree[next_node]++;
        }
        answer = max(answer, (ll) degree[node] * dsu.sz[dsu.GetRoot(node)]);
    }
    cout << answer << '\n';

    return 0;
}