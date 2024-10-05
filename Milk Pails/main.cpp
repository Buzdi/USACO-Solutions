#include <fstream>
#include <algorithm>
#include <cassert>
#include <cmath>
#include <queue>
#define ll long long

using namespace std;

ifstream cin("pails.in");
ofstream cout("pails.out");

const int XMAX = 200;
const int INF = 1e9;

int x, y, k, m, answer;
queue<pair<int, int>> Q;
int d[XMAX + 1][XMAX + 1];

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> x >> y >> k >> m;
    
    d[0][0] = 1;
    Q.push({ 0, 0 });
    while (!Q.empty()) {
        auto [i, j] = Q.front();
        Q.pop();
        assert(i >= 0 && j >= 0 && i <= x && j <= y);

        if (i != x && !d[x][j]) {
            d[x][j] = d[i][j] + 1;
            Q.push({ x, j });
        }
        if (j != y && !d[i][y]) {
            d[i][y] = d[i][j] + 1;
            Q.push({ i, y });
        }

        if (i != 0 && !d[0][j]) {
            d[0][j] = d[i][j] + 1;
            Q.push({ 0, j });
        }
        if (j != 0 && !d[i][0]) {
            d[i][0] = d[i][j] + 1;
            Q.push({ i, 0 });
        }

        if (!d[i - min(i, y - j)][j + min(i, y - j)]) {
            d[i - min(i, y - j)][j + min(i, y - j)] = d[i][j] + 1;
            Q.push({ i - min(i, y - j), j + min(i, y - j) });
        }
        if (!d[i + min(j, x - i)][j - min(j, x - i)]) {
            d[i + min(j, x - i)][j - min(j, x - i)] = d[i][j] + 1;
            Q.push({ i + min(j, x - i), j - min(j, x - i) });
        }
    }

    answer = INF;
    for (int i = 0; i <= x; i++) {
        for (int j = 0; j <= y; j++) {
            if (d[i][j] && d[i][j] - 1 <= k) {
                answer = min(answer, abs(m - (i + j)));
            }
        }
    }
    cout << answer << '\n';
    return 0;
}
