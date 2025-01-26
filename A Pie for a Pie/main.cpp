#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
 
#define ll long long
#define ld long double

using namespace std;
using namespace __gnu_pbds;

ifstream fin("piepie.in");
ofstream fout("piepie.out");

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

const int NMAX = 1e5;

int n, delta;
int a[2][NMAX + 1][2];
int d[2][NMAX + 1];
set<pair<int, int>> s[2];
queue<pair<int, int>> q;

int main() {
    ios::sync_with_stdio(0);
    fin.tie(0);
    fout.tie(0);

    fin >> n >> delta;
    for(int k = 0; k <= 1; k++) {
        for(int i = 1; i <= n; i++) {
            fin >> a[k][i][0] >> a[k][i][1];
        }
    }

    // Adding (TO DO)
    for(int k = 0; k <= 1; k++) {
        for(int i = 1; i <= n; i++) {
            if(!a[k][i][1 ^ k]) {
                d[k][i] = 1;
                q.push({k, i});
            }
            s[k].insert({a[1 ^ k][i][k], i});
        }
    }

    while(!q.empty()) {
        auto [k, i] = q.front();
        q.pop();

        auto it = s[k].lower_bound(make_pair(a[k][i][k] - delta, 0));
        while(it != s[k].end() && it->first <= a[k][i][k]) {
            if(!d[1 ^ k][it->second]) {
                d[1 ^ k][it->second] = d[k][i] + 1;
                q.push({1 ^ k, it->second});
            }
            it++;
            s[k].erase(prev(it));
        }
    }

    for(int i = 1; i <= n; i++) {
        fout << (d[0][i] == 0 ? -1 : d[0][i]) << '\n';
    }

    return 0;
}