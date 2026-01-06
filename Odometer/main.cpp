#include <bits/stdc++.h>
#define ll long long

using namespace std;

ifstream fin("odometer.in");
ofstream fout("odometer.out");

const int NMAX = 19;
const int DMAX = 38;

string s;
ll l, r;
ll dp[NMAX + 1][DMAX + 1][2][2]; /// dp[i][dif][under][started]

void reset() {
    for(int i = 0; i <= NMAX; i++) {
        for(int j = 0; j <= DMAX; j++) {
            dp[i][j][0][0] = dp[i][j][0][1] = dp[i][j][1][0] = dp[i][j][1][1] = -1;
        }
    }
}

ll solve_dp(int i, int k, bool under, bool started, int cif_need1, int cif_need2) {
    if(i == s.size()) {
        if(!started) {
            /// Nu am inceput numarul
            return 0;
        }

        if(cif_need2 != -1) {
            /// Diferenta trebuie sa fie 0
            return k == 0;
        }
        /// Diferenta trebuie sa fie >= 0
        return k >= 0;
    }

    /// Memoizare
    if(dp[i][k + NMAX][under][started] != -1) {
        return dp[i][k + NMAX][under][started];
    }

    int lim = s[i] - '0';
    ll dp_here = 0;
    for(int cif = 0; cif < 10; cif++) {
        if(!under && cif > lim) {
            continue;
        }

        bool next_under = under | (cif < lim);
        bool next_started = started | (cif != 0);

        if(next_started && cif_need2 != -1 && cif != cif_need1 && cif != cif_need2) {
            continue;
        }

        int next_k = k;
        if(next_started) {
            next_k += (cif == cif_need1 ? 1 : -1);
        }
        dp_here += solve_dp(i + 1, next_k, next_under, next_started, cif_need1, cif_need2);
    }
    return dp[i][k + NMAX][under][started] = dp_here;
}

ll solve(ll n) {
    s = to_string(n);
    ll answer = 0;
    for(int i = 0; i < 10; i++) {
        reset();
        answer += solve_dp(0, 0, 0, 0, i, -1);
    }

    for(int i = 0; i < 10; i++) {
        for(int j = i + 1; j < 10; j++) {
            reset();
            answer -= solve_dp(0, 0, 0, 0, i, j);
        }
    }
    return answer;
}

int main()
{
    fin >> l >> r;
    fout << solve(r) - solve(l - 1) << '\n';
    return 0;
}
