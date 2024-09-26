#include <fstream>
#include <algorithm>
#include <cassert>
#include <cmath>
#include <vector>
#define ll long long

using namespace std;

ifstream cin("fenceplan.in");
ofstream cout("fenceplan.out");

const int NMAX = 1e5;
const int INF = 2e9;

struct Point {
    int x, y;
    void read() {
        cin >> x >> y;
    }
}points[NMAX + 1];

int n, m, x_1, y_1, x_2, y_2, answer;
vector<int> G[NMAX + 1];
bool visited[NMAX + 1];

void DFS(int node) {
    visited[node] = 1;
    x_1 = min(x_1, points[node].x);
    y_1 = min(y_1, points[node].y);
    x_2 = max(x_2, points[node].x);
    y_2 = max(y_2, points[node].y);

    for (int next_node : G[node]) {
        if (!visited[next_node]) {
            DFS(next_node);
        }
    }
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        points[i].read();
    }

    for (int i = 1; i <= m; i++) {
        int a, b;
        cin >> a >> b;
        G[a].push_back(b);
        G[b].push_back(a);
    }

    answer = INF;
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            x_1 = y_1 = INF;
            x_2 = y_2 = 0;
            DFS(i);
            answer = min(answer, 2 * (x_2 - x_1 + y_2 - y_1));
        }
    }
    cout << answer << '\n';

    return 0;
}
