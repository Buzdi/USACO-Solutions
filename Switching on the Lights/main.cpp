#include <fstream>
#include <algorithm>
#include <cassert>
#include <cmath>
#include <iomanip>
#include <vector>
#include <queue>
#include <map>
#include <set>
#define ll long long

using namespace std;

ifstream cin("lightson.in");
ofstream cout("lightson.out");

const int NMAX = 100;
const int di[] = { 0, 0, 1, -1 };
const int dj[] = { 1, -1, 0, 0 };

int n, m, answer;
vector<pair<int, int>> G[NMAX + 1][NMAX + 1];
bool lit[NMAX + 1][NMAX + 1];
bool can_add[NMAX + 1][NMAX + 1];
bool visited[NMAX + 1][NMAX + 1];

bool InMat(int i, int j) {
    return i >= 1 && i <= n && j >= 1 && j <= n;
}

void DFS(int istart, int jstart) {
    queue<pair<int, int>> Q;
    lit[istart][jstart] = can_add[istart][jstart] = visited[istart][jstart] = 1;
    Q.push({ istart, jstart });
    while (!Q.empty()) {
        auto [i, j] = Q.front();
        Q.pop();

        for (auto [inou, jnou] : G[i][j]) {
            if (can_add[inou][jnou] && !visited[inou][jnou]) {
                visited[inou][jnou] = 1;
                Q.push({ inou, jnou });
            }
            lit[inou][jnou] = 1;
        }

        for (int d = 0; d < 4; d++) {
            int inou = i + di[d];
            int jnou = j + dj[d];
            if (InMat(inou, jnou)) {
                if (lit[inou][jnou] && !visited[inou][jnou]) {
                    visited[inou][jnou] = 1;
                    Q.push({ inou, jnou });
                }
                else if (!lit[inou][jnou]) {
                    can_add[inou][jnou] = 1;
                }
            }
        }
    }
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int x, y, a, b;
        cin >> x >> y >> a >> b;
        G[x][y].push_back({ a, b });
    }

    DFS(1, 1);
    for (int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            answer += lit[i][j];
        }
    }
    cout << answer << '\n';

    return 0;
}
