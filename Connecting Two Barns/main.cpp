#include <iostream>
#include <algorithm>
#include <cassert>
#include <cmath>
#include <vector>
#include <set>
#define ll long long
#define int long long

using namespace std;

const int NMAX = 1e5;
const ll INF = 1e18;

int n, m, components;
vector<int> G[NMAX + 1];
bool visited[NMAX + 1];
vector<int> component[NMAX + 1];
int which_component[NMAX + 1];

ll Square(int x) {
    return (ll)x * x;
}

void Erase() {
    for (int i = 1; i <= n; i++) {
        visited[i] = 0;
        which_component[i] = 0;
        G[i].clear();
    }
    for (int i = 1; i <= components; i++) {
        component[i].clear();
    }
    components = 0;
}

void DFS(int node) {
    visited[node] = 1;
    which_component[node] = components;
    component[components].push_back(node);
    for (int next_node : G[node]) {
        if (!visited[next_node]) {
            DFS(next_node);
        }
    }
}

ll GetMinCost(int first_component, int second_component) {
    if (component[first_component].size() < component[second_component].size()) {
        swap(first_component, second_component);
    }

    ll answer = INF;
    for (int node : component[second_component]) {
        auto it = lower_bound(component[first_component].begin(), component[first_component].end(), node);
        if (it != component[first_component].end()) {
            answer = min(answer, Square(*it - node));
        }
        if (it != component[first_component].begin()) {
            answer = min(answer, Square(node - *prev(it)));
        }
    }
    return answer;
}

void test_case() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int a, b;
        cin >> a >> b;
        G[a].push_back(b);
        G[b].push_back(a);
    }

    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            components++;
            DFS(i);
        }
    }

    if (which_component[n] == which_component[1]) {
        cout << 0 << '\n';
        Erase();
        return;  
    }

    for (int i = 1; i <= components; i++) {
        sort(component[i].begin(), component[i].end());
    }

    // Try 1
    ll answer = GetMinCost(which_component[1], which_component[n]);

    // Try 2
    for (int i = 1; i <= components; i++) {
        if (which_component[1] != i && which_component[n] != i) {
            answer = min(answer, GetMinCost(which_component[1], i) + GetMinCost(which_component[n], i));
        }
    }
    cout << answer << '\n';

    Erase();
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T;
    cin >> T;
    while (T--) {
        test_case();
    }

    return 0;
}
