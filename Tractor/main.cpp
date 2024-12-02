#include <fstream>
#include <vector>
#include <cassert>
#include <queue>

using namespace std;

ifstream cin("tractor.in");
ofstream cout("tractor.out");

const int VMAX = 1e6;
const int NMAX = 500;
const int di[] = {0, 0, 1, -1};
const int dj[] = {1, -1, 0, 0};

int n, sz;
vector<pair<int, int>> positions[VMAX + 1];
int a[NMAX + 1][NMAX + 1];
char visited[NMAX + 1][NMAX + 1];

bool InMat(int i, int j) {
    return i >= 1 && i <= n && j >= 1 && j <= n;
}

int GetHash(int i, int j) {
    return (i - 1) * n + j;
}

void DFS(int istart, int jstart, int value) {
    queue<pair<int, int>> q;
    visited[istart][jstart] = 1;
    q.push({istart, jstart});
    sz++;
    while(!q.empty()) {
        auto [i, j] = q.front();
        q.pop();

        for(int d = 0; d < 4; d++) {
            int inou = i + di[d];
            int jnou = j + dj[d];
            if(InMat(inou, jnou) && abs(a[i][j] - a[inou][jnou]) <= value && !visited[inou][jnou]) {
                visited[inou][jnou] = 1;
                sz++;
                q.push({inou, jnou});
            }
        }
    }
}

bool Check(int value) {
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            visited[i][j] = 0;
        }
    }

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            if(!visited[i][j]) {
                sz = 0;
                DFS(i, j, value);
                if(sz >= (n * n) / 2 + (n * n) % 2) {
                    return true;
                }
            }
        }
    }
    return false;
}

int main()
{
    cin >> n;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            int x;
            cin >> x;
            a[i][j] = x;
        }
    }

    int left = 0, right = VMAX, answer = -1;
    while(left <= right) {
        int mid = (left + right) / 2;
        if(Check(mid)) {
            answer = mid;
            right = mid - 1;
        }
        else {
            left = mid + 1;
        }
    }
    cout << answer << '\n';

    return 0;
}
