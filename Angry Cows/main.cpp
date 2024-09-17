#include <fstream>
#include <algorithm>
#include <vector>
#include <map>
#include <queue>
#define ll long long

using namespace std;

ifstream cin("angry.in");
ofstream cout("angry.out");

const int NMAX = 5e4;

int n, k;
int a[NMAX + 1];

bool Check(int R) {
    int cnt = 1;
    int left = 1;
    for(int i = 1; i <= n; i++) {
        if(a[i] - a[left] > 2 * R) {
            cnt++;
            left = i;
        }
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

    int left = 1, right = 1e9, answer = -1;
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
