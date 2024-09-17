#include <iostream>
#include <cmath>
#include <set>
#include <map>
#include <vector>
#include <cassert>
#include <algorithm>
#define int long long
#define ll long long

using namespace std;

const int NMAX = 1e5;
const ll INF = 1e18;

int n, m, Q;
int a[NMAX + 1];
int b[NMAX + 1];
ll sums_b[NMAX + 1];
ll sum_a;

ll TernarySearch() {
    int left = 1, right = m - n + 1;
    ll answer = INF;
    while(right - left > 4) {
        int mid1 = (left + right) / 2;
        int mid2 = (left + right) / 2 + 1;

        ll f1 = abs(sum_a + sums_b[mid1]);
        ll f2 = abs(sum_a + sums_b[mid2]);
        if(f1 > f2) {
            left = mid2;
        }
        else {
            right = mid1;
        }
    }

    for(int i = left; i <= right; i++) {
        answer = min(answer, abs(sum_a + sums_b[i]));
    }
    return answer;
}

ll BruteSearch() {
    ll answer = INF;
    for(int i = 1; i <= m - n + 1; i++) {
        answer = min(answer, abs(sum_a + sums_b[i]));
    }
    return answer;
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m >> Q;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int i = 1; i <= m; i++) {
        cin >> b[i];
    }

    for(int i = 1; i <= n; i++) {
        sums_b[1] += (i % 2 == 1 ? -1 : 1) * b[i];
    }
    for(int i = n + 1; i <= m; i++) {
        sums_b[i - n + 1] = -sums_b[i - n] - b[i - n] + (n % 2 == 1 ? -1 : 1) * b[i];
    }
    sort(sums_b + 1, sums_b + (m - n + 1) + 1);

    for(int i = 1; i <= n; i++) {
        sum_a += (i % 2 == 1 ? 1 : -1) * a[i];
    }

    cout << TernarySearch() << '\n';
    while(Q--) {
        int left, right, x;
        cin >> left >> right >> x;

        int cnt_even = right / 2 - (left - 1) / 2;
        sum_a -= (ll) cnt_even * x;
        sum_a += (ll) (right - left + 1 - cnt_even) * x;
        cout << TernarySearch() << '\n';
    }

    return 0;
}
