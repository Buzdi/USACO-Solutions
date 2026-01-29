#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int NMAX = 300 + 1;
const int DMAX = 18;
const int MOD = 1e9 + 7;

int n, q;
char a[NMAX + 1];
int dp[NMAX + 1][DMAX + 1][DMAX + 1][3];
int answer[2][NMAX + 1][NMAX + 1];
ll A, B;

void reset() {
    for(int i = 1; i <= n; i++) {
        for(int l = 1; l <= DMAX; l++) {
            for(int r = 1; r <= DMAX; r++) {
                for(int c : {0, 1, 2}) {
                    dp[i][l][r][c] = 0;
                }
            }
        }
    }
}

void add_mod(int& x, int y) {
    x += y;
    if(x >= MOD) {
        x -= MOD;
    }
}

int compare(char c1, char c2) {
    if(c2 < c1) {
        return 0;
    }
    if(c2 == c1) {
        return 1;
    }
    return 2;
}

int next_left(int c1, int c2) {
    if(c2 != 1) {
        return c2;
    }
    return c1;
}

int next_right(int c1, int c2) {
    if(c2 == 1) {
        return c1;
    }
    if(c1 != 1) {
        return c1;
    }
    return c2;

}

void solve(int w, ll x) {
    string s = to_string(x);
    int d = s.size();
    s = "$" + s;

    for(int i = 1; i <= n; i++) {
        reset();
        for(int j = i - 1; j <= n; j++) {
            /// Vom aduna la answer dp-ul curent
            for(int l = 1; l <= d; l++) {
                add_mod(answer[w][i][j], dp[j][l][d][0]);
                add_mod(answer[w][i][j], dp[j][l][d][1]);
                if(l != 1) {
                    add_mod(answer[w][i][j], dp[j][l][d][2]);
                }
            }

            if(j == n) {
                continue;
            }

            for(int l = 1; l <= d; l++) {
                for(int r = l; r <= d; r++) {
                    for(int c : {0, 1, 2}) {
                        /// Nu adaug in numar
                        add_mod(dp[j + 1][l][r][c], dp[j][l][r][c]);

                        /// Adaug in stanga
                        if(l > 1) {
                            add_mod(dp[j + 1][l - 1][r][next_left(c, compare(s[l - 1], a[j + 1]))], dp[j][l][r][c]);
                        }

                        /// Adaug in dreapta
                        if(r < d) {
                            add_mod(dp[j + 1][l][r + 1][next_right(c, compare(s[r + 1], a[j + 1]))], dp[j][l][r][c]);
                        }
                    }
                }
            }

            for(int l = 1; l <= d; l++) {
                /// Creez prima cifra acum in 2 moduri
                add_mod(dp[j + 1][l][l][compare(s[l], a[j + 1])], 2);
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> A >> B;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    solve(0, A - 1);
    solve(1, B);

    cin >> q;
    while(q--) {
        int l, r;
        cin >> l >> r;
        cout << (answer[1][l][r] - answer[0][l][r] + MOD) % MOD << '\n';
    }
    return 0;
}
