#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define ll long long
#define ld long double
// #define int long long

using namespace std;
using namespace __gnu_pbds;

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

ifstream fin("snowcow.in");
ofstream fout("snowcow.out");

const int NMAX = 1e5;

struct AIB {
    int n;
    ll aib[NMAX + 1];

    void Initialize(int n) {
        this->n = n;
        for(int i = 1; i <= n; i++) {
            aib[i] = 0;
        }
    }

    void Update(int pos, int value) {
        for(int i = pos; i <= n; i += i & (-i)) {
            aib[i] += value;
        }
    }

    ll PointQuery(int pos) {
        ll answer = 0;
        for(int i = pos; i >= 1; i -= i & (-i)) {
            answer += aib[i];
        }
        return answer;
    }

    ll SumQuery(int left, int right) {
        if(left > right) {
            return 0;
        }
        return PointQuery(right) - PointQuery(left - 1);
    }
}aib_above, aib_below;

int n, q, dfs_time;
vector<int> g[NMAX + 1];
int dfs[NMAX + 1];
int sub_tree_size[NMAX + 1];
set<pair<int, int>> s[NMAX + 1];

void DFS(int node, int dad = 0) {
    dfs[node] = ++dfs_time;
    sub_tree_size[node] = 1;
    for(int next_node : g[node]) {
        if(next_node != dad) {
            DFS(next_node, node);
            sub_tree_size[node] += sub_tree_size[next_node];
        }
    }
}

void UpdateAIB(int x, int value) {
    aib_above.Update(dfs[x], value);
    aib_above.Update(dfs[x] + sub_tree_size[x], -value);
    aib_below.Update(dfs[x], sub_tree_size[x] * value);
}

void Update(int x, int c) {
    auto it = s[c].lower_bound(make_pair(dfs[x], 0));
    if(it != s[c].begin() && dfs[x] <= prev(it)->first + sub_tree_size[prev(it)->second] - 1) {
        return;
    }
    while(it != s[c].end() && it->first <= dfs[x] + sub_tree_size[x] - 1) {
        UpdateAIB(it->second, -1);
        it = s[c].erase(it);
    }
    UpdateAIB(x, 1);
    s[c].insert(make_pair(dfs[x], x));
}

ll Query(int x) {
    return aib_above.PointQuery(dfs[x]) * sub_tree_size[x] + aib_below.SumQuery(dfs[x] + 1, dfs[x] + sub_tree_size[x] - 1);
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    fin >> n >> q;
    for(int i = 1; i <= n - 1; i++) {
        int a, b;
        fin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    DFS(1);
    aib_above.Initialize(n);
    aib_below.Initialize(n);
    while(q--) {
        int type;
        fin >> type;
        if(type == 1) {
            int x, c;
            fin >> x >> c;
            Update(x, c);
        }
        else {
            int x;
            fin >> x;
            fout << Query(x) << '\n';
        }
    }

    return 0;
}