#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>

#define ll long long

using namespace std;

const int NMAX = 1e5;
const int YMAX = 10;
const int DSU_NMAX = 1e5;

struct Edge {
    int x, y;
    ll cost;
    bool operator < (const Edge &other) const {
        return cost < other.cost;
    }
};

struct Point {
    int x, y;
}points[NMAX + 1];

struct DSU {
    int sz[DSU_NMAX + 1];
    int parent[DSU_NMAX + 1];
    
    void Initialize(int n) {
        for(int i = 1; i <= n; i++) {
            parent[i] = i;
            sz[i] = 1;
        }
    }

    int GetRoot(int node) {
        return parent[node] = (parent[node] == node ? node : GetRoot(parent[node]));
    }

    bool Unite(int x, int y) {
        int root_x = GetRoot(x);
        int root_y = GetRoot(y);
        if(root_x == root_y) {
            return false;
        }

        if(sz[root_x] > sz[root_y]) {
            swap(root_x, root_y);
        }
        sz[root_y] += sz[root_x];
        parent[root_x] = root_y;
        return true;
    }
}dsu;

int n;
ll answer;
vector<Edge> edges;
vector<pair<int, int>> pos_x[YMAX + 1];

ll Square(int x) {
    return (ll)x * x;
}

ll Distance(Point p1, Point p2) {
    return Square(p1.x - p2.x) + Square(p1.y - p2.y);
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> points[i].x >> points[i].y;
    }

    for(int i = 1; i <= n; i++) {
        pos_x[points[i].y].push_back({points[i].x, i});
    }

    for(int y = 0; y <= YMAX; y++) {
        sort(pos_x[y].begin(), pos_x[y].end());
    }

    for(int i = 1; i <= n; i++) {
        for(int y = 0; y <= YMAX; y++) {
            if(pos_x[y].empty()) {
                continue;
            }

            int pos1 = lower_bound(pos_x[y].begin(), pos_x[y].end(), make_pair(points[i].x, 0)) - pos_x[y].begin();
            int pos2 = pos1 - 1;
            if(pos_x[y][pos1].second == i) {
                assert(make_pair(pos_x[y][pos1].first, y) == make_pair(points[i].x, points[i].y));
                pos1++;
            }

            if(pos1 >= 0 && pos1 < (int) pos_x[y].size()) {
                edges.push_back({i, pos_x[y][pos1].second, Distance(points[i], {pos_x[y][pos1].first, y})});
            }
            if(pos2 >= 0 && pos2 < (int) pos_x[y].size()) {
                edges.push_back({i, pos_x[y][pos2].second, Distance(points[i], {pos_x[y][pos2].first, y})});
            }
        }
    }

    sort(edges.begin(), edges.end());
    dsu.Initialize(n);
    for(auto [a, b, c] : edges) {
        if(dsu.Unite(a, b)) {
            answer += c;
        }
    }
    cout << answer << '\n';

    return 0;
}