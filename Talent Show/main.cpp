#include <fstream>
#define ll long long

using namespace std;

ifstream cin("talent.in");
ofstream cout("talent.out");

const int NMAX = 250;
const int INF = 2e9;
const int WMAX = 1000;

int n, w;
int weight[NMAX + 1];
int talent[NMAX + 1];
ll dp[WMAX + 1];

bool Check(int y) {
    for(int i = 0; i <= w; i++) {
        dp[i] = -INF;
    }
    dp[0] = 0;

    for(int i = 1; i <= n; i++) {
        ll value = 1000LL * talent[i] - (ll) y * weight[i];
        for(int j = w; j >= 0; j--) {
            int nxt_j = min(w, j + weight[i]);
            if(dp[j] != -INF) {
                dp[nxt_j] = max(dp[nxt_j], dp[j] + value);
            }
        }
    }
    return dp[w] >= 0;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> w;
    for(int i = 1; i <= n; i++) {
        cin >> weight[i] >> talent[i];
    }

    int left = 0, right = INF, answer = -1;
    while(left <= right) {
        int mid = (left + right) / 2;
        if(Check(mid)) {
            answer = mid;
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    cout << answer << '\n';

    return 0;
}
