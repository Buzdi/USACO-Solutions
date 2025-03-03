#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define ll long long
#define ld long double

using namespace std;
using namespace __gnu_pbds;

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

ifstream fin("grass.in");
ofstream fout("grass.out");

const int NMAX = 1e5;

int n, m, ind, components, answer;
vector<int> g[NMAX + 1], gt[NMAX + 1], gc[NMAX + 1], gct[NMAX + 1];
int order[NMAX + 1];
bool visited[NMAX + 1];
int component[NMAX + 1];
int size_c[NMAX + 1];
int dp[NMAX + 1][2];

void DFS1(int node) {
    visited[node] = 1;
    for(int next_node : g[node]) {
        if(!visited[next_node]) {
            DFS1(next_node);
        }
    }
    order[++ind] = node;
}

void DFS2(int node) {
    component[node] = components;
    size_c[components]++;
    for(int next_node : gt[node]) {
        if(!component[next_node]) {
            DFS2(next_node);
        }
    }
}

void SolveGC() {
    for(int i = 1; i <= components; i++) {
        dp[i][0] = -1;
    }
    dp[component[1]][0] = size_c[component[1]];

    for(int i = 1; i <= components; i++) {
        if(dp[i][0] == -1) {
            continue;
        }
        for(int j : gc[i]) {
            dp[j][0] = max(dp[j][0], dp[i][0] + size_c[j]);
        }
    }
}

void SolveGCT() {
    for(int i = 1; i <= components; i++) {
        dp[i][1] = -1;
    }
    dp[component[1]][1] = size_c[component[1]];

    for(int i = components; i >= 1; i--) {
        if(dp[i][1] == -1) {
            continue;
        }
        for(int j : gct[i]) {
            dp[j][1] = max(dp[j][1], dp[i][1] + size_c[j]);
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    fin.tie(0);
    fout.tie(0);

    fin >> n >> m;
    for(int i = 1; i <= m; i++) {
        int a, b;
        fin >> a >> b;
        g[a].push_back(b);
        gt[b].push_back(a);
    }

    for(int i = 1; i <= n; i++) {
        if(!visited[i]) {
            DFS1(i);
        }
    }

    for(int i = n; i >= 1; i--) {
        if(!component[order[i]]) {
            components++;
            DFS2(order[i]);
        }
    }

    for(int i = 1; i <= n; i++) {
        for(int j : g[i]) {
            if(component[i] != component[j]) {
                gc[component[i]].push_back(component[j]);
                gct[component[j]].push_back(component[i]);
            }
        }
    }

    SolveGC();
    SolveGCT();

    answer = size_c[component[1]];
    for(int i = 1; i <= components; i++) {
        for(int j : gc[i]) {
            if(dp[j][0] != -1 && dp[i][1] != -1) {
                answer = max(answer, dp[j][0] + dp[i][1] - size_c[component[1]]);
            }
        }
    }
    fout << answer << '\n';

    return 0;
}