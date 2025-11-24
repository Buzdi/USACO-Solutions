#include <bits/stdc++.h>
#define cin fin
#define cout fout

using namespace std;

ifstream fin("pieaters.in");
ofstream fout("pieaters.out");

const int NMAX = 300;

int n, m;
int max_w[NMAX + 1][NMAX + 2][NMAX + 2];
int dp[NMAX + 1][NMAX + 1];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;
    for(int i = 1; i <= m; i++) {
        int w, l, r;
        cin >> w >> l >> r;
        for(int j = l; j <= r; j++) {
            max_w[j][l][r] = max(max_w[j][l][r], w);
        }
    }

    for(int i = 1; i <= n; i++) {
        for(int l = i; l >= 1; l--) {
            for(int r = i; r <= n; r++) {
                max_w[i][l][r] = max({max_w[i][l][r], max_w[i][l + 1][r], max_w[i][l][r - 1]});
            }
        }
    }

    for(int i = n; i >= 1; i--) {
        for(int j = i; j <= n; j++) {
            for(int k = i; k < j; k++) {
                dp[i][j] = max(dp[i][j], dp[i][k] + dp[k + 1][j]);
            }
            for(int k = i; k <= j; k++) {
                if(max_w[k][i][j]) {
                    dp[i][j] = max(dp[i][j], dp[i][k - 1] + dp[k + 1][j] + max_w[k][i][j]);
                }
            }
        }
    }
    cout << dp[1][n];
    return 0;
}
