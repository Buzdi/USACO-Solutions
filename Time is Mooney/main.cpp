#include <fstream>
#include <vector>
#define ll long long

using namespace std;

ifstream cin("time.in");
ofstream cout("time.out");

const int NMAX = 1000;
const int INF = 2e9;

int n, m, c;
int a[NMAX + 1];
vector<int> gt[NMAX + 1];
ll answer;
int dp[NMAX + 1][NMAX + 1];

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m >> c;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    for(int i = 1; i <= m; i++) {
        int a, b;
        cin >> a >> b;
        gt[b].push_back(a);
    }

    for(int i = 1; i <= n; i++) {
        for(int j = 0; j <= NMAX; j++) {
            dp[i][j] = -INF;
        }
    }
    dp[1][0] = 0;

    for(int j = 1; j <= NMAX; j++) {
        for(int i = 1; i <= n; i++) {
            for(int i_v : gt[i]) {
                if(dp[i_v][j - 1] != -INF) {
                    dp[i][j] = max(dp[i][j], dp[i_v][j - 1] + a[i]);
                }
            }
        }
    }

    answer = 0;
    for(int j = 1; j <= NMAX; j++) {
        answer = max(answer, dp[1][j] - (ll) c * j * j);
    }
    cout << answer << '\n';

    return 0;
}
