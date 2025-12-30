#include <bits/stdc++.h>
#define ll long long
using namespace std;

ifstream fin("taming.in");
ofstream fout("taming.out");

const int NMAX = 100;
const int INF = 1e9;

int n;
int a[NMAX + 1];
int dp[NMAX + 1][NMAX + 1][NMAX + 1];

signed main()
{
    fin >> n;
    for(int i = 1; i <= n; i++) {
        fin >> a[i];
    }

    for(int l = 0; l <= n - 1; l++) {
        for(int br = 0; br <= n; br++) {
            dp[0][l][br] = INF;
        }
    }
    dp[0][0][0] = 0;
    for(int i = 1; i <= n; i++) {
        for(int l = 0; l <= n - 1; l++) {
            dp[i][l][0] = INF;
            for(int br = 1; br <= n; br++) {
                dp[i][l][br] = INF;
                if(l == 0) {
                    for(int l2 = 0; l2 <= n - 1; l2++) {
                        dp[i][l][br] = min(dp[i][l][br], dp[i - 1][l2][br - 1]);
                    }
                }
                else {
                    dp[i][l][br] = min(dp[i][l][br], dp[i - 1][l - 1][br]);
                }
                dp[i][l][br] += (a[i] != l);
            }
        }
    }

    for(int br = 1; br <= n; br++) {
        int answer = INF;
        for(int l = 0; l <= n - 1; l++) {
            answer = min(answer, dp[n][l][br]);
        }
        fout << answer << '\n';
    }
    return 0;
}
