#include <iostream>
#include <queue>
#include <set>

using namespace std;

const int NMAX = 25;
const int CMAX = 19682;

const int di[] = {0, 0, 1, -1};
const int dj[] = {1, -1, 0, 0};

struct Triplet {
    int i, j, code;
};

struct Move {
    int type, x, y;
}a[NMAX + 1][NMAX + 1];

int n, istart, jstart;
int p3[9];
set<int> winning;
char visited[NMAX + 1][NMAX + 1][CMAX + 1];

bool InMat(int i, int j) {
    return i >= 1 && i <= n && j >= 1 && j <= n;
}

bool WinState(int code) {
    int a[3][3] = {0};
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            a[i][j] = code % 3;
            code /= 3;
        }
    }

    for(int i = 0; i < 3; i++) {
        if(a[i][0] == 1 && a[i][1] == 2 && a[i][2] == 2) {
            return true;
        }
        if(a[i][0] == 2 && a[i][1] == 2 && a[i][2] == 1) {
            return true;
        }
    }

    for(int j = 0; j < 3; j++) {
        if(a[0][j] == 1 && a[1][j] == 2 && a[2][j] == 2) {
            return true;
        }
        if(a[0][j] == 2 && a[1][j] == 2 && a[2][j] == 1) {
            return true;
        }
    }

    if(a[0][0] == 1 && a[1][1] == 2 && a[2][2] == 2) {
        return true;
    }
    if(a[0][0] == 2 && a[1][1] == 2 && a[2][2] == 1) {
        return true;
    }

    if(a[0][2] == 1 && a[1][1] == 2 && a[2][0] == 2) {
        return true;
    }
    if(a[0][2] == 2 && a[1][1] == 2 && a[2][0] == 1) {
        return true;
    }
    return false;
}

int Add(int code, Move m) {
    if(m.type == 0) {
        return code;
    }
    int cell = m.x * 3 + m.y;
    if(code / p3[cell] % 3 != 0) {
        return code;
    }
    return code + p3[cell] * m.type;
}

void Fill(int istart, int jstart) {
    queue<Triplet> Q;
    visited[istart][jstart][0] = 1;
    Q.push({istart, jstart, 0});
    while(!Q.empty()) {
        auto [i, j, code] = Q.front();
        Q.pop();

        for(int d = 0; d < 4; d++) {
            int inou = i + di[d];
            int jnou = j + dj[d];
            if(InMat(inou, jnou) && a[inou][jnou].type != -1) {
                int codenou = Add(code, a[inou][jnou]);
                if(!visited[inou][jnou][codenou]) {
                    visited[inou][jnou][codenou] = 1;
                    if(!WinState(codenou)) {
                        Q.push({inou, jnou, codenou});
                    }
                    else {
                        winning.insert(codenou);
                    }
                }
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
        for(int j = 1; j <= n; j++) {
            char type, x, y;
            cin >> type >> x >> y;
            if(type == '#') {
                a[i][j] = {-1, -1, -1};
            }
            if(type == '.') {
                a[i][j] = {0, -1, -1};
            }
            if(type == 'M') {
                a[i][j] = {1, x - '0' - 1, y - '0' - 1};
            }
            if(type == 'O') {
                a[i][j] = {2, x - '0' - 1, y - '0' - 1};
            }
            if(type == 'B') {
                a[i][j] = {0, -1, -1};
                istart = i;
                jstart = j;
            }
        }
    }

    p3[0] = 1;
    for(int i = 1; i < 9; i++) {
        p3[i] = p3[i - 1] * 3;
    }

    Fill(istart, jstart);
    cout << winning.size() << '\n';

    return 0;
}
