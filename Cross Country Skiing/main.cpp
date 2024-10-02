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

ifstream cin("ccski.in");
ofstream cout("ccski.out");

const int NMAX = 500;
const int di[] = { 0, 0, 1, -1 };
const int dj[] = { 1, -1, 0, 0 };

int n, m, ind_w;
int a[NMAX + 1][NMAX + 1];
pair<int, int> waypoints[NMAX * NMAX + 1];
bool visited[NMAX + 1][NMAX + 1];

bool InMat(int i, int j) {
    return i >= 1 && i <= n && j >= 1 && j <= m;
}

bool Check(int D) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            visited[i][j] = 0;
        }
    }

    queue<pair<int, int>> Q;
    visited[waypoints[1].first][waypoints[1].second] = 1;
    Q.push(waypoints[1]);
    while (!Q.empty()) {
        auto [i, j] = Q.front();
        Q.pop();

        for (int d = 0; d < 4; d++) {
            int inou = i + di[d];
            int jnou = j + dj[d];
            if (InMat(inou, jnou) && abs(a[i][j] - a[inou][jnou]) <= D && !visited[inou][jnou]) {
                visited[inou][jnou] = 1;
                Q.push({ inou, jnou });
            }
        }
    }

    for (int i = 1; i <= ind_w; i++) {
        auto [x, y] = waypoints[i];
        if (!visited[x][y]) {
            return false;
        }
    }
    return true;
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> a[i][j];
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int x;
            cin >> x;
            if (x == 1) {
                waypoints[++ind_w] = { i, j };
            }
        }
    }

    int left = 0, right = 1e9, answer = -1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (Check(mid)) {
            answer = mid;
            right = mid - 1;
        }
        else {
            left = mid + 1;
        }
    }
    cout << answer << '\n';
    return 0;
}
