#include <fstream>
#include <algorithm>
#include <cassert>
#include <cmath>
#include <vector>
#define ll long long

using namespace std;

ifstream cin("closing.in");
ofstream cout("closing.out");

const int NMAX = 3000;
const int INF = 1e9;

int n, m, cnt;
vector<int> G[NMAX + 1];
bool blocked[NMAX + 1];
bool visited[NMAX + 1];

void DFS(int node) {
    visited[node] = 1;
    for (int next_node : G[node]) {
        if (!visited[next_node] && !blocked[next_node]) {
            DFS(next_node);
        }
    }
}

bool Check() {
    for (int i = 1; i <= n; i++) {
        visited[i] = 0;
    }

    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (!visited[i] && !blocked[i]) {
            DFS(i);
            cnt++;
        }
    }

    return cnt == 1;
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int a, b;
        cin >> a >> b;
        G[a].push_back(b);
        G[b].push_back(a);
    }

    cout << (Check() ? "YES" : "NO") << '\n';
    for (int i = 1; i <= n - 1; i++) {
        int x;
        cin >> x;
        blocked[x] = 1;
        cout << (Check() ? "YES" : "NO") << '\n';
    }

    return 0;
}
