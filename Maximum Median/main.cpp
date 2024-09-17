#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#define ll long long

using namespace std;

const int NMAX = 2e5;

int n, k;
int a[NMAX + 1];

bool Check(ll value) {
    ll cnt = 0;
    for(int i = (n + 1) / 2; i <= n; i++) {
        cnt += max(0LL, value - a[i]);
    }
    return cnt <= k;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> n >> k;
	for(int i = 1; i <= n; i++) {
        cin >> a[i];
	}
	sort(a + 1, a + n + 1);

	ll left = 1, right = 2e9, answer = -1;
	while(left <= right) {
        ll mid = (left + right) / 2;
        if(Check(mid)) {
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
