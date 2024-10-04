#include <fstream>
#include <algorithm>
#include <cassert>
#include <cmath>
#include <queue>
#include <map>
#define ll long long

using namespace std;

ifstream cin("gates.in");
ofstream cout("gates.out");

const int NMAX = 4000;
const int dx[] = {0, 1, 0, -1};
const int dy[] = { 1, 0, -1, 0 };

char a[NMAX + 1][NMAX + 1];
int n, curent_x, curent_y, components;

bool InMat(int x, int y) {
    return x >= 0 && x <= NMAX && y >= 0 && y <= NMAX;
}

void DFS(int xstart, int ystart) {
    queue<pair<int, int>> Q;
    a[xstart][ystart] = 1;
    Q.push({ xstart, ystart });
    while (!Q.empty()) {
        auto [x, y] = Q.front();
        Q.pop();
        for (int d = 0; d < 4; d++) {
            int xnou = x + dx[d];
            int ynou = y + dy[d];
            if (InMat(xnou, ynou) && a[xnou][ynou] == 0) {
                a[xnou][ynou] = 1;
                Q.push({ xnou, ynou });
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

    curent_x = NMAX / 2, curent_y = NMAX / 2;
    a[curent_x][curent_y] = 1;
    for (int i = 1; i <= n; i++) {
        char s;
        cin >> s;

        int d;
        if (s == 'N') {
            d = 0;
        }
        else if (s == 'E') {
            d = 1;
        }
        else if (s == 'S') {
            d = 2;
        }
        else {
            d = 3;
        }
        for (int cnt = 1; cnt <= 2; cnt++) {
            curent_x += dx[d];
            curent_y += dy[d];
            a[curent_x][curent_y] = 1;
        }
    }

    for (int i = 0; i <= NMAX; i++) {
        for (int j = 0; j <= NMAX; j++) {
            if (a[i][j] == 0) {
                DFS(i, j);
                components++;
            }
        }
    }
    cout << components - 1;

    return 0;
}
