#include <fstream>
#define ll long long

using namespace std;

ifstream cin("snakes.in");
ofstream cout("snakes.out");

const int NMAX = 400;
const ll INF = 1e18;

int n, k, maxi;
ll sum, answer;
int a[NMAX + 1];
ll dp[NMAX + 1][NMAX + 1];

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> k;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    for(int i = 0; i <= n; i++) {
        for(int j = 0; j <= k; j++) {
            dp[i][j] = INF;
        }
    }

    dp[0][0] = 0;
    for(int i = 1; i <= n; i++) {
        sum += a[i];
        maxi = max(maxi, a[i]);
        dp[i][0] = (ll) maxi * i - sum;
    }

    for(int j = 1; j <= k; j++) {
        for(int i = 1; i <= n; i++) {
            sum = 0;
            maxi = 0;
            for(int p = i; p >= 1; p--) {
                sum += a[p];
                maxi = max(maxi, a[p]);
                dp[i][j] = min(dp[i][j], dp[p - 1][j - 1] + (ll) maxi * (i - p + 1) - sum);
            }
        }
    }

    answer = INF;
    for(int j = 0; j <= k; j++) {
        answer = min(answer, dp[n][j]);
    }
    cout << answer << '\n';

    return 0;
}
