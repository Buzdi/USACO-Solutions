#include <iostream>
#include <queue>
#include <set>
#include <cassert>

using namespace std;

const int NMAX = 3000;
const int di[] = {0, 0, 1, -1};
const int dj[] = {1, -1, 0, 0};

int n, total_cows;
char visited[NMAX + 1][NMAX + 1];

void Add(queue<pair<int, int>> &Q, int i, int j) {
    int neighbours = 0;
    for(int d = 0; d < 4; d++) {
        int inou = i + di[d];
        int jnou = j + dj[d];
        if(visited[inou][jnou]) {
            neighbours++;
        }
    }

    if(neighbours == 3) {
        for(int d = 0; d < 4; d++) {
            int inou = i + di[d];
            int jnou = j + dj[d];
            if(!visited[inou][jnou]) {
                visited[inou][jnou] = 1;
                total_cows++;
                Q.push({inou, jnou});
            }
        }
    }
}

void Fill(int istart, int jstart) {
    queue<pair<int, int>> Q;
    visited[istart][jstart] = 1;
    total_cows++;
    Q.push({istart, jstart});
    while(!Q.empty()) {
        auto [i, j] = Q.front();
        Q.pop();

        Add(Q, i, j);
        for(int d = 0; d < 4; d++) {
            int inou = i + di[d];
            int jnou = j + dj[d];
            if(visited[inou][jnou]) {
                Add(Q, inou, jnou);
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    for(int i = 1; i <= n; i++) {
        int x, y;
        cin >> x >> y;
        x += 1000; y += 1000;

        if(!visited[x][y]) {
            Fill(x, y);
        }
        cout << total_cows - i << '\n';
    }

    return 0;
}
