#include <fstream>
#include <vector>
#include <queue>

using namespace std;

ifstream cin("pump.in");
ofstream cout("pump.out");

const int INF = 1e9;
const int NMAX = 1000;

struct Edge {
    int node, cost, flow;
};

struct PQElement {
    int node, flow, cost;
    bool operator < (const PQElement &other) const {
        return other.cost < cost;
    }
};

int n, m, answer;
vector<Edge> g[NMAX + 1];
priority_queue<PQElement> pq;
int cost[NMAX + 1][NMAX + 1];

int main()
{
    cin >> n >> m;
    for(int i = 1; i <= m; i++) {
        int a, b, c, f;
        cin >> a >> b >> c >> f;
        g[a].push_back({b, c, f});
        g[b].push_back({a, c, f});
    }

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= NMAX; j++) {
            cost[i][j] = INF;
        }
    }

    cost[1][NMAX] = 0;
    pq.push({1, NMAX});
    while(!pq.empty()) {
        auto [node, curent_flow, curent_cost] = pq.top();
        pq.pop();

        if(curent_cost != cost[node][curent_flow]) {
            continue; /// Forgive me, Father
        }

        for(auto [next_node, edge_cost, edge_flow] : g[node]) {
            int next_cost = curent_cost + edge_cost;
            int next_flow = min(curent_flow, edge_flow);
            if(next_cost < cost[next_node][next_flow]) {
                cost[next_node][next_flow] = next_cost;
                pq.push({next_node, next_flow, next_cost});
            }
        }
    }

    for(int j = 1; j <= NMAX; j++) {
        answer = max(answer, (j * 1000000) / cost[n][j]);
    }
    cout << answer << '\n';

    return 0;
}
