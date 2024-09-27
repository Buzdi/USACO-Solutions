#include <fstream>
#include <vector>

using namespace std;

ifstream cin("wormsort.in");
ofstream cout("wormsort.out");

const int NMAX = 1e5;

int n, m;
int a[NMAX + 1];
vector<pair<int, int>> G[NMAX + 1];
bool visited[NMAX + 1];

void DFS(int node, int k) {
    visited[node] = 1;
    for(auto [next_node, width] : G[node]) {
        if(!visited[next_node] && width >= k) {
            DFS(next_node, k);
        }
    }
}

bool Check(int k) {
    for(int i = 1; i <= n; i++) {
        visited[i] = 0;
    }

    for(int i = 1; i <= n; i++) {
        if((visited[i] ^ visited[a[i]]) && i != a[i]) {
            return false;
        }
        if(!visited[i]) {
            DFS(i, k);
        }
        if((visited[i] ^ visited[a[i]]) && i != a[i]) {
            return false;
        }
    }
    return true;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int i = 1; i <= m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        G[a].push_back({b, c});
        G[b].push_back({a, c});
    }

    int left = 1, right = 1e9 + 1, answer = -1;
    while(left <= right) {
        int mid = left + (right - left) / 2;
        if(Check(mid)) {
            answer = mid;
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    cout << (answer == 1e9 + 1 ? -1 : answer) << '\n';

    return 0;
}
