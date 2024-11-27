#include <fstream>
#include <vector>
#include <queue>
#include <map>

using namespace std;

ifstream cin("lasers.in");
ofstream cout("lasers.out");

const int NMAX = 1e5;

int n, xl, yl, xb, yb, ID1, ID2;
pair<int, int> a[NMAX + 3];
vector<int> gx[NMAX + 1];
vector<int> gy[NMAX + 1];
map<int, int> mp1, mp2;
int d[NMAX + 1][2];

void BFS() {
    queue<pair<int, int>> q;
    for(int i = 1; i <= n; i++) {
        d[i][0] = d[i][1] = -1;
    }

    d[1][0] = d[1][1] = 0;
    for(int pos : gy[a[1].second]) {
        if(d[pos][0] == -1) {
            d[pos][0] = 1;
            q.push({pos, 0});
        }
    }
    for(int pos : gx[a[1].first]) {
        if(d[pos][1] == -1) {
            d[pos][1] = 1;
            q.push({pos, 1});
        }
    }
    gy[a[1].second].clear();
    gx[a[1].first].clear();

    while(!q.empty()) {
        auto [pos, which] = q.front();
        q.pop();

        if(which == 0) {
            for(int next_pos : gx[a[pos].first]) {
                if(d[next_pos][1] == -1) {
                    d[next_pos][1] = d[pos][0] + 1;
                    q.push({next_pos, 1});
                }
            }
            gx[a[pos].first].clear();
        }
        else {
            for(int next_pos : gy[a[pos].second]) {
                if(d[next_pos][0] == -1) {
                    d[next_pos][0] = d[pos][1] + 1;
                    q.push({next_pos, 0});
                }
            }
            gy[a[pos].second].clear();
        }
    }
}

int main()
{
    cin >> n >> a[1].first >> a[1].second >> a[n + 2].first >> a[n + 2].second;
    for(int i = 2; i <= n + 1; i++) {
        cin >> a[i].first >> a[i].second;
    }
    n += 2;

    for(int i = 1; i <= n; i++) {
        mp1[a[i].first] = 1;
        mp2[a[i].second] = 1;
    }

    for(auto &x : mp1) {
        x.second = ++ID1;
    }
    for(auto &x : mp2) {
        x.second = ++ID2;
    }

    for(int i = 1; i <= n; i++) {
        a[i].first = mp1[a[i].first];
        a[i].second = mp2[a[i].second];
    }

    for(int i = 1; i <= n; i++) {
        gx[a[i].first].push_back(i);
        gy[a[i].second].push_back(i);
    }

    BFS();
    if(d[n][0] == -1 && d[n][1] == -1) {
        cout << -1 << '\n';
    }
    else {
        cout << min(d[n][0] == -1 ? 1e9 : d[n][0], d[n][1] == -1 ? 1e9 : d[n][1]) - 1 << '\n';
    }


    return 0;
}
