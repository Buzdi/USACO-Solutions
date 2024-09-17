#include <fstream>
#include <algorithm>
#include <vector>
#include <map>
#define ll long long

using namespace std;

ifstream cin("haybales.in");
ofstream cout("haybales.out");

const int NMAX = 1e5;

int n, Q;
int a[NMAX + 1];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> n >> Q;
	for(int i = 1; i <= n; i++) {
        cin >> a[i];
	}
	sort(a + 1, a + n + 1);

    while(Q--) {
        int left, right;
        cin >> left >> right;

        int pos_left = lower_bound(a + 1, a + n + 1, left) - a;
        if(pos_left == n + 1) {
            cout << 0 << '\n';
        }
        else {
            int pos_right = upper_bound(a + 1, a + n + 1, right) - a - 1;
            cout << pos_right - pos_left + 1 << '\n';
        }
    }

	return 0;
}
