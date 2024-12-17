#include <fstream>
#include <vector>
#include <queue>

using namespace std;

ifstream cin("dining.in");
ofstream cout("dining.out");

const int NMAX = 5e4;
const int INF = 2e9;

struct PQElement {
    int node, cost;
    bool operator < (const PQElement &other) const {
        return other.cost < cost;;
    }
};

int n, m, k;
int cost[NMAX + 1][2];
int haybale[NMAX + 1];
int max_value[NMAX + 1];
vector<pair<int, int>> g[NMAX + 1];

void Dijkstra(int type) {
    for(int i = 1; i <= n; i++) {
        cost[i][type] = INF;
    }

    priority_queue<PQElement> pq;
    if(type == 0) {
        cost[n][0] = 0;
        pq.push({n, 0});
    }
    else {
        for(int i = 1; i <= k; i++) {
            cost[haybale[i]][1] = cost[haybale[i]][0] - max_value[haybale[i]];
            pq.push({haybale[i], cost[haybale[i]][1]});
        }
    }

    while(!pq.empty()) {
        auto [node, curent_cost] = pq.top();
        pq.pop();

        if(curent_cost != cost[node][type]) {
            continue;
        }

        for(auto [next_node, edge_cost] : g[node]) {
            int next_cost = curent_cost + edge_cost;
            if(next_cost < cost[next_node][type]) {
                cost[next_node][type] = next_cost;
                pq.push({next_node, next_cost});
            }
        }
    }
}

int main()
{
    cin >> n >> m >> k;
    for(int i = 1; i <= m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        g[a].push_back({b, c});
        g[b].push_back({a, c});
    }

    for(int i = 1; i <= k; i++) {
        int node, value;
        cin >> node >> value;
        haybale[i] = node;
        max_value[node] = max(max_value[node], value);
    }

    Dijkstra(0);
    Dijkstra(1);
    for(int i = 1; i <= n - 1; i++) {
//        cout << cost[i][0] << ' ' << cost[i][1] << '\n';
        cout << (cost[i][0] >= cost[i][1]) << '\n';
    }

    return 0;
}
