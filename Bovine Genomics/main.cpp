#include <bits/stdc++.h>
//#define ll long long
#define cin fin
#define cout fout
#define ull unsigned long long

using namespace std;

ifstream fin("cownomics.in");
ofstream fout("cownomics.out");

const int NMAX = 500;
const int MOD = 1e9 + 7;
const int BASE = 31;

int n, m;
string a[2 * NMAX + 1];
ull pbase[NMAX + 1];
ull prefix_hash[2 * NMAX + 1][NMAX + 1];

ull get_hash(ull h[], int left, int right) {
    return h[right] - h[left - 1] * pbase[right - left + 1];
}

bool check(int len) {
    for(int right = len; right <= m; right++) {
        int left = right - len + 1;
        unordered_set<int> s;
        for(int i = 1; i <= n; i++) {
            s.insert(get_hash(prefix_hash[i], left, right));
        }
        bool ok = true;
        for(int i = n + 1; i <= 2 * n && ok; i++) {
            if(s.count(get_hash(prefix_hash[i], left, right))) {
                ok = false;
            }
        }
        if(ok) {
            return true;
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;
    for(int i = 1; i <= 2 * n; i++) {
        cin >> a[i];
    }

    pbase[0] = 1;
    for(int i = 1; i <= m; i++) {
        pbase[i] = pbase[i - 1] * BASE;
    }
    for(int i = 1; i <= 2 * n; i++) {
        for(int j = 1; j <= a[i].size(); j++) {
            prefix_hash[i][j] = prefix_hash[i][j - 1] * BASE + (a[i][j - 1] - 'A' + 1);
        }
    }

    int left = 1, right = m, answer = -1;
    while(left <= right) {
        int mid = (left + right) / 2;
        if(check(mid)) {
            answer = mid;
            right = mid - 1;
        }
        else {
            left = mid + 1;
        }
    }
    cout << answer << '\n';
    return 0;
}
