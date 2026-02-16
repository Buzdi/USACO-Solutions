#include <bits/stdc++.h>
#define ll long long

using namespace std;

ifstream fin("nondec.in");
ofstream fout("nondec.out");

const int NMAX = 5e4;
const int KMAX = 20;
const int MOD = 1e9 + 7;
const int QMAX = 2e5;

struct Query {
    int left, right;
}queries[QMAX + 1];

int n, k, q;
int a[NMAX + 1];
vector<int> pos_queries;
int answer[QMAX + 1];
int dp_left[NMAX + 1][KMAX + 1][KMAX + 1];
int dp_right[NMAX + 1][KMAX + 1][KMAX + 1];
int sp_left[NMAX + 1][KMAX + 1];
int sp_right[NMAX + 1][KMAX + 1];

void add_mod(int& x, int y) {
    x += y;
    if(x >= MOD) {
        x -= MOD;
    }
}

void solve(int left, int right, vector<int>& pos_queries) {
    if(pos_queries.empty()) {
        return;
    }

    if(left == right) {
        for(int ind : pos_queries) {
            answer[ind] = 2;
        }
        return;
    }

    int mid = (left + right) / 2;
    vector<int> left_queries, right_queries, cross_queries;

    for(int ind : pos_queries) {
        auto query = queries[ind];
        if(query.left <= mid && mid + 1 <= query.right) {
            cross_queries.push_back(ind);
        }
        else if(query.right <= mid) {
            left_queries.push_back(ind);
        }
        else {
            right_queries.push_back(ind);
        }
    }

    if(!cross_queries.empty()) {
        /// Facem dp left

        for(int x = 1; x <= k; x++) {
            for(int y = 1; y <= k; y++) {
                dp_left[mid][x][y] = 0;
            }
        }
        dp_left[mid][a[mid]][a[mid]] = 1;

        for(int i = mid - 1; i >= left; i--) {
            for(int x = 1; x <= k; x++) {
                for(int y = x; y <= k; y++) {
                    dp_left[i][x][y] = dp_left[i + 1][x][y];
                }
            }

            add_mod(dp_left[i][a[i]][a[i]], 1); /// Creez subsir independent

            for(int x = a[i]; x <= k; x++) {
                for(int y = x; y <= k; y++) {
                    /// Imi dau append la toate subsirurile care incep cu o valoare >= decat mine si se termina intr-o oarecare valoare
                    add_mod(dp_left[i][a[i]][y], dp_left[i + 1][x][y]);
                }
            }
        }

        for(int i = mid; i >= left; i--) {
            for(int y = 1; y <= k; y++) {
                sp_left[i][y] = sp_left[i][y - 1];
                for(int x = 1; x <= y; x++) {
                    add_mod(sp_left[i][y], dp_left[i][x][y]);
                }
            }
        }

        /// Facem dp right

        for(int x = 1; x <= k; x++) {
            for(int y = 1; y <= k; y++) {
                dp_right[mid + 1][x][y] = 0;
            }
        }
        dp_right[mid + 1][a[mid + 1]][a[mid + 1]] = 1;

        for(int i = mid + 2; i <= right; i++) {
            for(int x = 1; x <= k; x++) {
                for(int y = 1; y <= k; y++) {
                    dp_right[i][x][y] = dp_right[i - 1][x][y];
                }
            }

            add_mod(dp_right[i][a[i]][a[i]], 1);

            for(int x = 1; x <= a[i]; x++) {
                for(int y = x; y <= a[i]; y++) {
                    add_mod(dp_right[i][x][a[i]], dp_right[i - 1][x][y]);
                }
            }
        }

        for(int i = mid + 1; i <= right; i++) {
            for(int x = 1; x <= k; x++) {
                sp_right[i][x] = 0;
                for(int y = x; y <= k; y++) {
                    add_mod(sp_right[i][x], dp_right[i][x][y]);
                }
            }
        }

        for(int ind : cross_queries) {
            auto query = queries[ind];
            for(int x = 1; x <= k; x++) {
                add_mod(answer[ind], (ll) (sp_left[query.left][x] + 1) * sp_right[query.right][x] % MOD);
            }
            add_mod(answer[ind], sp_left[query.left][k] + 1);
        }
    }

    solve(left, mid, left_queries);
    solve(mid + 1, right, right_queries);
}

int main()
{
    fin >> n >> k;
    for(int i = 1; i <= n; i++) {
        fin >> a[i];
    }

    fin >> q;
    for(int i = 1; i <= q; i++) {
        int left, right;
        fin >> left >> right;
        queries[i] = {left, right};
    }

    for(int i = 1; i <= q; i++) {
        pos_queries.push_back(i);
    }

    solve(1, n, pos_queries);
    for(int i = 1; i <= q; i++) {
        fout << answer[i] << '\n';
    }
    return 0;
}
