#include <fstream>
#include <vector>

using namespace std;

ifstream cin("closing.in");
ofstream cout("closing.out");

const int NMAX = 2e5;

struct DSU {
    int components;
    int parent[NMAX + 1];
    int sz[NMAX + 1];
    char blocked[NMAX + 1];

    void Initialize(int n) {
        for(int i = 1; i <= n; i++) {
            parent[i] = i;
            sz[i] = 1;
            blocked[i] = 1;
        }
    }

    int GetRoot(int node) {
        return parent[node] = (node == parent[node] ? node : GetRoot(parent[node]));
    }

    void Unite(int x, int y) {
        if(blocked[x] || blocked[y]) {
            return;
        }

        int root_x = GetRoot(x);
        int root_y = GetRoot(y);
        if(root_x == root_y) {
            return;
        }

        components--;
        if(sz[root_x] > sz[root_y]) {
            swap(root_x, root_y);
        }
        parent[root_x] = root_y;
        sz[root_y] += sz[root_x];
    }
}dsu;

int n, m;
int queries[NMAX + 1];
int answer[NMAX + 1];
vector<int> g[NMAX + 1];

int main()
{
    cin >> n >> m;
    for(int i = 1; i <= m; i++) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    for(int i = 1; i <= n; i++) {
        cin >> queries[i];
    }

    dsu.Initialize(n);
    answer[n] = 1;
    for(int i = n; i >= 1; i--) {
        int node = queries[i];
        dsu.blocked[node] = 0;
        dsu.components++;
        for(int next_node : g[node]) {
            dsu.Unite(node, next_node);
        }
        answer[i - 1] = (dsu.components == 1);
    }

    for(int i = 0; i <= n - 1; i++) {
        cout << (answer[i] ? "YES" : "NO") << '\n';
    }

    return 0;
}
