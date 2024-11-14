#include <fstream>
#define ll long long

using namespace std;

ifstream cin("teamwork.in");
ofstream cout("teamwork.out");

const int NMAX = 1e4;

int n, k;
int a[NMAX + 1];
ll dp[NMAX + 1];

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> k;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    for(int i = 1; i <= n; i++) {
        int maxi = 0;
        for(int j = i; j >= max(1, i - k + 1); j--) {
            maxi = max(maxi, a[j]);
            dp[i] = max(dp[i], dp[j - 1] + (ll) maxi * (i - j + 1));
        }
    }
    cout << dp[n];

    return 0;
}
