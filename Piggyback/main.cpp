#include <fstream>
#include <cassert>
#include <cstring>
#include <queue>
#define ll long long

using namespace std;

ifstream cin("piggyback.in");
ofstream cout("piggyback.out");

const int NMAX = 4e4;

int b, e, p, n, m, answer;
int d1[NMAX + 1], d2[NMAX + 1], dn[NMAX + 1];
vector<int> g[NMAX + 1];

void BFS(int start, int d[]) {
    for(int i = 1; i <= n; i++) {
        d[i] = -1;
    }

    queue<int> q;
    d[start] = 0;
    q.push(start);
    while(!q.empty()) {
        int node = q.front();
        q.pop();

        for(int next_node : g[node]) {
            if(d[next_node] == -1) {
                d[next_node] = d[node] + 1;
                q.push(next_node);
            }
        }
    }
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> b >> e >> p >> n >> m;
	for(int i = 1; i <= m; i++) {
        int x, y;
        cin >> x >> y;
        g[x].push_back(y);
        g[y].push_back(x);
	}

    BFS(1, d1);
    BFS(2, d2);
    BFS(n, dn);

    answer = 2e9;
    for(int i = 1; i <= n; i++) {
        if(d1[i] != -1 && d2[i] != -1 && dn[i] != -1) {
            answer = min(answer, d1[i] * b + d2[i] * e + dn[i] * p);
        }
    }
    cout << answer << '\n';

	return 0;
}
