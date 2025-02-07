#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define ll long long
#define ld long double

using namespace std;
using namespace __gnu_pbds;

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

ifstream fin("hopscotch.in");
ofstream fout("hopscotch.out");

const int NMAX = 750;
const int MOD = 1e9 + 7;

struct AIB {
    int n;
    vector<int> aib;

    void Initialize(int n) {
        this->n = n;
        aib.resize(n + 1, 0);
    }

    void Update(int pos, int value) {
        for(int i = pos; i <= n; i += i & (-i)) {
            aib[i] = (aib[i] + value) % MOD;
        }
    }

    int Query(int pos) {
        int answer = 0;
        for(int i = pos; i >= 1; i -= i & (-i)) {
            answer = (answer + aib[i]) % MOD;
        }
        return answer;
    }
}aib[NMAX * NMAX + 1];

int n, m, k;
int a[NMAX + 1][NMAX + 1];
int col_dp[NMAX + 1];
int sp[NMAX + 1];
int dp[NMAX + 1];
vector<int> positions[NMAX * NMAX + 1];

int GetPos(int colour, int value) {
    int pos = upper_bound(positions[colour].begin(), positions[colour].end(), value) - positions[colour].begin() - 1;
    // cout << colour << ' ' << value << ' ' << pos << '\n';
    // if(!(pos >= 0 && pos <= m)) {
    //     exit(0);
    // }
    return pos;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    fin >> n >> m >> k;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            fin >> a[i][j];
        }
    }
    
    for(int i = 1; i <= k; i++) {
        positions[i].push_back(0);
    }
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            positions[a[i][j]].push_back(j);
        }
    }
    for(int i = 1; i <= k; i++) {
        sort(positions[i].begin(), positions[i].end());
        positions[i].erase(unique(positions[i].begin(), positions[i].end()), positions[i].end());
    }

    // for(int i = 1; i <= k; i++) {
    //     for(int x : positions[i]) {
    //         cout << x << ' ';
    //     }
    //     cout << '\n';
    // }

    for(int i = 1; i <= k; i++) {
        aib[i].Initialize(positions[i].size() - 1);
    }
    aib[a[1][1]].Update(GetPos(a[1][1], 1), 1);
    col_dp[1] = 1;
    for(int j = 1; j <= m; j++) {
        sp[j] = 1;
    }

    for(int i = 2; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            dp[j] = (sp[j - 1] - aib[a[i][j]].Query(GetPos(a[i][j], j - 1)) + MOD) % MOD;
        }
        
        // for(int j = 1; j <= m; j++) {
        //     cout << dp[j] << ' ';
        // }
        // cout << '\n';
        // for(int j = 1; j <= m; j++) {
        //     cout << sp[j] << ' ';
        // }
        // cout << '\n';
        // cout << '\n';

        for(int j = 1; j <= m; j++) {
            col_dp[j] = (col_dp[j] + dp[j]) % MOD;
            sp[j] = (sp[j - 1] + col_dp[j]) % MOD;
            aib[a[i][j]].Update(GetPos(a[i][j], j), dp[j]);
        }
    }
    fout << dp[m];
    return 0;
}