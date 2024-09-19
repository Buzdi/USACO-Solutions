#include <fstream>
#include <algorithm>
#include <vector>
#define ll long long

using namespace std;

ifstream cin("loan.in");
ofstream cout("loan.out");

ll n, k, m;

bool Check(ll x) {
    ll cur_n = n;
    ll cur_k = k;
    ll y = cur_n / x;
    while (y > m && cur_k > 0) {
        /// n - k * y < y * x
        /// k > (n - y * x) / y

        ll k_here = (cur_n - y * x) / y + 1;
        cur_n -= k_here * y;
        cur_k -= k_here;
        y = cur_n / x;
    }
    cur_n -= cur_k * m;
    return cur_n <= 0;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> k >> m;
    ll left = 1, right = n, answer = -1;
    while (left <= right) {
        ll mid = left + (right - left) / 2;
        if (Check(mid)) {
            answer = mid;
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    cout << answer << '\n';

    return 0;
}
