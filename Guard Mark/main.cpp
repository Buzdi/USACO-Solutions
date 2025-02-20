#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define ll long long
#define ld long double

using namespace std;
using namespace __gnu_pbds;

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

ifstream fin("guard.in");
ofstream fout("guard.out");

const int NMAX = 20;
const int INF = 2e9;

struct Cow {
    int h, w, s;
}cows[NMAX + 1];

int n, h, answer;
int dp[1 << NMAX];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    fin >> n >> h;
    for(int i = 1; i <= n; i++) {
        fin >> cows[i].h >> cows[i].w >> cows[i].s;
    }

    for(int mask = 1; mask < (1 << n); mask++) {
        dp[mask] = -INF;
    }
    for(int i = 1; i <= n; i++) {
        dp[1 << (i - 1)] = cows[i].s;
    }
    for(int mask = 1; mask < (1 << n); mask++) {
        if(__builtin_popcount(mask) == 1) {
            continue;
        }

        for(int i = 1; i <= n; i++) {
            if(mask >> (i - 1) & 1 && cows[i].w <= dp[mask ^ (1 << (i - 1))]) {
                dp[mask] = max(dp[mask], min(cows[i].s, dp[mask ^ (1 << (i - 1))] - cows[i].w));
            }
        }
    }

    answer = -INF;
    for(int mask = 1; mask < (1 << n); mask++) {
        if(dp[mask] != -INF) {
            ll total_height = 0;
            for(int i = 1; i <= n; i++) {
                if(mask >> (i - 1) & 1) {
                    total_height += cows[i].h;
                }
            }
            if(total_height >= h) {
                answer = max(answer, dp[mask]);
            }
        }
    }

    if(answer == -INF) {
        fout << "Mark is too tall\n";
    }
    else {
        fout << answer << '\n';
    }

    return 0;
}