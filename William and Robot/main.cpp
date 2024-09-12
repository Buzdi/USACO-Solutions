#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cassert>
#include <set>
#define ll long long

using namespace std;

const int NMAX = 1e5;

int n;
int a[NMAX + 5];
ll answer;
multiset<int> s;

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    s.insert(max(a[1], a[2]));
    for(int i = 3; i + 1 <= n; i += 2) {
        int mini = *s.begin();
        if(mini < min(a[i], a[i + 1])) {
            s.erase(s.begin());
            s.insert(a[i]);
            s.insert(a[i + 1]);
        }
        else {
            s.insert(max(a[i], a[i + 1]));
        }
    }

    for(int x : s) {
        answer += x;
    }
    cout << answer << '\n';

	return 0;
}
