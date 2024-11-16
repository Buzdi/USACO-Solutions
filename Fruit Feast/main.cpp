#include <fstream>

using namespace std;

const int NMAX = 5e6;

ifstream cin("feast.in");
ofstream cout("feast.out");

int n, a, b, answer;
char visited[NMAX + 1][2];

void DFS(int node, bool halfing) {
    if(visited[node][halfing]) {
        return;
    }

    visited[node][halfing] = 1;
    if(node + a <= n) {
        DFS(node + a, halfing);
    }
    if(node + b <= n) {
        DFS(node + b, halfing);
    }
    if(halfing) {
        DFS(node / 2, 0);
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> a >> b;
    DFS(0, 1);
    for(int i = 1; i <= n; i++) {
        if(visited[i][0] || visited[i][1]) {
            answer = i;
        }
    }
    cout << answer << '\n';

    return 0;
}
