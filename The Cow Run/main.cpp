#include <bits/stdc++.h>

using namespace std;

ifstream fin("cowrun.in");
ofstream fout("cowrun.out");

const int INF = 1e9;

int n;
vector<int> a, b;
vector<vector<int>> dp[2];

int main()
{
    fin >> n;
    for(int i = 1; i <= n; i++) {
        int x;
        fin >> x;
        if(x < 0) {
            a.push_back(-x);
        }
        else {
            b.push_back(x);
        }
    }
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    dp[0].resize(a.size() + 1, vector<int>(b.size() + 1, INF));
    dp[1].resize(a.size() + 1, vector<int>(b.size() + 1, INF));
    dp[0][0][0] = dp[1][0][0] = 0;
    for(int i = 1; i <= a.size(); i++) {
        dp[0][i][0] = dp[0][i - 1][0] + (n - i + 1) * (a[i - 1] - (i - 2 >= 0 ? a[i - 2] : 0));
    }
    for(int j = 1; j <= b.size(); j++) {
        dp[1][0][j] = dp[1][0][j - 1] + (n - j + 1) * (b[j - 1] - (j - 2 >= 0 ? b[j - 2] : 0));
    }
    for(int i = 1; i <= a.size(); i++) {
        for(int j = 1; j <= b.size(); j++) {
            dp[0][i][j] = min(dp[0][i - 1][j] + (n - i - j + 1) * (a[i - 1] - (i - 2 >= 0 ? a[i - 2] : 0)), dp[1][i - 1][j] + (n - i - j + 1) * (b[j - 1] + a[i - 1]));
            dp[1][i][j] = min(dp[1][i][j - 1] + (n - i - j + 1) * (b[j - 1] - (j - 2 >= 0 ? b[j - 2] : 0)), dp[0][i][j - 1] + (n - i - j + 1) * (a[i - 1] + b[j - 1]));
        }
    }
    fout << min(dp[0][a.size()][b.size()], dp[1][a.size()][b.size()]);
//    cout << dp[0][a.size()][b.size()] << ' ' << dp[1][a.size()][b.size()] << '\n';
    return 0;
}
