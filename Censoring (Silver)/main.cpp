#include <bits/stdc++.h>
#define cin fin
#define cout fout
#define ll long long

using namespace std;

ifstream fin("censor.in");
ofstream fout("censor.out");

const int NMAX = 1e6;
const int BASE = 31;
const int MOD = 1e9 + 7;

int n, m, hash_s2;
string s1, s2;
char st[NMAX + 1];
int prefix_hash[NMAX + 1];
int pbase[NMAX + 1];

int get_hash(int left, int right) {
    return (prefix_hash[right] - (ll) prefix_hash[left - 1] * pbase[right - left + 1] % MOD + MOD) % MOD;
}

int main() {
    cin >> s1 >> s2;
    m = s2.size();

    for(char x : s2) {
        hash_s2 = ((ll) hash_s2 * BASE + (x - 'a' + 1)) % MOD;
    }

    pbase[0] = 1;
    for(char x : s1) {
        n++;
        st[n] = x;
        pbase[n] = (ll) pbase[n - 1] * BASE % MOD;
        prefix_hash[n] = ((ll) prefix_hash[n - 1] * BASE + (x - 'a' + 1)) % MOD;
        while(m <= n && get_hash(n - m + 1, n) == hash_s2) {
            n -= m;
        }
    }
    for(int i = 1; i <= n; i++) {
        cout << st[i];
    }
    return 0;
}
