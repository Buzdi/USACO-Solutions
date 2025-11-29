#include <bits/stdc++.h>
#define cin fin
#define cout fout
#define int long long

using namespace std;

ifstream fin("dirtraverse.in");
ofstream fout("dirtraverse.out");

const int NMAX = 1e5;
const int INF = 1e18;

int n, answer;
vector<int> v[NMAX + 1], g[NMAX + 1];
bool marked[NMAX + 1];
int sz[NMAX + 1];
int sum_sz[NMAX + 1];
int sum_cnt[NMAX + 1][2], cnt[NMAX + 1];
int dp[NMAX + 1][2];

void DFS1(int node, int dad = 0) {
    dp[node][0] = sum_sz[node];
    sum_cnt[node][0] = cnt[node];
    for(int next_node : g[node]) {
        if(next_node != dad) {
            DFS1(next_node, node);
            sum_cnt[node][0] += sum_cnt[next_node][0];
            dp[node][0] += dp[next_node][0] + (sz[next_node] + 1) * sum_cnt[next_node][0];
        }
    }
}

void DFS2(int node, int dad = 0) {
//    cout << node << ' ' << dp[node][0] << ' ' << dp[node][1] << ' ' << sum_cnt[node][1] << '\n';
    answer = min(answer, dp[node][0] + dp[node][1] + 3 * sum_cnt[node][1]);
    int total_sum_dp = sum_sz[node];
    int total_sum_cnt = cnt[node];
    for(int next_node : g[node]) {
        if(next_node != dad) {
            total_sum_dp += dp[next_node][0] + (sz[next_node] + 1) * sum_cnt[next_node][0];
            total_sum_cnt += sum_cnt[next_node][0];
        }
    }
    for(int next_node : g[node]) {
        if(next_node != dad) {
            sum_cnt[next_node][1] = total_sum_cnt - sum_cnt[next_node][0] + sum_cnt[node][1];
            dp[next_node][1] = total_sum_dp - (dp[next_node][0] + (sz[next_node] + 1) * sum_cnt[next_node][0]) + dp[node][1] + 3 * sum_cnt[node][1];
        }
    }
    for(int next_node : g[node]) {
        if(next_node != dad) {
            DFS2(next_node, node);
        }
    }
}

signed main() {
    cin >> n;
    for(int i = 1; i <= n; i++) {
        string s;
        int k;
        cin >> s >> k;

        if(k == 0) {
            marked[i] = 1;
        }
        sz[i] = s.size();
        for(int j = 1; j <= k; j++) {
            int x;
            cin >> x;
            v[i].push_back(x);
        }
    }

    for(int i = 1; i <= n; i++) {
        for(int j : v[i]) {
            if(!marked[j]) {
                g[i].push_back(j);
                g[j].push_back(i);
            }
            else {
                sum_sz[i] += sz[j];
                cnt[i]++;
            }
        }
    }

    DFS1(1);
//    for(int i = 1; i <= n; i++) {
//        cout << dp[i][0] << ' ';
//    }
//    cout << '\n';
    answer = INF;
    DFS2(1);
    cout << answer << '\n';
    return 0;
}
