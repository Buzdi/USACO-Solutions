#include <iostream>
#include <algorithm>

using namespace std;

const int NMAX = 1e5;
const int INF = 2e9;

int n, t, L, sum, answer;
int a[NMAX + 1];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> t;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    L = 1;
    for(int i = 1; i <= n; i++) {
        sum += a[i];
        while(sum > t) {
            sum -= a[L++];
        }
        answer = max(answer, i - L + 1);
    }
    cout << answer << '\n';

    return 0;
}