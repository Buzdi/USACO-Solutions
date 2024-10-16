#include <fstream>
#include <algorithm>
#include <vector>
#define ll long long

using namespace std;

ifstream cin("mootube.in");
ofstream cout("mootube.out");

const int NMAX = 5000;

int n, Q, answer;
vector<pair<int, int>> G[NMAX + 1];

void DFS(int node, int k, int dad = 0) {
    answer++;
    for(auto [next_node, r] : G[node]) {
        if(next_node != dad && r >= k) {
            DFS(next_node, k, node);
        }
    }
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> n >> Q;
	for(int i = 1; i <= n - 1; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        G[a].push_back({b, c});
        G[b].push_back({a, c});
	}

    while(Q--) {
        int node, k;
        cin >> k >> node;
        answer = 0;
        DFS(node, k);
        cout << answer - 1 << '\n';
    }

	return 0;
}
