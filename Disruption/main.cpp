#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define ll long long
#define cin fin
#define cout fout

using namespace std;
using namespace __gnu_pbds;

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

ifstream fin("disrupt.in");
ofstream fout("disrupt.out");

const int NMAX = 5e4;
const int INF = 2e9;
const int BSIZE = 250;

struct Query {
    int left, right, pos;
    bool operator < (const Query& other) const {
        if(left / BSIZE != other.left / BSIZE) {
            return left / BSIZE < other.left / BSIZE;
        }
        return (left / BSIZE & 1 ? right > other.right : right < other.right);
    }
}queries[NMAX + 1];

int n, m, t, l, r;
int in[NMAX + 1], out[NMAX + 1];
int node_end[NMAX + 1];
int dfstrav[NMAX + 1];
vector<pair<int, int>> g[NMAX + 1], g2[NMAX + 1];
multiset<int> s;
int answer[NMAX + 1];

void DFS(int node, pair<int, int> edge_dad = {0, 0}) {
    in[node] = ++t;
    dfstrav[t] = node;
    if(edge_dad.first != 0) {
        node_end[edge_dad.second] = node;
    }
    for(auto [next_node, edge_id] : g[node]) {
        if(next_node != edge_dad.first) {
            DFS(next_node, {node, edge_id});
        }
    }
    out[node] = t;
}

void add(int pos) {
    int node = dfstrav[pos];
    for(auto [next_node, c] : g2[node]) {
        if(in[next_node] >= l && in[next_node] <= r) {
            s.erase(s.find(c));
        }
        else {
            s.insert(c);
        }
    }
}

void remove(int pos) {
    int node = dfstrav[pos];
    for(auto [next_node, c] : g2[node]) {
        if(in[next_node] >= l && in[next_node] <= r) {
            s.insert(c);
        }
        else {
            s.erase(s.find(c));
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;
    for(int i = 1; i <= n - 1; i++) {
        int a, b;
        cin >> a >> b;
        g[a].push_back({b, i});
        g[b].push_back({a, i});
    }
    for(int i = 1; i <= m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        g2[a].push_back({b, c});
        g2[b].push_back({a, c});
    }

    DFS(1);
    for(int i = 1; i <= n - 1; i++) {
        int node = node_end[i];
        queries[i] = {in[node], out[node], i};
    }
    sort(queries + 1, queries + (n - 1) + 1);

    l = 1, r = 0;
    for(int i = 1; i <= n - 1; i++) {
        auto [leftq, rightq, pos] = queries[i];
        while(r < rightq) {
            r++;
            add(r);
        }
        while(l > leftq) {
            l--;
            add(l);
        }
        while(r > rightq) {
            remove(r);
            r--;
        }
        while(l < leftq) {
            remove(l);
            l++;
        }
        answer[pos] = (s.empty() ? -1 : *s.begin());
    }

    for(int i = 1; i <= n - 1; i++) {
        cout << answer[i] << '\n';
    }
    return 0;
}
