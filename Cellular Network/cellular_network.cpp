#include <iostream>
#include <algorithm>
#include <vector>
#define ll long long

using namespace std;

const int NMAX = 1e5;

struct Event {
	int type;
	ll x;
};

int n, m;
int a[NMAX + 1];
int b[NMAX + 1];

bool cmpEvents(const Event &a, const Event &b) {
	if(a.x < b.x) {
		return true;
	}
	if(a.x == b.x && a.type < b.type) {
		return true;
	}
	return false;
}

bool Check(int distance) {
	vector<Event> events;
	for(int i = 1; i <= m; i++) {
		events.push_back({1, (ll) b[i] - distance});
		events.push_back({2, (ll) b[i] + distance + 1});
	}
	for(int i = 1; i <= n; i++) {
		events.push_back({3, a[i]});
	}

	sort(events.begin(), events.end(), cmpEvents);
	int cnt = 0;
	for(auto event : events) {
		if(event.type == 1) {
			cnt++;
		}
		else if(event.type == 2) {
			cnt--;
		}
		else if(cnt == 0) {
			return false;
		}
	}
	return true;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> n >> m;
	for(int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	for(int i = 1; i <= m; i++) {
		cin >> b[i];
	}

	int left = 0, right = 2e9, answer = -1;
	while(left <= right) {
		int mid = (left + right) / 2;
		if(Check(mid)) {
			answer = mid;
			right = mid - 1;
		}
		else {
			left = mid + 1;
		}
	}
	cout << answer << '\n';

	return 0;
}
