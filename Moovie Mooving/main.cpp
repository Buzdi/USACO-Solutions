#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define ll long long
#define ld long double
// #define int long long

using namespace std;
using namespace __gnu_pbds;

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

ifstream fin("movie.in");
ofstream fout("movie.out");

const int NMAX = 20;
const int INF = 1e9;

int n, l, answer;
int duration[NMAX];
vector<int> start_time[NMAX];
int dp[1 << NMAX];

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    fin >> n >> l;
    for(int i = 0; i < n; i++) {
        fin >> duration[i];

        int k;
        fin >> k;
        for(int j = 0; j < k; j++) {
            int x;
            fin >> x;
            start_time[i].push_back(x);
        }
    }

    for(int i = 0; i < n; i++) {
        if(start_time[i][0] == 0) {
            dp[1 << i] = start_time[i][0] + duration[i];
        }
    }
    for(int mask = 1; mask < (1 << n); mask++) {
        if(__builtin_popcount(mask) == 1) {
            continue;
        }

        for(int i = 0; i < n; i++) {
            if(mask >> i & 1) {
                int pos = upper_bound(start_time[i].begin(), start_time[i].end(), dp[mask ^ (1 << i)]) - start_time[i].begin() - 1;
                if(pos >= 0) {
                    dp[mask] = max(dp[mask], start_time[i][pos] + duration[i]);
                }
            }
        }
    }

    answer = INF;
    for(int mask = 1; mask < (1 << n); mask++) {
        if(dp[mask] >= l) {
            // cout << mask << ' ' << __builtin_popcount(mask) << '\n';
            answer = min(answer, __builtin_popcount(mask));
        }
    }
    fout << (answer == INF ? -1 : answer) << '\n';

    return 0;
}