#include <iostream>
#include <vector>
#define ll long long
using namespace std;

const int NMAX = 1e5;

int n;
int a[NMAX + 1], v[NMAX + 1], parent[NMAX + 1];
ll answer;
bool visited[NMAX + 1];
vector<int> G[NMAX + 1];

void DFS(int node) {
    visited[node] = 1;
    for (int next_node : G[node]) {
        if (!visited[next_node]) {
            DFS(next_node);
        }
    }
}

int Floyd(int i) {
    int x = i, y = i;
    do {
        x = a[x];
        y = a[a[y]];
    } while (x != y);

    x = i;
    while (x != y) {
        x = a[x];
        y = a[y];
    }

    int first = x;
    int mini = 2e9;
    do
    {
        mini = min(mini, v[x]);
        x = a[x];
    } while (x != first);

    DFS(first);
    return mini;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i] >> v[i];
        G[a[i]].push_back(i);
        answer += v[i];
    }

    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            answer -= Floyd(i);
        }
    }
    cout << answer << '\n';

    return 0;
}
