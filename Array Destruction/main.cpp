#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cassert>
#include <set>
#define ll long long

using namespace std;

void test_case() {
    int n;
    cin >> n;
    n *= 2;

    vector<int> a(n + 1);
    int maxi = 0;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        maxi = max(maxi, a[i]);
    }

    int cnt = 0;
    for(int i = 1; i <= n; i++) {
        if(a[i] == maxi) {
            cnt++;
        }
    }

    for(int i = 1; i <= n; i++) {
        if(cnt >= 2 || a[i] != maxi) {
            multiset<int> s;
            for(int j = 1; j <= n; j++) {
                if(i != j) {
                    s.insert(a[j]);
                }
            }
            s.erase(prev(s.end()));

            vector<pair<int, int>> op;
            op.push_back({a[i], maxi});

            int x = maxi;
            bool ok = true;
            while(!s.empty() && ok) {
                int maxi = *prev(s.end());
                s.erase(prev(s.end()));

                int need = x - maxi;
                auto it = s.find(need);
                if(it != s.end()) {
                    op.push_back({need, maxi});
                    s.erase(it);
                    x = maxi;
                }
                else {
                    ok = false;
                }
            }

            if(ok) {
                cout << "YES" << '\n';
                cout << a[i] + maxi << '\n';
                for(auto x : op) {
                    cout << x.first << ' ' << x.second << '\n';
                }
                return;
            }
        }
    }
    cout << "NO" << '\n';
}

signed main() {
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
