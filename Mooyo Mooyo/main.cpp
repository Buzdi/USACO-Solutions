#include <fstream>
#include <algorithm>
#include <vector>
#include <queue>
#define ll long long

using namespace std;

ifstream cin("mooyomooyo.in");
ofstream cout("mooyomooyo.out");

const int NMAX = 100;
const int MMAX = 10;
const int di[] = {0, 0, 1, -1};
const int dj[] = {1, -1, 0, 0};

int n, m, k, curent_size;
bool done;
char a[NMAX + 1][MMAX + 1];
bool visited[NMAX + 1][MMAX + 1];

bool InMat(int i, int j) {
    return i >= 1 && i <= n && j >= 1 && j <= m;
}

void FillSize(int istart, int jstart) {
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            visited[i][j] = 0;
        }
    }
    queue<pair<int, int>> Q;
    visited[istart][jstart] = 1;
    curent_size = 1;
    Q.push({istart, jstart});
    while(!Q.empty()) {
        auto [i, j] = Q.front();
        Q.pop();

        for(int d = 0; d < 4; d++) {
            int inou = i + di[d];
            int jnou = j + dj[d];
            if(InMat(inou, jnou) && a[inou][jnou] == a[i][j] && !visited[inou][jnou]) {
                visited[inou][jnou] = 1;
                curent_size++;
                Q.push({inou, jnou});
            }
        }
    }
}

void FillDelete(int istart, int jstart) {
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            visited[i][j] = 0;
        }
    }
    char start_c = a[istart][jstart];
    queue<pair<int, int>> Q;
    visited[istart][jstart] = 1;
    a[istart][jstart] = '0';
    Q.push({istart, jstart});
    while(!Q.empty()) {
        auto [i, j] = Q.front();
        Q.pop();

        for(int d = 0; d < 4; d++) {
            int inou = i + di[d];
            int jnou = j + dj[d];
            if(InMat(inou, jnou) && a[inou][jnou] == start_c && !visited[inou][jnou]) {
                visited[inou][jnou] = 1;
                a[inou][jnou] = '0';
                Q.push({inou, jnou});
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> k;
    m = 10;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            cin >> a[i][j];
        }
    }

    done = false;
    while(!done) {
        done = true;
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= m; j++) {
                if(a[i][j] != '0' && !visited[i][j]) {
                    FillSize(i, j);
                    if(curent_size >= k) {
                        done = false;
                        FillDelete(i, j);
                    }
                }
            }
        }
        if(!done) {
            for(int i = 1; i <= n; i++) {
                for(int j = 1; j <= m; j++) {
                    if(a[i][j] == '0') {
                        for(int k = i - 1; k >= 1; k--) {
                            a[k + 1][j] = a[k][j];
                        }
                        a[1][j] = '0';
                    }
                }
            }
        }

//        for(int i = 1; i <= n; i++, cout << '\n') {
//            for(int j = 1; j <= m; j++) {
//                cout << a[i][j];
//            }
//        }
//        cout << '\n';
    }

    for(int i = 1; i <= n; i++, cout << '\n') {
        for(int j = 1; j <= m; j++) {
            cout << a[i][j];
        }
    }

    return 0;
}
