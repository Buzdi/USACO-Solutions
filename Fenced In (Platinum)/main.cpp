#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define ll long long
#define ld long double

using namespace std;
using namespace __gnu_pbds;

ifstream fin("fencedin.in");
ofstream fout("fencedin.out");

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

const int NMAX = 25000;

int A, B, n, m, ind_lengths, i, j;
ll answer;
int a[NMAX + 2];
int b[NMAX + 2];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    fin >> A >> B >> n >> m;
    for(int i = 1; i <= n; i++) {
        fin >> a[i];
    }
    for(int i = 1; i <= m; i++) {
        fin >> b[i];
    }
    a[n + 1] = A;
    b[m + 1] = B;

    sort(a + 1, a + n + 1);
    sort(b + 1, b + m + 1);
    for(int i = n + 1; i >= 1; i--) {
        a[i] = a[i] - a[i - 1];
    }
    for(int i = m + 1; i >= 1; i--) {
        b[i] = b[i] - b[i - 1];
    }

    sort(a, a + n + 2);
    sort(b, b + m + 2);
    answer = (ll) a[1] * m + (ll) b[1] * n;
    i = 2, j = 2;
    while(i <= n + 1 && j <= m + 1) {
        if(a[i] < b[j]) {
            answer += (ll) a[i] * (m - (j - 1) + 1);
            i++;
        }
        else {
            answer += (ll) b[j] * (n - (i - 1) + 1);
            j++;
        }
    }
    fout << answer << '\n';

    return 0;
}