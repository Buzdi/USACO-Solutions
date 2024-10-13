#include <fstream>
#include <algorithm>
#include <vector>
#include <queue>
#define ll long long

using namespace std;

ifstream cin("where.in");
ofstream cout("where.out");

const int NMAX = 20;
const int di[] = { 0, 0, 1, -1 };
const int dj[] = { 1, -1, 0, 0 };

struct Rectangle {
    int i1, j1, i2, j2;
};

int n, w, h;
char a[NMAX + 1][NMAX + 1];
bool visited[NMAX + 1][NMAX + 1];
vector<Rectangle> answer;

bool InMat(int i, int j, int i1, int j1, int i2, int j2) {
    return i >= i1 && i <= i2 && j >= j1 && j <= j2;
}

void Fill(int istart, int jstart, int i1, int j1, int i2, int j2) {
    queue<pair<int, int>> Q;
    visited[istart][jstart] = 1;
    Q.push({ istart, jstart });
    while (!Q.empty()) {
        auto [i, j] = Q.front();
        Q.pop();

        for (int d = 0; d < 4; d++) {
            int inou = i + di[d];
            int jnou = j + dj[d];
            if (InMat(inou, jnou, i1, j1, i2, j2) && a[inou][jnou] == a[i][j] && !visited[inou][jnou]) {
                visited[inou][jnou] = 1;
                Q.push({ inou, jnou });
            }
        }
    }
}

void Solve(int i1, int j1, int i2, int j2) {
    int f[26] = { 0 };
    for (int i = i1; i <= i2; i++) {
        for (int j = j1; j <= j2; j++) {
            visited[i][j] = 0;
        }
    }

    for (int i = i1; i <= i2; i++) {
        for (int j = j1; j <= j2; j++) {
            if (!visited[i][j]) {
                Fill(i, j, i1, j1, i2, j2);
                f[a[i][j] - 'A']++;
            }
        }
    }

    int cnt = 0;
    for (int i = 0; i < 26; i++) {
        if (f[i]) {
            cnt++;
        }
    }
    if (cnt != 2) {
        return;
    }

    int cnt_1 = 0, cnt_greater = 0;
    for(int i = 0; i < 26; i++) {
        if (!f[i]) {
            continue;
        }
        if (f[i] == 1) {
            cnt_1++;
        }
        else {
            cnt_greater++;
        }
    }

    if (cnt_1 == 2 || cnt_greater == 2) {
        return;
    }

    for (int i = 0; i < (int)answer.size(); i++) {
        if (answer[i].i1 <= i1 && answer[i].j1 <= j1 && answer[i].i2 >= i2 && answer[i].j2 >= j2) {
            return;
        }
    }

    vector<Rectangle> new_answer;
    for (int i = 0; i < (int)answer.size(); i++) {
        if (!(i1 <= answer[i].i1 && j1 <= answer[i].j1 && i2 >= answer[i].i2 && j2 >= answer[i].j2)) {
            new_answer.push_back(answer[i]);
        }
    }
    new_answer.push_back({ i1, j1, i2, j2 });
    answer = new_answer;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> a[i][j];
        }
    }

    for (int h = 1; h <= n; h++) {
        for (int w = 1; w <= n; w++) {
            for (int i = 1; i + h - 1 <= n; i++) {
                for (int j = 1; j + w - 1 <= n; j++) {
                    Solve(i, j, i + h - 1, j + w - 1);
                }
            }
        }
    }
    cout << answer.size() << '\n';

    return 0;
}
