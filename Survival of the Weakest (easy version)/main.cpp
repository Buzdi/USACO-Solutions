#include <iostream>
#include <queue>
#include <algorithm>
#define ll long long

using namespace std;

const int NMAX = 3000;
const int MOD = 1e9 + 7;

struct Triplet {
    int sum, i1, i2;
    bool operator < (const Triplet &other) const {
        return other.sum < sum;
    }
};

int Power(int a, int b) {
    int rez = 1;
    while(b) {
        if(b % 2 == 1) {
            rez = (ll) rez * a % MOD;
        }
        a = (ll) a * a % MOD;
        b /= 2;
    }
    return rez;
}

int n, answer;
int a[NMAX + 1];
int b[NMAX + 1];

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    sort(a + 1, a + n + 1);

    for(int j = 1; j <= n - 1; j++) {
        int mini = a[1];
        for(int i = 2; i <= n - j + 1; i++) {
            mini = min(mini, a[i]);
        }
        for(int i = 1; i <= n - j + 1; i++) {
            a[i] -= mini;
        }

        answer = (answer + (ll) mini * Power(2, n - j) % MOD) % MOD;
        priority_queue<Triplet> pq;
        for(int i = 1; i < n - j + 1; i++) {
            pq.push({a[i] + a[i + 1], i, i + 1});
        }

        int ind = 1;
        while(ind <= n - j) {
            auto [sum, i1, i2] = pq.top();
            pq.pop();

            b[ind] = sum;
            ind++;

            if(i2 + 1 <= n - j + 1) {
                pq.push({a[i1] + a[i2 + 1], i1, i2 + 1});
            }
        }

        for(int i = 1; i <= n - j; i++) {
            a[i] = b[i];
        }
    }
    cout << (a[1] + answer) % MOD << '\n';

    return 0;
}
