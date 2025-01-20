#include <fstream>
#include <cassert>
#include <algorithm>
#include <tuple>

#define ll long long

using namespace std;

ifstream cin("walk.in");
ofstream cout("walk.out");

const int NMAX = 7500;
const int INF = 2e9 + 1e8;
const int A = 2019201913;
const int B = 2019201949;
const int MOD = 2019201997;

int n, k, last, ind;
int g[NMAX + 1][NMAX + 1];
int min_edge[NMAX + 1];
int apm[NMAX + 1];
char used[NMAX + 1];

int main()
{
    cin >> n >> k;
    for(int i = 1; i <= n; i++) {
        for(int j = i + 1; j <= n; j++) {
            g[i][j] = ((ll)A * i % MOD + (ll)B * j % MOD) % MOD;
            g[j][i] = g[i][j];
        }
    }

//    for(int i = 1; i <= n; i++) {
//        for(int j = i + 1; j <= n; j++) {
//            cout << i << ' ' << j << ' ' << g[i][j] << '\n';
//        }
//    }
//
//    for(int i = 1; i <= n; i++) {
//        for(int j = i + 1; j <= n; j++) {
//            if(j == i + 1 && i != 1 && g[i - 1][j - 1] <= g[i][j]) {
//                cout << "$ " << i << ' ' << j << ' ' << g[i][j] << '\n';
//            }
//            if(j != i + 1 && g[i][j - 1] <= g[i][j]) {
//                cout << "@ " << i << ' ' << j << ' ' << g[i][j] << '\n';
//            }
//        }
//    }

    for(int i = 1; i <= n; i++) {
        min_edge[i] = INF;
    }
    min_edge[1] = 0;
    for(int i = 1; i <= n; i++) {
        int pos_min = 0;
        for(int j = 1; j <= n; j++) {
            if(!used[j] && (pos_min == 0 || min_edge[j] < min_edge[pos_min])) {
                pos_min = j;
            }
        }

        used[pos_min] = 1;
        apm[++ind] = min_edge[pos_min];
        for(int j = 1; j <= n; j++) {
            if(pos_min != j && !used[j] && g[pos_min][j] < min_edge[j]) {
                min_edge[j] = g[pos_min][j];
            }
        }
    }

    sort(apm + 1, apm + ind + 1);
    cout << apm[ind - (k - 1) + 1];

    return 0;
}
