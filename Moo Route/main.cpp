#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define ll long long
#define ld long double

using namespace std;
using namespace __gnu_pbds;

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

const int NMAX = 1e5;
const int MOD = 1e9 + 7;
const int VMAX = 1e6 / 2;

int n, max_a;
int a[NMAX + 1];
int dp[NMAX + 1];
int fact[VMAX + 1];
int invmod[VMAX + 1];

int Power(int a, int b) {
    int rez = 1;
    while(b) {
        if(b % 2 == 1) {
            rez = (ll)rez * a % MOD;
        }
        a = (ll)a * a % MOD;
        b /= 2;
    }
    return rez;
}

int Combinari(int n, int k) {
    return (ll)fact[n] * invmod[k] % MOD * invmod[n - k] % MOD;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i] /= 2;
        max_a = max(max_a, a[i]);
    }

    fact[0] = 1;
    for(int i = 1; i <= max_a; i++) {
        fact[i] = (ll) fact[i - 1] * i % MOD;
    } 
    invmod[max_a] = Power(fact[max_a], MOD - 2);
    for(int i = max_a - 1; i >= 0; i--) {
        invmod[i] = (ll) invmod[i + 1] * (i + 1) % MOD;
    }

    dp[n] = 1;
    for(int i = n - 1; i >= 1; i--) {
        if(a[i] <= a[i + 1]) {
            dp[i] = (ll) dp[i + 1] * Combinari(a[i + 1] - 1, a[i] - 1) % MOD;
        } 
        else {
            dp[i] = (ll) dp[i + 1] * Combinari(a[i], a[i + 1]) % MOD;
        }
    }
    cout << dp[1];

    return 0;
}