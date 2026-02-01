#include <bits/stdc++.h>
#define ll long long

using namespace std;

ifstream fin("runaway.in");
ofstream fout("runaway.out");

const int NMAX = 2e5;

int n, ind;
ll l;
vector<pair<int, ll>> g[NMAX + 1];
pair<ll, int> st[NMAX + 1];
int mars[NMAX + 1];

void DFS1(int node, pair<int, ll> dad_edge = {0, 0}) {
    ind++;
    if(node != 1) {
        st[ind] = {st[ind - 1].first + dad_edge.second, node};
    }
    int pos = lower_bound(st + 1, st + ind + 1, make_pair(st[ind].first - l, 0)) - st - 1;
//    for(int i = 1; i <= ind; i++) {
//        cout << st[i].first << ' ';
//    }
//    cout << '\n';
//    cout << pos << ' ' << node << ' ' << st[pos].second << ' ' << st[ind].first - l << '\n';
    mars[node]++;
    mars[st[pos].second]--;

    for(auto [next_node, x] : g[node]) {
        if(next_node != dad_edge.first) {
            DFS1(next_node, {node, x});
        }
    }

    ind--;
}

void DFS2(int node, int dad = 0) {
    for(auto [next_node, x] : g[node]) {
        if(next_node != dad) {
            DFS2(next_node, node);
            mars[node] += mars[next_node];
        }
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    fin >> n >> l;
    for(int i = 2; i <= n; i++) {
        int p;
        ll x;
        fin >> p >> x;
        g[p].push_back({i, x});
        g[i].push_back({p, x});
    }

    st[1] = {0, 1};
    DFS1(1);
    DFS2(1);
    for(int i = 1; i <= n; i++) {
        fout << mars[i] << '\n';
    }
    return 0;
}
