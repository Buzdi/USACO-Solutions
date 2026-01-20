#include <bits/stdc++.h>

#define ll long long

using namespace std;

const int NMAX = 40;

int n, ind_a, ind_b, xg, yg;
pair<int, int> a[NMAX + 1], b[NMAX + 1];
vector<pair<ll, ll>> sums1[NMAX + 1], sums2[NMAX + 1];
ll answer[NMAX + 1];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> xg >> yg;
    for(int i = 1; i <= n; i++) {
        int x, y;
        cin >> x >> y;
        if(i <= n / 2) {
            a[++ind_a] = {x, y};
        }
        else {
            b[++ind_b] = {x, y};
        }
    }

    for(int mask = 0; mask < (1 << ind_a); mask++) {
        ll sum_x = 0, sum_y = 0;
        int cnt = __builtin_popcount(mask);
        for(int i = 1; i <= ind_a; i++) {
            if(mask >> (i - 1) & 1) {
                sum_x += a[i].first;
                sum_y += a[i].second;
            }
        }
        sums1[cnt].emplace_back(sum_x, sum_y);
    }
    for(int i = 0; i <= ind_a; i++) {
        sort(sums1[i].begin(), sums1[i].end());
    }

    for(int mask = 0; mask < (1 << ind_b); mask++) {
        ll sum_x = 0, sum_y = 0;
        int cnt = __builtin_popcount(mask);
        for(int i = 1; i <= ind_b; i++) {
            if(mask >> (i - 1) & 1) {
                sum_x += b[i].first;
                sum_y += b[i].second;
            }
        }
        sums2[cnt].emplace_back(sum_x, sum_y);
    }

    for(int k = 1; k <= n; k++) {
        for(int k2 = 0; k2 <= k; k2++) {
            for(auto [x, y] : sums2[k2]) {
                auto bounds = equal_range(sums1[k - k2].begin(), sums1[k - k2].end(), make_pair(xg - x, yg - y));
                answer[k] += bounds.second - bounds.first;
            }
        }
    }

    for(int k = 1; k <= n; k++) {
        cout << answer[k] << '\n';
    }
    return 0;
}
