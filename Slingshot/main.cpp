#include <fstream>
#include <map>
#include <array>
#include <algorithm>

#define ll long long

using namespace std;

ifstream cin("slingshot.in");
ofstream cout("slingshot.out");

const int NMAX = 1e5;
const int XMAX = 1e9 + 1;
const ll INF = 1e18;

struct AINT {
    ll aint[8 * NMAX + 1];
    void Initialize(int n) {
        for(int i = 1; i <= 4 * n; i++) {
            aint[i] = INF;
        }
    }

    void Update(int node, int left, int right, int pos, ll value) {
        if(left == right) {
            aint[node] = min(aint[node], value);
            return;
        }

        int mid = (left + right) / 2;
        if(pos <= mid) {
            Update(node * 2, left, mid, pos, value);
        }
        else {
            Update(node * 2 + 1, mid + 1, right, pos, value);
        }
        aint[node] = min(aint[node * 2], aint[node * 2 + 1]);
    }

    ll Query(int node, int left, int right, int Qleft, int Qright) {
        if(left > Qright || right < Qleft) {
            return INF;
        }
        if(left >= Qleft && right <= Qright) {
            return aint[node];
        }

        int mid = (left + right) / 2;
        return min(Query(node * 2, left, mid, Qleft, Qright), Query(node * 2 + 1, mid + 1, right, Qleft, Qright));
    }
}aint1, aint2;

int n, m, ind1, ind2, indq1, indq2, ID, inde;
array<int, 3> v1[NMAX + 1], v2[NMAX + 1];
array<int, 3> queries1[NMAX + 1], queries2[NMAX + 1];
ll answer[NMAX + 1];
array<int, 4> events[2 * NMAX + 1];

bool cmp1(array<int, 4>& a, array<int, 4>& b) {
    if(a[0] < b[0]) {
        return true;
    }
    if(a[0] == b[0] && a[1] < b[1]) {
        return true;
    }
    return false;
}

bool cmp2(array<int, 4>& a, array<int, 4>& b) {
    if(a[0] > b[0]) {
        return true;
    }
    if(a[0] == b[0] && a[1] < b[1]) {
        return true;
    }
    return false;
}

void Solve(array<int, 3> v[], int ind, array<int, 3> queries[], int indq) {
    map<int, int> mp;
    for(int i = 1; i <= ind; i++) {
        auto [a, b, d] = v[i];
//        mp[a] = 1;
        mp[b] = 1;
    }

    for(int i = 1; i <= indq; i++) {
        auto [pos1, pos2, posq] = queries[i];
//        mp[left] = 1;
        mp[pos2] = 1;
    }

    ID = 0;
    for(auto &x : mp) {
        x.second = ++ID;
    }

    inde = 0;
    for(int i = 1; i <= ind; i++) {
        auto [a, b, d] = v[i];
        events[++inde] = {a, 0, b, d};
    }
    for(int i = 1; i <= indq; i++) {
        auto [left, right, posq] = queries[i];
        events[++inde] = {left, 1, right, posq};
    }

    sort(events + 1, events + inde + 1, cmp1);
    aint1.Initialize(ID);
    aint2.Initialize(ID);
    for(int i = 1; i <= inde; i++) {
        if(events[i][1] == 0) {
            auto [a, t, b, d] = events[i];
            aint1.Update(1, 1, ID, mp[b], -a + b + d);
            aint2.Update(1, 1, ID, mp[b], -a - b + d);
        }
        else {
            auto [pos1, t, pos2, posq] = events[i];
            ll cost1 = aint1.Query(1, 1, ID, mp[pos2], ID);
            ll cost2 = aint2.Query(1, 1, ID, 1, mp[pos2]);
            answer[posq] = min(answer[posq], pos1 - pos2 + cost1);
            answer[posq] = min(answer[posq], pos1 + pos2 + cost2);
        }
    }

    sort(events + 1, events + inde + 1, cmp2);
    aint1.Initialize(ID);
    aint2.Initialize(ID);
    for(int i = 1; i <= inde; i++) {
        if(events[i][1] == 0) {
            auto [a, t, b, d] = events[i];
            aint1.Update(1, 1, ID, mp[b], a + b + d);
            aint2.Update(1, 1, ID, mp[b], a - b + d);
        }
        else {
            auto [pos1, t, pos2, posq] = events[i];
            ll cost1 = aint1.Query(1, 1, ID, mp[pos2], ID);
            ll cost2 = aint2.Query(1, 1, ID, 1, mp[pos2]);
            answer[posq] = min(answer[posq], -pos1 - pos2 + cost1);
            answer[posq] = min(answer[posq], -pos1 + pos2 + cost2);
        }
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;
    for(int i = 1; i <= n; i++) {
        int a, b, d;
        cin >> a >> b >> d;
        a++; b++;
        if(a <= b) {
            v1[++ind1] = {a, b, d};
        }
        else {
            a = XMAX - a + 1;
            b = XMAX - b + 1;
            v2[++ind2] = {a, b, d};
        }
    }

    for(int i = 1; i <= m; i++) {
        int left, right;
        cin >> left >> right;
        left++; right++;

        answer[i] = abs(left - right);
        if(left < right) {
            queries1[++indq1] = {left, right, i};
        }
        else {
            left = XMAX - left + 1;
            right = XMAX - right + 1;
            queries2[++indq2] = {left, right, i};
        }
    }

    Solve(v1, ind1, queries1, indq1);
    Solve(v2, ind2, queries2, indq2);
    for(int i = 1; i <= m; i++) {
        cout << answer[i] << '\n';
    }

    return 0;
}
