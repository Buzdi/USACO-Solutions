#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#define ll long long

using namespace std;

const int INF = 2e9;

void test_case() {
    int n;
    cin >> n;

    vector<pair<int, int>> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i].first >> a[i].second;
    }
    sort(a.begin(), a.end());

    vector<int> max_sufix(n + 1);
    max_sufix[n] = a[n].second;
    for(int i = n - 1; i >= 1; i--) {
        max_sufix[i] = max(max_sufix[i + 1], a[i].second);
    }

    set<int> s;
    int answer = INF;
    for(int i = 1; i <= n; i++) {
        int curent_max = (i == n ? -1 : max_sufix[i + 1]);
        if(curent_max >= a[i].first) {
            answer = min(answer, curent_max - a[i].first);
        }
        else {
            if(i < n) {
                answer = min(answer, a[i].first - curent_max);
            }
            auto it = s.lower_bound(a[i].first);
            if(it != s.end()) {
                answer = min(answer, *it - a[i].first);
            }
            if(it != s.begin()) {
                answer = min(answer, a[i].first - *prev(it));
            }
        }
        s.insert(a[i].second);
    }
    cout << answer << '\n';
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int T;
	cin >> T;
	while(T--) {
        test_case();
	}

	return 0;
}
