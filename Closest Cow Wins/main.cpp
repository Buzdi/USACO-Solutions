#include <iostream>
#include <algorithm>
#include <cassert>
#include <vector>
#define ll long long

using namespace std;

const int NMAX = 2e5;
const int INF = 2e9;

int k, m, n, ind, L, R;
int cows[NMAX + 2];
vector<pair<ll, int>> values;
ll sum_solo, sum_double, answer;
pair<int, int> patches[NMAX + 1];

bool cmp(pair<ll, int> a, pair<ll, int> b) {
    if(a.first > b.first) {
        return true;
    }
    if(a.first == b.first && a.second < b.second) {
        return true;
    }
    return false;
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> k >> m >> n;
    for(int i = 1; i <= k; i++) {
        cin >> patches[i].first >> patches[i].second;
    }
    for(int i = 1; i <= m; i++) {
        cin >> cows[i];
    }
    sort(patches + 1, patches + k + 1);
    sort(cows + 1, cows + m + 1);

    /// Left interval
    R = 1;
    while(patches[R].first < cows[1]) {
        sum_solo += patches[R].second;
        R++;
    }
    values.push_back({sum_solo, 1});

    /// Right interval
    L = k;
    sum_solo = 0;
    while(patches[L].first > cows[m]) {
        sum_solo += patches[L].second;
        L--;
    }
    values.push_back({sum_solo, 1});

    /// Middle intervals
    for(int i = 1; i <= m - 1; i++) {
        if(cows[i] + 1 == cows[i + 1]) {
            continue;
        }

        L = lower_bound(patches + 1, patches + k + 1, make_pair(cows[i], 0)) - patches;
        R = L;
        sum_double = 0;
        while(patches[R].first < cows[i + 1]) {
            sum_double += patches[R].second;
            R++;
        }

        sum_solo = 0;
        R = L;
        int pos = cows[i] + 1;
        ll max_sum = 0;
        while(patches[R].first < cows[i + 1]) {
            while(2 * patches[R].first < cows[i + 1] + pos) {
                sum_solo += patches[R].second;
                R++;
            }
            while(2 * patches[L].first <= cows[i] + pos) {
                sum_solo -= patches[L].second;
                L++;
            }
            max_sum = max(max_sum, sum_solo);
            pos++;
        }

        values.push_back({sum_double - max_sum, 2});
        values.push_back({max_sum, 1});
    }

    sort(values.begin(), values.end(), cmp);
    for(int i = 0; i < min(n, (int) values.size()); i++) {
        answer += values[i].first;
    }
    cout << answer << '\n';

    return 0;
}
