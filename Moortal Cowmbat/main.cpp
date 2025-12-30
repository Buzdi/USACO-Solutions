#include <bits/stdc++.h>
#define ll long long
using namespace std;

ifstream fin("cowmbat.in");
ofstream fout("cowmbat.out");

const int INF = 2e9;
const int NMAX = 1e5;
const int MMAX = 26;

int n, m, k, answer;
string s;
int a[MMAX + 1][MMAX + 1];
int sp[NMAX + 1][MMAX + 1];
int dp[NMAX + 1][MMAX + 1];
int mini[NMAX + 1][MMAX + 1];

signed main()
{
    fin >> n >> m >> k >> s;
    s = "$" + s;
    for(int i = 1; i <= m; i++) {
        for(int j = 1; j <= m; j++) {
            fin >> a[i][j];
        }
    }

    for(int k = 1; k <= m; k++) {
        for(int i = 1; i <= m; i++) {
            for(int j = 1; j <= m; j++) {
                a[i][j] = min(a[i][j], a[i][k] + a[k][j]);
            }
        }
    }

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            sp[i][j] = sp[i - 1][j] + a[s[i] - 'a' + 1][j];
        }
    }

    for(int i = 1; i < k; i++) {
        for(int j = 1; j <= m; j++) {
            dp[i][j] = INF;
        }
    }
    for(int i = k; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            mini[i - k + 1][j] = mini[i - k][j];
            for(int jj = 1; jj <= m; jj++) {
                if(jj != j) {
                    mini[i - k + 1][j] = min(mini[i - k + 1][j], dp[i - k][jj] - sp[i - k][j]);
                }
            }
        }

        for(int j = 1; j <= m; j++) {
            dp[i][j] = INF;
            for(int jj = 1; jj <= m; jj++) {
                if(jj != j) {
                    dp[i][j] = min(dp[i][j], sp[i][j] + mini[i - k + 1][j]);
                }
            }
        }
    }

//    dp[0][0] = 0;
//    for(int i = 1; i < k; i++) {
//        for(int j = 1; j <= m; j++) {
//            dp[i][j] = INF;
//        }
//    }
//    for(int i = k; i <= n; i++) {
//        for(int j = 1; j <= m; j++) {
//            dp[i][j] = INF;
//            for(int ii = 1; ii <= i - k + 1; ii++) {
//                for(int jj = 1; jj <= m; jj++) {
//                    if(j != jj) {
//                        dp[i][j] = min(dp[i][j], dp[ii - 1][jj] + (sp[i][j] - sp[ii - 1][j]));
//                    }
//                }
//            }
//        }
//    }

    answer = INF;
    for(int j = 1; j <= m; j++) {
        answer = min(answer, dp[n][j]);
    }
    fout << answer << '\n';
    return 0;
}
