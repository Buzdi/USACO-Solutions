#include <fstream>
#include <algorithm>
#include <vector>
#include <queue>
#define ll long long

using namespace std;

ifstream cin("snowboots.in");
ofstream cout("snowboots.out");

const int NMAX = 250;

int n, b;
bool visited[NMAX + 1][NMAX + 1];
int a[NMAX + 1];
pair<int, int> boots[NMAX + 1];

void Fill(int istart, int jstart) {
    queue<pair<int, int>> Q;
    visited[istart][jstart] = 1;
    Q.push({istart, jstart});
    while(!Q.empty()) {
        auto [i, j] = Q.front();
        Q.pop();

        /// Go
        for(int p = i + 1; p <= min(n, i + boots[j].second); p++) {
            if(boots[j].first >= a[p] && !visited[p][j]) {
                visited[p][j] = 1;
                Q.push({p, j});
            }
        }

        /// Change
        for(int k = j + 1; k <= b; k++) {
            if(boots[k].first >= a[i] && !visited[i][k]) {
                visited[i][k] = 1;
                Q.push({i, k});
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> b;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int i = 1; i <= b; i++) {
        cin >> boots[i].first >> boots[i].second;
    }

    Fill(1, 1);
    for(int i = 1; i <= b; i++) {
        if(visited[n][i]) {
            cout << i - 1 << '\n';
            break;
        }
    }

    return 0;
}
