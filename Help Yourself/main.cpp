#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define ll long long
#define ld long double

using namespace std;
using namespace __gnu_pbds;

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

ifstream fin("help.in");
ofstream fout("help.out");

const int NMAX = 1e5;
const int MOD = 1e9 + 7;

struct AIB {
    int n;
    int aib[2 * NMAX + 1];
    
    void Initialize(int n) {
        this->n = n;
        for(int i = 1; i <= n; i++) {
            aib[i] = 0;
        }
    }

    void Update(int pos, int value) {
        for(int i = pos; i <= n; i += i & (-i)) {
            aib[i] += value;
        }
    }

    int Query(int pos) {
        int answer = 0;
        for(int i = pos; i >= 1; i -= i & (-i)) {
            answer += aib[i];
        }
        return answer;
    }
}aib;

int n, answer;
int L[NMAX + 1];
int R[NMAX + 1];
int sp[2 * NMAX + 1];
pair<int, int> intervals[NMAX + 1];
int full_inside[NMAX + 1];

int Power(int a, int b) {
    int rez = 1;
    while(b) {
        if(b % 2 == 1) {
            rez = (ll)rez * a % MOD;
        }
        a = (ll)a * a % MOD;
        b /= 2;
    }
    return rez;
}

void PrecomputeSP() {
    for(int i = 1; i <= n; i++) {
        sp[intervals[i].first] = 1;
        sp[intervals[i].second] = 1;
    }
    for(int i = 1; i <= 2 * n; i++) {
        sp[i] += sp[i - 1];
    }
}

void PrecomputeFullInside() {
    aib.Initialize(2 * n);
    for(int i = n; i >= 1; i--) {
        full_inside[i] = aib.Query(intervals[i].second);
        aib.Update(intervals[i].second, 1);
    }
}

int GetGreater(int value) {
    int pos = lower_bound(L + 1, L + n + 1, value + 1) - L;
    return n - pos + 1;
}

int GetSmaller(int value) {
    int pos = lower_bound(R + 1, R + n + 1, value) - R - 1;
    return pos;
}

int main() {
    ios::sync_with_stdio(0);
    fin.tie(0);
    fout.tie(0);

    fin >> n;
    for(int i = 1; i <= n; i++) {
        fin >> L[i] >> R[i];
    }
    for(int i = 1; i <= n; i++) {
        intervals[i] = {L[i], R[i]};
    }
    sort(L + 1, L + n + 1);
    sort(R + 1, R + n + 1);
    sort(intervals + 1, intervals + n + 1);

    PrecomputeSP();
    PrecomputeFullInside();
    aib.Initialize(2 * n);
    for(int i = 1; i <= n; i++) {
        auto [L, R] = intervals[i];
        int inside = sp[R] - sp[L - 1] - full_inside[i] - 2;
        int outside = GetGreater(R) + GetSmaller(L);
        inside -= aib.Query(R) - aib.Query(L - 1);
        answer = (answer + (ll) Power(2, inside) * Power(2, outside) % MOD) % MOD;
        aib.Update(R, 1);
    }
    fout << answer << '\n';

    return 0;
}