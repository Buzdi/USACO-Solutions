#include <fstream>
#include <cassert>
#include <cstring>
#include <queue>
#define ll long long

using namespace std;

ifstream cin("atlarge.in");
ofstream cout("atlarge.out");

const int NMAX = 1e5;

int n, k;
vector<int> g[NMAX + 1];
queue<int> q;
int d[NMAX + 1];

int DFS(int node, int dad = 0, int curent_d = 1) {
    if(d[node] <= curent_d) {
        return 1;
    }

    int answer = 0;
    for(int next_node : g[node]) {
        if(next_node != dad) {
            answer += DFS(next_node, node, curent_d + 1);
        }
    }
    return answer;
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> n >> k;
	for(int i = 1; i <= n - 1; i++) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
	}

    for(int i = 1; i <= n; i++) {
        if(g[i].size() == 1) {
            d[i] = 1;
            q.push(i);
        }
    }

    while(!q.empty()) {
        int node = q.front();
        q.pop();

        for(int next_node : g[node]) {
            if(!d[next_node]) {
                d[next_node] = d[node] + 1;
                q.push(next_node);
            }
        }
    }

    cout << DFS(k) << '\n';

	return 0;
}
