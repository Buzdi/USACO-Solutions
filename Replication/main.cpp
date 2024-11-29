#include <iostream>
#include <cassert>
#include <cstring>
#include <queue>
#include <map>
#include <unordered_map>
#include <string>
#define ll long long

using namespace std;

const int NMAX = 1000;
const int di[] = {0, 0, 1, -1};
const int dj[] = {1, -1, 0, 0};

int n, hours, answer;
char a[NMAX + 1][NMAX + 1];
int visited[NMAX + 1][NMAX + 1];
int d_rocks[NMAX + 1][NMAX + 1];
int d_robots[NMAX + 1][NMAX + 1];
queue<pair<int, int>> q_centers[NMAX + 1];

bool InMat(int i, int j) {
    return i >= 1 && i <= n && j >= 1 && j <= n;
}

void BFS_Rocks() {
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            d_rocks[i][j] = -1;
        }
    }

    queue<pair<int, int>> q;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            if(a[i][j] == '#') {
                d_rocks[i][j] = 0;
                q.push({i, j});
            }
        }
    }

    while(!q.empty()) {
        auto [i, j] = q.front();
        q.pop();

        for(int dir = 0; dir < 4; dir++) {
            int inou = i + di[dir];
            int jnou = j + dj[dir];
            if(InMat(inou, jnou) && d_rocks[inou][jnou] == -1) {
                d_rocks[inou][jnou] = d_rocks[i][j] + 1;
                q.push({inou, jnou});
            }
        }
    }
}

void BFS_GetCenters() {
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            d_robots[i][j] = -1;
        }
    }

    queue<pair<int, int>> q;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            if(a[i][j] == 'S') {
                d_robots[i][j] = 0;
                q.push({i, j});
            }
        }
    }

    while(!q.empty()) {
        auto [i, j] = q.front();
        q.pop();

        for(int dir = 0; dir < 4; dir++) {
            int inou = i + di[dir];
            int jnou = j + dj[dir];
            if(InMat(inou, jnou) && a[inou][jnou] != '#' && d_robots[inou][jnou] == -1) {
                if((d_robots[i][j] + 1) / hours < d_rocks[inou][jnou]) {
                    d_robots[inou][jnou] = d_robots[i][j] + 1;
                    q.push({inou, jnou});
                }
                else if((d_robots[i][j] + 1) % hours == 0 && (d_robots[i][j] + 1) / hours == d_rocks[inou][jnou]) {
                    d_robots[inou][jnou] = d_robots[i][j] + 1;
                }
            }
        }
    }
}

void BFS() {
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            if(d_robots[i][j] != -1) {
                visited[i][j] = 1;
                q_centers[d_rocks[i][j] - 1].push({i, j});
            }
        }
    }

    for(int r = n; r >= 1; r--) {
        while(!q_centers[r].empty()) {
            auto [i, j] = q_centers[r].front();
            q_centers[r].pop();

            for(int dir = 0; dir < 4; dir++) {
                int inou = i + di[dir];
                int jnou = j + dj[dir];
                if(InMat(inou, jnou) && a[inou][jnou] != '#' && !visited[inou][jnou]) {
                    visited[inou][jnou] = 1;
                    if(r > 0) {
                        q_centers[r - 1].push({inou, jnou});
                    }
                }
            }
        }
    }
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> n >> hours;
	for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            cin >> a[i][j];
        }
	}

	BFS_Rocks();
	BFS_GetCenters();
	BFS();

	for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            if(visited[i][j]) {
                answer++;
            }
        }
	}
	cout << answer << '\n';

	return 0;
}
