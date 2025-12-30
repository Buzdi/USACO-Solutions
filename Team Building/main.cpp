#include <bits/stdc++.h>
#define ll long long
using namespace std;

ifstream fin("team.in");
ofstream fout("team.out");

const int NMAX = 1000;
const int KMAX = 10;
const int MOD = 1e9 + 9;

int n, m, k;
int a[NMAX + 1], b[NMAX + 1];
int dp[KMAX + 1][NMAX + 1][NMAX + 1];

signed main()
{
    fin >> n >> m >> k;
    for(int i = 1; i <= n; i++) {
        fin >> a[i];
    }
    for(int i = 1; i <= m; i++) {
        fin >> b[i];
    }

    sort(a + 1, a + n + 1);
    sort(b + 1, b + m + 1);
    for(int i = 0; i <= n; i++) {
        for(int j = 0; j <= m; j++) {
            dp[0][i][j] = 1;
        }
    }
    for(int p = 1; p <= k; p++) {
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= m; j++) {
                if(a[i] > b[j]) {
                    dp[p][i][j] = dp[p - 1][i - 1][j - 1];
                }
                dp[p][i][j] = ((ll) dp[p][i][j] + dp[p][i - 1][j] + dp[p][i][j - 1] - dp[p][i - 1][j - 1] + MOD) % MOD;
            }
        }
    }
    fout << dp[k][n][m] << '\n';
    return 0;
}
