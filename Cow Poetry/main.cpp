#include <fstream>
#define ll long long

using namespace std;

ifstream cin("poetry.in");
ofstream cout("poetry.out");

const int NMAX = 5000;
const int CMAX = 26;
const int MOD = 1e9 + 7;

int n, m, k, answer;
int s[NMAX + 1];
int c[NMAX + 1];
int dp[NMAX + 1];
int dp_c[NMAX + 1];
int dp_without[NMAX + 1];
int f[CMAX];

int Power(int a, int b) {
    int rez = 1;
    while (b) {
        if (b % 2 == 1) {
            rez = (ll)rez * a % MOD;
        }
        a = (ll)a * a % MOD;
        b /= 2;
    }
    return rez;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) {
        cin >> s[i] >> c[i];
    }

    for (int i = 1; i <= m; i++) {
        char s;
        cin >> s;
        f[s - 'A']++;
    }

    dp[0] = 1;
    for (int j = 1; j <= k; j++) {
        for (int i = 1; i <= n; i++) {
            if (j - s[i] >= 0) {
                dp[j] = (dp[j] + dp[j - s[i]]) % MOD;
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        dp_c[c[i]] = (dp_c[c[i]] + dp[k - s[i]]) % MOD;
    }

    answer = 1;
    for (int i = 0; i < 26; i++) {
        if (f[i]) {
            int answer_here = 0;
            for (int j = 1; j <= n; j++) {
                answer_here = (answer_here + Power(dp_c[j], f[i])) % MOD;
            }
            answer = (ll)answer * answer_here % MOD;
        }
    }
    cout << answer << '\n';

    return 0;
}
