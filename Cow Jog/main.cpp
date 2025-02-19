#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define ll long long
#define ld long double

using namespace std;
using namespace __gnu_pbds;

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

ifstream fin("cowjog.in");
ofstream fout("cowjog.out");

const int NMAX = 1e5;
const ll INF = 1e18 + 5; 

int n, t, answer;
ll a[NMAX + 1];
ll dp[NMAX + 1];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    fin>> n >> t;
    for(int i = 1; i <= n; i++) {
        int p, v;
        fin >> p >> v;
        a[i] = p + (ll) t * v;
    }    

    for(int i = 1; i <= n; i++) {
        dp[i] = INF;
    }
    dp[0] = -INF;

    for(int i = n; i >= 1; i--) {
        int l = upper_bound(dp, dp + n + 1, a[i]) - dp;
        dp[l] = a[i];
    }

    for(int i = 0; i <= n; i++) {
        if(dp[i] < INF) {
            answer = i;
        }
    }
    fout << answer << '\n';

    return 0;
}