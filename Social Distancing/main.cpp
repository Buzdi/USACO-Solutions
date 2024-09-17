#include <fstream>
#include <algorithm>
#include <vector>
#include <map>
#include <queue>
#define ll long long

using namespace std;

ifstream cin("socdist.in");
ofstream cout("socdist.out");

const int NMAX = 1e5;

int n, m;
pair<ll, ll> a[NMAX + 1];

bool Check(ll D) {
    int curent_n = n;
    ll pos = 0;
    for(int i = 1; i <= m && curent_n; i++) {
        pos = max(pos, a[i].first);
        while(curent_n && pos >= a[i].first && pos <= a[i].second) {
            curent_n--;
            pos += D;
        }
    }
    return curent_n == 0;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> n >> m;
	for(int i = 1; i <= m; i++) {
        cin >> a[i].first >> a[i].second;
	}
	sort(a + 1, a + m + 1);

    ll left = 1, right = 1e18, answer = -1;
    while(left <= right) {
        ll mid = left + (right - left) / 2;
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
