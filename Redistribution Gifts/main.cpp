#include <iostream>
#include <algorithm>
#include <cassert>
#include <cmath>
#include <vector>
#include <set>
#define ll long long

using namespace std;

const int NMAX = 500;

int n;
vector<int> G[NMAX + 1];
int visited[NMAX + 1][NMAX + 1];

void DFS(int start_node, int node) {
    visited[start_node][node] = 1;
    for (int next_node : G[node]) {
        if (!visited[start_node][next_node]) {
            DFS(start_node, next_node);
        }
    }
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int x;
            cin >> x;
            G[i].push_back(x);
        }
        while (G[i].back() != i) {
            G[i].pop_back();
        }
    }

    for (int i = 1; i <= n; i++) {
        DFS(i, i);
    }

    for (int i = 1; i <= n; i++) {
        for (int node : G[i]) {
            if (visited[node][i]) {
                cout << node << '\n';
                break;
            }
        }
    }

    return 0;
}
