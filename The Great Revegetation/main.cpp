#include <fstream>
#include <algorithm>
#include <cassert>
#include <cmath>
#include <vector>
#include <set>
#define ll long long

using namespace std;

ifstream cin("revegetate.in");
ofstream cout("revegetate.out");

const int NMAX = 2e5;

int n, m, components;
vector<pair<int, char>> G[NMAX + 1];
int visited[NMAX + 1];
bool okay;

void DFS(int node, int value) {
    visited[node] = value;
    for (auto [next_node, which] : G[node]) {
        if (visited[next_node] == -1) {
            DFS(next_node, visited[node] ^ (which == 'D' ? 1 : 0));
        }
        else if(visited[node] == visited[next_node] && which == 'D') {
            okay = false;
        }
        else if (visited[node] != visited[next_node] && which == 'S') {
            okay = false;
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
        char x;
        int a, b;
        cin >> x >> a >> b;
        G[a].push_back({ b, x });
        G[b].push_back({ a, x });
    }

    for (int i = 1; i <= n; i++) {
        visited[i] = -1;
    }

    okay = true;
    for (int i = 1; i <= n; i++) {
        if (visited[i] == -1) {
            DFS(i, 1);
            components++;
        }
    }

    if (okay) {
        cout << 1;
        for (int i = 1; i <= components; i++) {
            cout << 0;
        }
    }
    else {
        cout << 0;
    }

    return 0;
}
