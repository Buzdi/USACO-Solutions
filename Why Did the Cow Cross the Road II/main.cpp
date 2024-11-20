#include <fstream>

using namespace std;

ifstream cin("nocross.in");
ofstream cout("nocross.out");

const int NMAX = 1000;

int n;
int a[NMAX + 1];
int b[NMAX + 1];
int dp[NMAX + 1][NMAX + 1];

int main()
{
    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int i = 1; i <= n; i++) {
        cin >> b[i];
    }

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            dp[i][j] = max(max(dp[i - 1][j], dp[i][j - 1]), dp[i - 1][j - 1] + (abs(a[i] - b[j]) <= 4));
        }
    }
    cout << dp[n][n];

    return 0;
}
