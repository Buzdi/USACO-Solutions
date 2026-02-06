#include <bits/stdc++.h>
#define ll long long
using namespace std;

ifstream fin("cbarn.in");
ofstream fout("cbarn.out");

const ll INF = 1e18;
const int NMAX = 2000;
const int KMAX = 7;

int n, k;
ll answer;
int a[NMAX + 1];
ll c[NMAX + 1][NMAX + 1];
ll dp[KMAX + 1][NMAX + 1];

void solve(int j, int left, int right, int left_opt, int right_opt) {
    if(left > right) {
        return;
    }

    int mid = (left + right) / 2;
    int cur_opt = 0;
    dp[j][mid] = INF;
    for(int i = left_opt; i <= min(mid - 1, right_opt); i++) {
        ll cost_here = dp[j - 1][i] + c[i][mid - 1];
        if(cost_here < dp[j][mid]) {
            dp[j][mid] = cost_here;
            cur_opt = i;
        }
    }

    solve(j, left, mid - 1, left_opt, cur_opt);
    solve(j, mid + 1, right, cur_opt, right_opt);
}

ll solve_dp(int start) {
    int ending = start + n - 1;
    for(int i = start; i <= ending; i++) {
        dp[2][i] = c[start][i - 1];
    }

    for(int j = 3; j <= k; j++) {
        solve(j, start, ending, start, ending);
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
