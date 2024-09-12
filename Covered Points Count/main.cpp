#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>
#include <set>
#include <map>
#define ll long long
//#define int long long

using namespace std;

const int NMAX = 2e5;

int n, value;
ll last;
ll answer[NMAX + 1];
map<ll, int> mp;

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> n;
	for(int i = 1; i <= n; i++) {
        ll x, y;
        cin >> x >> y;
        mp[x]++;
        mp[y + 1]--;
	}

	last = 0;
    for(auto x : mp) {
        answer[value] += x.first - last;
        value += x.second;
        last = x.first;
    }
    for(int i = 1; i <= n; i++) {
        cout << answer[i] << ' ';
    }

	return 0;
}
