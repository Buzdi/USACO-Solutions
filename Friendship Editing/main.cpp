#include <bits/stdc++.h>

using namespace std;

const int NMAX = 16;
const int INF = 2e9;

int n, m;
bool g[NMAX + 1][NMAX + 1];
int dp[1 << NMAX];
int cnt[1 << NMAX];

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;
    for(int i = 1; i <= m; i++) {
        int a, b;
        cin >> a >> b;
        g[a][b] = g[b][a] = 1;
    }

    for(int mask = 0; mask < (1 << n); mask++) {
        int sz = 0;
        for(int i = 1; i <= n; i++) {
            if(mask >> (i - 1) & 1) {
                sz++;
                for(int j = 1; j < i; j++) {
                    if((mask >> (j - 1) & 1) && !g[i][j]) {
                        cnt[mask]++;
                    }
                }
            }
        }
        cnt[mask] = sz * (sz - 1) / 2 - 2 * cnt[mask];
    }

    dp[0] = n * (n - 1) / 2 - m;
    for(int mask = 1; mask < (1 << n); mask++) {
        dp[mask] = INF;
        for(int submask = mask; submask; submask = (submask - 1) & mask) {
            int subset = mask ^ submask;
            dp[mask] = min(dp[mask], dp[subset] + cnt[submask]);
        }
    }
    cout << dp[(1 << n) - 1] << '\n';
    return 0;
}
