#include <iostream>
#include <algorithm>
#include <vector>
#define ll long long

using namespace std;

const int NMAX = 1e5;

int n;
ll answer;
vector<int> G[NMAX + 1];

void DFS(int node, int dad = 0) {
    int children = 1; /// Including myself
    for(int next_node : G[node]) {
        if(next_node != dad) {
            children++;
        }
    }

    int exp = 0;
    while((1 << exp) < children) {
        exp++;
    }
    answer += exp + (children - 1);

    for(int next_node : G[node]) {
        if(next_node != dad) {
            DFS(next_node, node);
        }
    }
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> n;
	for(int i = 1; i <= n - 1; i++) {
        int a, b;
        cin >> a >> b;
        G[a].push_back(b);
        G[b].push_back(a);
	}

    DFS(1);
    cout << answer;

	return 0;
}
