#include <fstream>
#include <vector>
#define ll long long

using namespace std;

ifstream cin("exercise.in");
ofstream cout("exercise.out");

const int NMAX = 1e4;

int n, MOD, answer;
char c[NMAX + 1];
vector<int> primes;
vector<vector<int>> dp;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> MOD;

    c[0] = c[1] = 1;
    for(int i = 2; i * i <= n; i++) {
        if(!c[i]) {
            for(int j = i + i; j <= n; j += i) {
                c[j] = 1;
            }
        }
    }

    for(int i = 2; i <= n; i++) {
        if(!c[i]) {
            primes.push_back(i);
        }
    }

    dp.resize(primes.size() + 1, vector<int>(n + 1));
    for(int j = 0; j <= n; j++) {
        dp[0][j] = 1;
    }

    for(int i = 1; i <= primes.size(); i++) {
        int curent_prime = primes[i - 1];
        for(int j = 0; j <= n; j++) {
            dp[i][j] = dp[i - 1][j];
            for(int factor = curent_prime; factor <= j; factor *= curent_prime) {
                dp[i][j] = (dp[i][j] + (ll)dp[i - 1][j - factor] * factor % MOD) % MOD;
            }
        }
    }
    cout << dp[primes.size()][n];

    return 0;
}
