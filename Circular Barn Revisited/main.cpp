#include <bits/stdc++.h>
#define ll long long
using namespace std;

ifstream fin("cbarn2.in");
ofstream fout("cbarn2.out");

const ll INF = 1e18;
const int NMAX = 200;
const int KMAX = 7;

int n, k;
ll answer;
int a[NMAX + 1];
ll c[NMAX + 1][NMAX + 1];
ll dp[KMAX + 1][NMAX + 1];

ll solve_dp(int start) {
    int ending = start + n - 1;
    /// Obligatoriu pun la start
    for(int i = start; i <= ending; i++) {
        dp[2][i] = c[start][i - 1];
    }

    for(int j = 3; j <= k; j++) {
        for(int i = start + j - 1; i <= ending; i++) {
            dp[j][i] = INF;
            for(int iprev = start; iprev < i; iprev++) {
                dp[j][i] = min(dp[j][i], dp[j - 1][iprev] + c[iprev][i - 1]);
            }
        }
    }

    ll answer = INF;
    for(int i = start; i <= ending; i++) {
        answer = min(answer, dp[k][i] + c[i][ending]);
    }
    return answer;
}

signed main()
{
    fin >> n >> k;
    for(int i = 1; i <= n; i++) {
        fin >> a[i];
        a[i + n] = a[i];
    }

    for(int i = 1; i <= 2 * n; i++) {
        for(int j = i + 1; j <= 2 * n; j++) {
            c[i][j] = c[i][j - 1] + (ll)(j - i) * a[j];
        }
    }

    if(k == 1) {
        ll answer = INF;
        for(int i = 1; i <= n; i++) {
            answer = min(answer, c[i][i + n - 1]);
        }
        fout << answer << '\n';
        return 0;
    }

    answer = INF;
    for(int i = 1; i <= n; i++) {
        answer = min(answer, solve_dp(i));
    }
    fout << answer << '\n';
    return 0;
}
