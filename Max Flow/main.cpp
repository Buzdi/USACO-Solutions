#include <bits/stdc++.h>

using namespace std;

ifstream fin("maxflow.in");
ofstream fout("maxflow.out");

const int NMAX = 5e4;
const int LOGMAX = 16;

int n, k, ind_e;
vector<int> g[NMAX + 1];
int parent[NMAX + 1];
int depth[NMAX + 1];
int euler[2 * NMAX + 1];
int pos_e[NMAX + 1];
int rmq[LOGMAX + 1][2 * NMAX + 1];
int mars[NMAX + 1];

void DFS1(int node, int dad = 0) {
    parent[node] = dad;
    depth[node] = depth[dad] + 1;
    euler[++ind_e] = node;
    pos_e[node] = ind_e;

    for(int next_node : g[node]) {
        if(next_node != dad) {
            DFS1(next_node, node);
            euler[++ind_e] = node;
        }
    }
}

void precompute() {
    for(int i = 1; i <= ind_e; i++) {
        rmq[0][i] = euler[i];
    }
    for(int k = 1; (1 << k) <= ind_e; k++) {
        for(int i = 1; i + (1 << k) - 1 <= ind_e; i++) {
            int n1 = rmq[k - 1][i];
            int n2 = rmq[k - 1][i + (1 << (k - 1))];
            rmq[k][i] = (depth[n1] < depth[n2] ? n1 : n2);
        }
    }
}

int get_lca(int x, int y) {
    x = pos_e[x];
    y = pos_e[y];
    if(x > y) {
        swap(x, y);
    }

    int k = 31 - __builtin_clz(y - x + 1);
    int n1 = rmq[k][x];
    int n2 = rmq[k][y - (1 << k) + 1];
    return (depth[n1] < depth[n2] ? n1 : n2);
}

void DFS2(int node, int dad = 0) {
    for(int next_node : g[node]) {
        if(next_node != dad) {
            DFS2(next_node, node);
            mars[node] += mars[next_node];
        }
    }
}

int main()
{
    fin >> n >> k;
    for(int i = 1; i <= n - 1; i++) {
        int a, b;
        fin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    DFS1(1);
    precompute();
    for(int i = 1; i <= k; i++) {
        int x, y;
        fin >> x >> y;

        int lca = get_lca(x, y);
        mars[x]++;
        mars[y]++;
        mars[lca]--;
        mars[parent[lca]]--;
    }

    DFS2(1);
    fout << *max_element(mars + 1, mars + n + 1);
    return 0;
}
