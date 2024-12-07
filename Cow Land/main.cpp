#include <fstream>
#include <vector>

using namespace std;

ifstream cin("cowland.in");
ofstream cout("cowland.out");

const int NMAX = 1e5;
const int LOGMAX = 19;

struct AIB {
    int n;
    int aib[2 * NMAX + 1];

    void Initialize(int n) {
        this->n = n;
        for (int i = 1; i <= n; i++) {
            aib[i] = 0;
        }
    }

    void Update(int pos, int value) {
        for (int i = pos; i <= n; i += i & (-i)) {
            aib[i] ^= value;
        }
    }

    int Query(int pos) {
        int answer = 0;
        for (int i = pos; i >= 1; i -= i & (-i)) {
            answer ^= aib[i];
        }
        return answer;
    }
}aib;

int n, q, inde, indpm;
int depth[NMAX + 1];
int euler[2 * NMAX + 1];
int first_pos_euler[NMAX + 1];
int first_pos_pm[NMAX + 1];
int last_pos_pm[NMAX + 1];
int value[NMAX + 1];
vector<int> g[NMAX + 1];
int LOG[2 * NMAX + 1];
int rmq[LOGMAX + 1][2 * NMAX + 1];

void DFS(int node, int dad = 0) {
    depth[node] = depth[dad] + 1;

    euler[++inde] = node;
    first_pos_euler[node] = inde;

    indpm++;
    aib.Update(indpm, value[node]);
    first_pos_pm[node] = indpm;

    for (int next_node : g[node]) {
        if (next_node != dad) {
            DFS(next_node, node);
            euler[++inde] = node;
        }
    }

    indpm++;
    aib.Update(indpm, value[node]);
    last_pos_pm[node] = indpm;
}

void Precompute() {
    for (int i = 2; i <= inde; i++) {
        LOG[i] = LOG[i >> 1] + 1;
    }

    for (int i = 1; i <= inde; i++) {
        rmq[0][i] = euler[i];
    }
    for (int k = 1; (1 << k) <= inde; k++) {
        for (int i = 1; i + (1 << k) - 1 <= inde; i++) {
            int first_node = rmq[k - 1][i];
            int second_node = rmq[k - 1][i + (1 << (k - 1))];
            rmq[k][i] = (depth[first_node] < depth[second_node] ? first_node : second_node);
        }
    }
}

void Update(int node, int update_value) {
    aib.Update(first_pos_pm[node], value[node]);
    aib.Update(last_pos_pm[node], value[node]);
    value[node] = update_value;
    aib.Update(first_pos_pm[node], value[node]);
    aib.Update(last_pos_pm[node], value[node]);
}

int GetLCA(int x, int y) {
    int pos_x = first_pos_euler[x];
    int pos_y = first_pos_euler[y];
    if (pos_x > pos_y) {
        swap(pos_x, pos_y);
    }

    int k = LOG[pos_y - pos_x + 1];
    int first_node = rmq[k][pos_x];
    int second_node = rmq[k][pos_y - (1 << k) + 1];
    return (depth[first_node] < depth[second_node] ? first_node : second_node);
}

int QueryPM(int node) {
    return aib.Query(first_pos_pm[node]);
}

int Query(int x, int y) {
    int lca = GetLCA(x, y);
    return QueryPM(x) ^ QueryPM(y) ^ value[lca];
}

int main()
{
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> value[i];
    }

    for (int i = 1; i <= n - 1; i++) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    aib.Initialize(2 * n);
    DFS(1);
    Precompute();
    while (q--) {
        int type, x, y;
        cin >> type >> x >> y;
        if (type == 1) {
            Update(x, y);
        }
        else {
            cout << Query(x, y) << '\n';
        }
    }

    return 0;
}
