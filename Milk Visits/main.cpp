#include <fstream>
#include <algorithm>
#include <vector>
#define ll long long

using namespace std;

ifstream cin("milkvisits.in");
ofstream cout("milkvisits.out");

const int NMAX = 1e5;

int n, m, components;
string s;
vector<int> G[NMAX + 1];
char which[NMAX + 1];
int component[NMAX + 1];

void DFS(int node) {
    component[node] = components;
    for(int next_node : G[node]) {
        if(!component[next_node] && s[next_node] == s[node]) {
            DFS(next_node);
        }
    }
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

    cin >> n >> m >> s;
    s = "%" + s;

    for(int i = 1; i <= n - 1; i++) {
        int a, b;
        cin >> a >> b;
        G[a].push_back(b);
        G[b].push_back(a);
    }

    for(int i = 1; i <= n; i++) {
        if(!component[i]) {
            components++;
            which[components] = s[i];
            DFS(i);
        }
    }

    while(m--) {
        int x, y;
        char c;
        cin >> x >> y >> c;
        if(component[x] == component[y] && which[component[x]] == c) {
            cout << 1;
        }
        else if(component[x] != component[y]) {
            cout << 1;
        }
        else {
            cout << 0;
        }
    }

	return 0;
}
