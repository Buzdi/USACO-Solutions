#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define ll long long
#define ld long double

using namespace std;
using namespace __gnu_pbds;

ifstream fin("oracol.in");
ofstream fout("oracol.out");

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

const int NMAX = 500;
const int INF = 2e9;

int n;
int a[NMAX + 1][NMAX + 1];
int b[NMAX + 1][NMAX + 1];
int g[2 * NMAX + 1][2 * NMAX + 1];
int r[NMAX + 1];
int c[NMAX + 1];
int max_cost[2 * NMAX + 1];
char done[2 * NMAX + 1];

void Erase() {
    for(int i = 1; i <= 2 * n; i++) {
        for(int j = 1; j <= 2 * n; j++) {
            g[i][j] = 0;
        }
    }
}

int test_case() {
    fin >> n;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            fin >> a[i][j];
        }
    }
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            fin >> b[i][j];
        }
    }
    for(int i = 1; i <= n; i++) {
        fin >> r[i];
    }
    for(int i = 1; i <= n; i++) {
        fin >> c[i];
    }

    int total_cost = 0;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            if(a[i][j] == -1) {
                g[i][n + j] = b[i][j];
                g[n + j][i] = b[i][j];
                total_cost += b[i][j];
            }
        }
    }

    for(int i = 1; i <= 2 * n; i++) {
        max_cost[i] = -1;
        done[i] = 0;
    }

    max_cost[1] = 0;
    int answer = 0;
    for(int i = 1; i <= 2 * n; i++) {
        int max_pos = 0;
        for(int j = 1; j <= 2 * n; j++) {
            if(!done[j] && (max_pos == 0 || max_cost[j] > max_cost[max_pos])) {
                max_pos = j;
            }
        }

        done[max_pos] = 1;
        if(max_cost[max_pos] > -1) {
            answer += max_cost[max_pos];
        }
        for(int j = 1; j <= 2 * n; j++) {
            if(!done[j] && g[max_pos][j]) {
                max_cost[j] = max(max_cost[j], g[max_pos][j]);
            }
        }
    }
    Erase();
    return total_cost - answer;
}

int main() {
    ios::sync_with_stdio(0);
    fin.tie(0);
    fout.tie(0);

    int T;
    fin >> T;
    for(int i = 1; i <= T; i++) {
        fout << "Case #" << i << ": " << test_case() << '\n';
    }

    return 0;
}