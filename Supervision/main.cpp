#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int NMAX = 1e6 + 5;
const int MOD = 1e9 + 7;

int power(int a, int b) {
    int rez = 1;
    while(b) {
        if(b % 2 == 1) {
            rez = (ll) rez * a % MOD;
        }
        a = (ll) a * a % MOD;
        b /= 2;
    }
    return rez;
}

int n, d;
int p[NMAX + 1], type[NMAX + 1];
int dp[NMAX + 1][2];
int p2[NMAX + 1];
int sp0[NMAX + 1];
int invmodp2[NMAX + 1];
int sp_dp[NMAX + 1];

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> d;
    for(int i = 1; i <= n; i++) {
        cin >> p[i] >> type[i];
    }

    p2[0] = invmodp2[0] = 1;
    for(int i = 1; i <= n; i++) {
        p2[i] = (ll) p2[i - 1] * 2 % MOD;
        invmodp2[i] = power(p2[i], MOD - 2);
        sp0[i] = sp0[i - 1] + (type[i] == 0);
    }

    dp[n + 1][0] = 1;

    for(int i = n; i >= 1; i--) {
        dp[i][0] = (dp[i + 1][0] + dp[i + 1][1]) % MOD;
        if(type[i]) {
//            int j;
//            int dp_jump = 0;
//            for(j = i + 1; j <= n && p[j] - p[i] <= d; j++) {
//                if(type[j]) {
////                    dp[i][1] = (dp[i][1] + (ll) dp[j][1] * p2[cnt0] % MOD) % MOD;
//                    dp_jump = (dp_jump + (ll) dp[j][1] * p2[sp0[j]] % MOD) % MOD;
//                }
//            }
//            dp_jump = (ll) dp_jump * invmodp2[sp0[i - 1]] % MOD;
//            int cnt0 = sp0[j - 1] - sp0[i - 1];
//            dp[i][1] = (dp_jump + (ll) (dp[j][0] + dp[j][1]) % MOD * p2[cnt0] % MOD) % MOD;

            /// p[j] - p[i] > d
            /// p[j] > d + p[i]
            int j = upper_bound(p + 1, p + n + 1, d + p[i]) - p;
            assert(j >= i);

            int dp_jump = sp_dp[i + 1] - sp_dp[j];
            dp_jump = (ll) dp_jump * invmodp2[sp0[i - 1]] % MOD;
            int cnt0 = sp0[j - 1] - sp0[i - 1];
            dp[i][1] = (dp_jump + (ll) (dp[j][0] + dp[j][1]) % MOD * p2[cnt0] % MOD) % MOD;

            sp_dp[i] = (sp_dp[i + 1] + (ll) dp[i][1] * p2[sp0[i]] % MOD) % MOD;
        }
        else {
            dp[i][1] = 0;
            sp_dp[i] = sp_dp[i + 1];
        }
    }

    int ans = (dp[1][0] + dp[1][1]) % MOD;
    ans--;
    if(ans < 0) {
        ans += MOD;
    }
    cout << ans;
    return 0;
}
