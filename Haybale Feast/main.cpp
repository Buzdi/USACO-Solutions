#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
 
#define ll long long
#define ld long double

using namespace std;
using namespace __gnu_pbds;

ifstream fin("hayfeast.in");
ofstream fout("hayfeast.out");

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

const int NMAX = 1e5;

int n, R, answer;
ll sum_a, m;
int a[NMAX + 1];
int b[NMAX + 1];
multiset<int> s;

int main() {
    ios::sync_with_stdio(0);
    fin.tie(0);
    fout.tie(0);

    fin >> n >> m;
    for(int i = 1; i <= n; i++) {
        fin >> a[i] >> b[i];
    }

    R = 1;
    answer = 2e9;
    for(int i = 1; i <= n; i++) {
        while(R <= n && sum_a < m) {
            sum_a += a[R];
            s.insert(b[R]);
            R++;
        }

        if(sum_a >= m) {
            answer = min(answer, *prev(s.end()));
        }

        s.erase(s.find(b[i]));
        sum_a -= a[i];
    }
    fout << answer << '\n';

    return 0;
}