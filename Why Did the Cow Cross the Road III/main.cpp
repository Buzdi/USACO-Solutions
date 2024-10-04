#include <fstream>
#include <algorithm>
#include <cassert>
#include <cmath>
#include <queue>
#include <map>
#define ll long long

using namespace std;

const int NMAX = 100;
const int di[] = { 0, 0, 1, -1 };
const int dj[] = { 1, -1, 0, 0 };

ifstream cin("countcross.in");
ofstream cout("countcross.out");

struct DQElement {
    int i, j, cost;
};

int n, k, r, answer;
map<pair<int, int>, bool> mp[NMAX + 1][NMAX + 1];
int cost[NMAX + 1][NMAX + 1];
pair<int, int> cows[NMAX + 1];

bool InMat(int i, int j) {
    return i >= 1 && i <= n && j >= 1 && j <= n;
}

void BFS(int istart, int jstart) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cost[i][j] = -1;
        }
    }

    deque<DQElement> dq;
    dq.push_back({ istart, jstart, 0});
    while (!dq.empty()) {
        auto [i, j, curent_cost] = dq.back();
        dq.pop_back();
        
        if (cost[i][j] == -1) {
            cost[i][j] = curent_cost;
            for (int d = 0; d < 4; d++) {
                int inou = i + di[d];
                int jnou = j + dj[d];
                if (InMat(inou, jnou) && cost[inou][jnou] == -1) {
                    if (mp[i][j].find({ inou, jnou }) == mp[i][j].end()) {
                        dq.push_back({ inou, jnou, curent_cost });
                    }
                    else {
                        dq.push_front({ inou, jnou, curent_cost + 1 });
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

    cin >> n >> k >> r;
    for (int i = 1; i <= r; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        mp[x1][y1][{x2, y2}] = 1;
        mp[x2][y2][{x1, y1}] = 1;
    }

    for (int i = 1; i <= k; i++) {
        cin >> cows[i].first >> cows[i].second;
    }

    for (int i = 1; i <= k; i++) {
        BFS(cows[i].first, cows[i].second);
        for (int j = i + 1; j <= k; j++) {
            if (cost[cows[j].first][cows[j].second] >= 1) {
                answer++;
            }
        }
    }
    cout << answer << '\n';

    return 0;
}
