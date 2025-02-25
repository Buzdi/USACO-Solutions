#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define ll long long
#define ld long double

using namespace std;
using namespace __gnu_pbds;

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

ifstream fin("barnpainting.in");
ofstream fout("barnpainting.out");

const int NMAX = 1e5;
const int MOD = 1e9 + 7;

int n, k;
vector<int> g[NMAX + 1];
int color[NMAX + 1];
int dp[NMAX + 1][4];

void DFS(int node, int dad = 0) {
    vector<int> v;
    for(int next_node : g[node]) {
        if(next_node != dad) {
            DFS(next_node, node);
            v.push_back(next_node);
        }
    }

    if(v.empty()) {
        if(color[node]) {
            dp[node][color[node]] = 1;
        }
        else {
            dp[node][1] = dp[node][2] = dp[node][3] = 1;
        }
        return;
    }

    for(int x = 1; x <= 3; x++) {
        if(!color[node] || color[node] == x) {
            dp[node][x] = 1;
            for(int next_node : v) {
                int sum = 0;
                for(int y = 1; y <= 3; y++) {
                    if(x != y) {
                        sum = (sum + dp[next_node][y]) % MOD;
                    }
                }
                dp[node][x] = (ll)dp[node][x] * sum % MOD;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    fin >> n >> k;
    for(int i = 1; i <= n - 1; i++) {
        int a, b;
        fin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    for(int i = 1; i <= k; i++) {
        int x, y;
        fin >> x >> y;
        color[x] = y;
    }

    DFS(1);
    for(int i = 1; i <= n; i++) {
        // cout << dp[i][1] << ' ' << dp[i][2] << ' ' << dp[i][3] << '\n';
    }
    fout << ((ll)dp[1][1] + dp[1][2] + dp[1][3]) % MOD;

    return 0;
}