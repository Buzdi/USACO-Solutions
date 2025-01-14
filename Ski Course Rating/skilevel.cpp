#include <fstream>
#include <cassert>
#include <vector>
#include <algorithm>

#define ll long long

using namespace std;

ifstream cin("skilevel.in");
ofstream cout("skilevel.out");

const int NMAX = 500;
const int INF = 1e9;
const int di[] = {0, 0, 1, -1};
const int dj[] = {1, -1, 0, 0};

struct Edge {
    int a, b;
    int c;
};

struct DSU {
    int parent[NMAX * NMAX + 1];
    int sz[NMAX * NMAX + 1];

    void Initialize(int n) {
        for(int i = 1; i <= n; i++) {
            parent[i] = i;
            sz[i] = 1;
        }
    }

    int GetRoot(int node) {
        return parent[node] = (parent[node] == node ? node : GetRoot(parent[node]));
    }

    void Unite(int x, int y) {
        int root_x = GetRoot(x);
        int root_y = GetRoot(y);
        if(root_x == root_y) {
            return;
        }

        if(sz[root_x] > sz[root_y]) {
            swap(root_x, root_y);
        }
        sz[root_y] += sz[root_x];
        parent[root_x] = root_y;
    }
}dsu;

int n, m, t, ind_start;
ll answer_sum;
bool done;
int a[NMAX + 1][NMAX + 1];
int start_pos[NMAX * NMAX + 1];
pair<int, int> to_check[NMAX * NMAX + 1];
int L[NMAX * NMAX + 1];
int R[NMAX * NMAX + 1];
int answer[NMAX * NMAX + 1];
vector<Edge> edges;

bool InMat(int i, int j) {
    return i >= 1 && i <= n && j >= 1 && j <= m;
}

bool cmpEdges(const Edge &e1, const Edge &e2) {
    return e1.c < e2.c;
}

int GetHash(int i, int j) {
    return (i - 1) * m + j;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m >> t;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            cin >> a[i][j];
        }
    }

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            int x;
            cin >> x;
            if(x) {
                start_pos[++ind_start] = GetHash(i, j);
            }
        }
    }

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            for(int d = 0; d < 4; d++) {
                int inou = i + di[d];
                int jnou = j + dj[d];
                if(InMat(inou, jnou)) {
                    edges.push_back({GetHash(i, j), GetHash(inou, jnou), abs(a[i][j] - a[inou][jnou])});
                }
            }
        }
    }
    sort(edges.begin(), edges.end(), cmpEdges);

    for(int i = 1; i <= ind_start; i++) {
        L[i] = 0;
        R[i] = 1e9;
        answer[i] = -1;
    }

    done = false;
    while(!done) {
        done = true;
        int ind_check = 0;
        for(int i = 1; i <= ind_start; i++) {
            if(L[i] <= R[i]) {
                int mid = (L[i] + R[i]) / 2;
                to_check[++ind_check] = {mid, i};
            }
        }
        sort(to_check + 1, to_check + ind_check + 1);

        if(ind_check != 0) {
            done = false;
            int ind = 0;
            dsu.Initialize(n * m);
            for(int i = 1; i <= ind_check; i++) {
                auto [mid, pos] = to_check[i];
                while(ind < (int) edges.size() && edges[ind].c <= mid) {
                    dsu.Unite(edges[ind].a, edges[ind].b);
                    ind++;
                }
                int curent_size = dsu.sz[dsu.GetRoot(start_pos[pos])];
                if(curent_size >= t) {
                    answer[pos] = mid;
                    R[pos] = mid - 1;
                }
                else {
                    L[pos] = mid + 1;
                }
            }
        }
    }

    for(int i = 1; i <= ind_start; i++) {
        assert(answer[i] != -1);
        answer_sum += answer[i];
    }
    cout << answer_sum << '\n';

    return 0;
}