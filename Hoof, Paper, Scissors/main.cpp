#include <fstream>

using namespace std;

ifstream cin("hps.in");
ofstream cout("hps.out");

const int NMAX = 1e5;
const int KMAX = 20;
const int INF = 2e9;

int n, k, answer;
int a[NMAX + 1];
int dp[NMAX + 1][KMAX + 1][3];

int GetScore(int a, int b) {
    if(a == 0 && b == 2) {
        return 1;
    }
    if(a == 1 && b == 0) {
        return 1;
    }
    if(a == 2 && b == 1) {
        return 1;
    }
    return 0;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> k;
    for(int i = 1; i <= n; i++) {
        char s;
        cin >> s;
        if(s == 'H') {
            a[i] = 0;
        }
        else if(s == 'P') {
            a[i] = 1;
        }
        else {
            a[i] = 2;
        }
    }

    /// Base case
    dp[0][0][0] = dp[0][0][1] = dp[0][0][2] = 0;
    for(int j = 1; j <= k; j++) {
        for(int c = 0; c < 3; c++) {
            dp[0][j][c] = -INF;
        }
    }

    for(int i = 1; i <= n; i++) {
        for(int j = 0; j <= k; j++) {
            for(int c = 0; c < 3; c++) {
                int score = GetScore(c, a[i]);
                dp[i][j][c] = dp[i - 1][j][c] + score;

                if(j != 0) {
                    int max_dp_changing = -INF; /// ?
                    if(c != 0) {
                        max_dp_changing = max(max_dp_changing, dp[i - 1][j - 1][0]);
                    }
                    if(c != 1) {
                        max_dp_changing = max(max_dp_changing, dp[i - 1][j - 1][1]);
                    }
                    if(c != 2) {
                        max_dp_changing = max(max_dp_changing, dp[i - 1][j - 1][2]);
                    }
                    dp[i][j][c] = max(dp[i][j][c], max_dp_changing + score);
                }
            }
        }
    }

    answer = -INF;
    for(int j = 0; j <= k; j++) {
        for(int c = 0; c < 3; c++) {
            answer = max(answer, dp[n][j][c]);
        }
    }
    cout << answer << '\n';

    return 0;
}
