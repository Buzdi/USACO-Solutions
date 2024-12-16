#include <fstream>
#include <queue>

#define ll long long

using namespace std;

ifstream cin("visitfj.in");
ofstream cout("visitfj.out");

const int NMAX = 100;
const ll INF = 1e18;

const int di[] = {0, 0, 1, -1};
const int dj[] = {1, -1, 0, 0};

struct PQElement {
    int i, j, k;
    ll cost;
    bool operator < (const PQElement &other) const {
        return other.cost < cost;
    }
};

int n, T;
ll answer;
int a[NMAX + 1][NMAX + 1];
ll cost[NMAX + 1][NMAX + 1][3];
priority_queue<PQElement> pq;

bool InMat(int i, int j) {
    return i >= 1 && i <= n && j >= 1 && j <= n;
}

int main()
{
    cin >> n >> T;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            cin >> a[i][j];
        }
    }

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            for(int k = 0; k < 3; k++) {
                cost[i][j][k] = INF;
            }
        }
    }

    cost[1][1][0] = 0;
    pq.push({1, 1, 0, 0});
    while(!pq.empty()) {
        auto [i, j, k, curent_cost] = pq.top();
        pq.pop();

        if(curent_cost != cost[i][j][k]) {
            continue;
        }

        for(int d = 0; d < 4; d++) {
            int inou = i + di[d];
            int jnou = j + dj[d];
            if(InMat(inou, jnou)) {
                int next_k = (k + 1) % 3;
                ll next_cost = curent_cost + T;
                if(next_k == 0) {
                    next_cost += a[inou][jnou];
                }

                if(next_cost < cost[inou][jnou][next_k]) {
                    cost[inou][jnou][next_k] = next_cost;
                    pq.push({inou, jnou, next_k, next_cost});
                }
            }
        }
    }

    answer = INF;
    for(int k = 0; k < 3; k++) {
        answer = min(answer, cost[n][n][k]);
    }
    cout << answer << '\n';

//    for(int k = 0; k < 3; k++, cout << '\n') {
//        for(int i = 1; i <= n; i++, cout << '\n') {
//            for(int j = 1; j <= n; j++) {
//                cout << cost[i][j][k] << ' ';
//            }
//        }
//    }

    return 0;
}
