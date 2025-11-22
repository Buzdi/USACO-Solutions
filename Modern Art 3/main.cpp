#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int NMAX = 300;
const int INF = 1e9;

int n;
int a[NMAX + 1];
int dp[NMAX + 1][NMAX + 1];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int i = 1; i <= n; i++) {
        dp[i][i] = 1;
    }
    for(int i = n; i >= 1; i--) {
        for(int j = i + 1; j <= n; j++) {
            dp[i][j] = INF;
            for(int k = i; k < j; k++) {
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j] - (a[i] == a[j]));
            }
        }
    }
    cout << dp[1][n] << '\n';
    return 0;
}
