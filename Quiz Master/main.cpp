#include <iostream>
#include <algorithm>
#include <vector>
#define ll long long

using namespace std;

const int INF = 1e9;
const int NMAX = 1e5;
const int LGMAX = 18;

int n, m, inside;
int a[NMAX + 1];
int f[NMAX + 1];

void AddDivisor(int d) {
    if(d > m) {
        return;
    }

    if(f[d] == 0) {
        inside++;
    }
    f[d]++;
}

void DeleteDivisor(int d) {
    if(d > m) {
        return;
    }

    f[d]--;
    if(f[d] == 0) {
        inside--;
    }
}

void Add(int value) {
    for(int d = 1; d * d <= value; d++) {
        if(value % d == 0) {
            AddDivisor(d);
            if(d * d != value) {
                AddDivisor(value / d);
            }
        }
    }
}

void Delete(int value) {
    for(int d = 1; d * d <= value; d++) {
        if(value % d == 0) {
            DeleteDivisor(d);
            if(d * d != value) {
                DeleteDivisor(value / d);
            }
        }
    }
}

void test_case() {
    cin >> n >> m;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    sort(a + 1, a + n + 1);

    int right = 1, answer = INF;
    for(int i = 1; i <= n; i++) {
        while(right <= n && inside < m) {
            Add(a[right]);
            right++;
        }
        if(inside == m) {
            answer = min(answer, a[right - 1] - a[i]);
        }
        Delete(a[i]);
    }
    cout << (answer == INF ? -1 : answer) << '\n';

    /// Erasing stuff for next test
    for(int i = 1; i <= m; i++) {
        f[i] = 0;
    }
    inside = 0;
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
