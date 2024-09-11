#include <fstream>
#include <algorithm>
#include <vector>
#include <cassert>
#include <set>
#include <map>
#define ll long long

using namespace std;

ifstream cin("herding.in");
ofstream cout("herding.out");

const int NMAX = 1e5;
const int INF = 1e9;

int n;
int cows[NMAX + 1];

int GetMin() {
    if(cows[2] - cows[1] - 1 >= 2 && cows[n] - cows[2] + 1 == n - 1) {
        return 2;
    }
    if(cows[n] - cows[n - 1] - 1 >= 2 && cows[n - 1] - cows[1] + 1 == n - 1) {
        return 2;
    }

    int right = 1, most_cows = 0;
    for(int i = 1; i <= n; i++) {
        while(right <= n - 1 && cows[right + 1] - cows[i] + 1 <= n) {
            right++;
        }
        most_cows = max(most_cows, right - i + 1);
    }
    return n - most_cows;
}

int GetMax() {
    return max(cows[n] - cows[2], cows[n - 1] - cows[1]) - (n - 2);
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> n;
	for(int i = 1; i <= n; i++) {
        cin >> cows[i];
	}
    sort(cows + 1, cows + n + 1);
    cout << GetMin() << '\n' << GetMax();

	return 0;
}
