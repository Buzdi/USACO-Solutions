#include <fstream>
#include <vector>
#include <tuple>

using namespace std;

ifstream cin("milkvisits.in");
ofstream cout("milkvisits.out");

const int NMAX = 1e5;
const int LOGMAX = 18;

int n, m, ind_st;
int value[NMAX + 1];
vector<int> g[NMAX + 1];
int depth[NMAX + 1];
int euler[2 * NMAX + 1], ind_e;
int pos_euler[NMAX + 1];
int LOG[2 * NMAX + 1];
int rmq[LOGMAX + 1][2 * NMAX + 1];
vector<tuple<int, int, int>> queries[NMAX + 1];
bool answer[NMAX + 1];
vector<int> pos_v[NMAX + 1];
int pos[NMAX + 1];

void DFS(int node, int dad = 0) {
    depth[node] = depth[dad] + 1;
    euler[++ind_e] = node;
    pos_euler[node] = ind_e;

    for(int next_node : g[node]) {
        if(next_node != dad) {
            DFS(next_node, node);
            euler[++ind_e] = node;
        }
    }
}

void Precompute() {
    for(int i = 2; i <= ind_e; i++) {
        LOG[i] = LOG[i >> 1] + 1;
    }

    for(int i = 1; i <= ind_e; i++) {
        rmq[0][i] = euler[i];
    }
    for(int k = 1; (1 << k) <= ind_e; k++) {
        for(int i = 1; i + (1 << k) - 1 <= ind_e; i++) {
            int first_node = rmq[k - 1][i];
            int second_node = rmq[k - 1][i + (1 << (k - 1))];
            rmq[k][i] = (depth[first_node] < depth[second_node] ? first_node : second_node);
        }
    }
}

int GetLCA(int x, int y) {
    x = pos_euler[x];
    y = pos_euler[y];
    if(x > y) {
        swap(x, y);
    }

    int k = LOG[y - x + 1];
    int first_node = rmq[k][x];
    int second_node = rmq[k][y - (1 << k) + 1];
    return (depth[first_node] < depth[second_node] ? first_node : second_node);
}

bool SolveQuery(int lca, int x) {
    auto it = lower_bound(pos_v[x].begin(), pos_v[x].end(), pos[lca]);
    return it != pos_v[x].end();
}

void DFS2(int node, int dad = 0) {
    ind_st++;
    pos[node] = ind_st;
    pos_v[value[node]].push_back(ind_st);

    for(auto [lca, x, pos] : queries[node]) {
        answer[pos] |= SolveQuery(lca, x);
    }

    for(int next_node : g[node]) {
        if(next_node != dad) {
            DFS2(next_node, node);
        }
    }

    pos_v[value[node]].pop_back();
    pos[node] = 0;
    ind_st--;
}

int main() {
    cin >> n >> m;
    for(int i = 1; i <= n; i++) {
        cin >> value[i];
    }

    for(int i = 1; i <= n - 1; i++) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    DFS(1);
    Precompute();
    for(int i = 1; i <= m; i++) {
        int a, b, x;
        cin >> a >> b >> x;
        int lca = GetLCA(a, b);
        queries[a].push_back({lca, x, i});
        queries[b].push_back({lca, x, i});
    }

    DFS2(1);
    for(int i = 1; i <= m; i++) {
        cout << answer[i];
    }

    return 0;
}
