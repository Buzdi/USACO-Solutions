#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int NMAX = 2e5;

int n, ID;
ll curent_moves, answer;
int a[NMAX + 1];
int l[NMAX + 1], r[NMAX + 1];
ll diffs[NMAX + 1];
map<int, int> mp;

struct AIB {
    int n;
    int aib[NMAX + 1];

    void init(int n) {
        this->n = n;
        fill(aib + 1, aib + n + 1, 0);
    }

    void update(int pos, int value) {
        for(int i = pos; i <= n; i += i & (-i)) {
            aib[i] += value;
        }
    }

    int query(int pos) {
        int answer = 0;
        for(int i = pos; i >= 1; i -= i & (-i)) {
            answer += aib[i];
        }
        return answer;
    }
}aib;

void test_case() {
    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    for(int i = 1; i <= n; i++) {
        mp[a[i]] = 1;
    }
    for(auto& x : mp) {
        x.second = ++ID;
    }
    for(int i = 1; i <= n; i++) {
        a[i] = mp[a[i]];
    }

    aib.init(ID);
    for(int i = 1; i <= n; i++) {
        l[i] = aib.query(a[i] - 1);
        aib.update(a[i], 1);
    }

    aib.init(ID);
    for(int i = n; i >= 1; i--) {
        r[i] = aib.query(a[i] - 1);
        aib.update(a[i], 1);
    }

    for(int i = 1; i <= n; i++) {
        curent_moves += l[i];
        diffs[i] = r[i] - l[i];
    }
    sort(diffs + 1, diffs + n + 1);

    answer = curent_moves;
    for(int i = 1; i <= n; i++) {
        curent_moves += diffs[i];
        answer = min(answer, curent_moves);
    }
    cout << answer << '\n';

    curent_moves = answer = ID = 0;
    mp.clear();
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t;
    cin >> t;
    while(t--) {
        test_case();
    }
    return 0;
}
