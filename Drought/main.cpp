#include <bits/stdc++.h>

using namespace std;

const int NMAX = 100;
const int HMAX = 1000;
const int MOD = 1e9 + 7;

int n;
int h[NMAX + 1];
int dp[NMAX + 1][HMAX + 1];
int sp[NMAX + 1][HMAX + 1];

int solve(int diff) {
    for(int i = 2; i <= n; i++) {
        for(int j = 0; j <= HMAX; j++) {
            dp[i][j] = sp[i][j] = 0;
        }
    }

    for(int i = 0; i <= min(h[1] - diff, h[2] - diff); i++) {
        dp[2][i] = 1;
    }

    sp[2][0] = dp[2][0];
    for(int i = 1; i <= h[2]; i++) {
        sp[2][i] = sp[2][i - 1] + dp[2][i];
    }

    for(int i = 3; i <= n; i++) {
        for(int j = 0; j <= h[i] - diff; j++) {
//            for(int jprev = 0; jprev <= h[i - 1] - diff - j; jprev++) {
//                dp[i][j] = (dp[i][j] + dp[i - 1][jprev]) % MOD;
//            }
            if(h[i - 1] - diff - j >= 0) {
                dp[i][j] = sp[i - 1][h[i - 1] - diff - j];
            }
        }

        sp[i][0] = dp[i][0];
        for(int j = 1; j <= h[i] - diff; j++) {
            sp[i][j] = (sp[i][j - 1] + dp[i][j]) % MOD;
        }
    }

//    int answer = 0;
//    for(int i = 0; i <= h[n] - diff; i++) {
//        answer = (answer + dp[n][i]) % MOD;
//    }
//    return answer;
    return sp[n][h[n] - diff];
}

int main()
{
    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> h[i];
    }

    if(n % 2 == 0) {
        cout << solve(0) << '\n';
    }
    else {
        int answer = 0;
        int mini = *min_element(h + 1, h + n + 1);
        for(int i = 0; i <= mini; i++) {
            answer = (answer + solve(i)) % MOD;
        }
        cout << answer << '\n';
    }
    return 0;
}
