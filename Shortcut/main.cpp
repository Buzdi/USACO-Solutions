#include <fstream>
#include <vector>
#include <queue>

#define ll long long

using namespace std;

ifstream cin("shortcut.in");
ofstream cout("shortcut.out");

const int NMAX = 1e4;
const int INF = 2e9;

struct PQElement {
    int node, parent_node, distance;
    bool operator < (const PQElement &other) const {
        if(other.distance < distance) {
            return true;
        }
        if(other.distance == distance && other.parent_node < parent_node) {
            return true;
        }
        return false;
    }
};

int n, m, t;
ll answer;
int c[NMAX + 1];
int min_distance[NMAX + 1];
int parent[NMAX + 1];
int sub_tree_size[NMAX + 1];
vector<pair<int, int>> g[NMAX + 1];
vector<int> tree[NMAX + 1];

void Dijkstra(int start_node) {
    for(int i = 1; i <= n; i++) {
        min_distance[i] = INF;
    }

    priority_queue<PQElement> pq;
    pq.push({start_node, 0, 0});
    while(!pq.empty()) {
        auto [node, parent_node, distance] = pq.top();
        pq.pop();

        if(min_distance[node] == INF) {
            min_distance[node] = distance;
            parent[node] = parent_node;
            for(auto [next_node, edge_distance] : g[node]) {
                pq.push({next_node, node, edge_distance + distance});
            }
        }
    }
}

void DFS(int node, int dad = 0) {
    sub_tree_size[node] = c[node];
    for(int next_node : tree[node]) {
        if(next_node != dad) {
            DFS(next_node, node);
            sub_tree_size[node] += sub_tree_size[next_node];
        }
    }
}

signed main() {
    cin >> n >> m >> t;
    for(int i = 1; i <= n; i++) {
        cin >> c[i];
    }

    for(int i = 1; i <= m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        g[a].push_back({b, c});
        g[b].push_back({a, c});
    }

    Dijkstra(1);
    // for(int i = 1; i <= n; i++) {
    //     cout << min_distance[i] << ' ';
    // }
    // cout << '\n';
    // for(int i = 1; i <= n; i++) {
    //     cout << parent[i] << ' ';
    // }

    for(int i = 2; i <= n; i++) {
        tree[parent[i]].push_back(i);
    }
    DFS(1);
    for(int i = 1; i <= n; i++) {
        if(min_distance[i] > t) {
            answer = max(answer, (ll) (min_distance[i] - t) * sub_tree_size[i]);
        }
    }
    cout << answer << '\n';

    return 0;
}