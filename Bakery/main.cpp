#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <queue>
#define ll long long

using namespace std;

const int NMAX = 100;

struct Order {
    int a, b;
    ll c;
    void Read() {
        cin >> a >> b >> c;
    }
}orders[NMAX + 1];

int n, t_a, t_b;

bool Check(int w) {
    ll lx, rx;
    lx = max(1, t_a - w);
    rx = min(t_a + t_b - w - 1, t_a);
    for(int i = 1; i <= n; i++) {
        auto [a, b, c] = orders[i];
        ll d = t_a + t_b - w;
        if(a == b) {
            if(a * d > c) {
                return false;
            }
        }
        else {
            if(a - b > 0) {
                if(c - b * d < 0) {
                    rx = min(rx, (c - b * d) / (a - b) - ((c - b * d) % (a - b) != 0));
                }
                else {
                    rx = min(rx, (c - b * d) / (a - b));
                }
            }
            else {
                if(c - b * d < 0) {
                    lx = max(lx, (c - b * d) / (a - b) + ((c - b * d) % (a - b) != 0));
                }
                else {
                    lx = max(lx, (c - b * d) / (a - b));
                }
            }
        }
    }
    return lx <= rx;
}

void test_case() {
    cin >> n >> t_a >> t_b;
    for(int i = 1; i <= n; i++) {
        orders[i].Read();
    }

    int left = 1, right = t_a + t_b - 2, answer = -1;
    while(left <= right) {
        int mid = left + (right - left) / 2;
        if(Check(mid)) {
            answer = mid;
            right = mid - 1;
        }
        else {
            left = mid + 1;
        }
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
