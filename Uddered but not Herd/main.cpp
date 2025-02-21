#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define ll long long
#define ld long double

using namespace std;
using namespace __gnu_pbds;

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

const int INF = 1e9;
const int CMAX = 20;

string s;
int ID;
map<char, int> mp;
int adj[CMAX][CMAX];
int dp[1 << CMAX];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> s;
    for(char x : s) {
        mp[x] = 1;
    }
    for(auto &x : mp) {
        x.second = ID++;
    }

    for(int i = 0; i < (int) s.size() - 1; i++) {
        adj[mp[s[i]]][mp[s[i + 1]]]++;
    }

    dp[0] = 1;
    for(int mask = 1; mask < (1 << ID); mask++) {
        dp[mask] = INF;
        for(int i = 0; i < ID; i++) {
            if(mask >> i & 1) {
                int add = 0;
                for(int j = 0; j < ID; j++) {
                    if(mask >> j & 1) {
                        add += adj[i][j];
                    }
                }
                dp[mask] = min(dp[mask], dp[mask ^ (1 << i)] + add);
            }
        }
    }
    cout << dp[(1 << ID) - 1];

    return 0;
}