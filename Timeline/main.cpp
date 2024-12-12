#include <fstream>
#include <vector>

using namespace std;

ifstream cin("timeline.in");
ofstream cout("timeline.out");

const int NMAX = 1e5;

int n, m, c, ind;
int answer[NMAX + 1];
int topsort[NMAX + 1];
vector<pair<int, int>> g[NMAX + 1];
char visited[NMAX + 1];

void DFS(int node) {
    visited[node] = 1;
    for(auto [next_node, steps] : g[node]) {
        if(!visited[next_node]) {
            DFS(next_node);
        }
    }
    topsort[++ind] = node;
}

int main()
{
    cin >> n >> m >> c;
    for(int i = 1; i <= n; i++) {
        cin >> answer[i];
    }

    for(int i = 1; i <= c; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        g[a].push_back({b, c});
    }

    for(int i = 1; i <= n; i++) {
        if(!visited[i]) {
            DFS(i);
        }
    }

    for(int i = ind; i >= 1; i--) {
        int node = topsort[i];
        for(auto [next_node, days] : g[node]) {
            answer[next_node] = max(answer[next_node], answer[node] + days);
        }
    }

    for(int i = 1; i <= n; i++) {
        cout << answer[i] << '\n';
    }

    return 0;
}
