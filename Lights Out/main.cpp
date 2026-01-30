#include <bits/stdc++.h>
#define ll long long

using namespace std;

ifstream fin("lightsout.in");
ofstream fout("lightsout.out");

const int NMAX = 500;
const int XMAX = 4e5;
const int EXIT = XMAX + 1;
const int ANGLE_PLUS = XMAX + 2;
const int ANGLE_MINUS = XMAX + 3;
const int BASE = 7326127;
const int MOD = 1e9 + 9;

struct Point {
    int x, y;
}points[NMAX + 1];

int n, ind, answer;
int sp[NMAX + 1];
int v[2 * NMAX + 10];
map<ll, int> mp;

int get_distance(Point p1, Point p2) {
    return abs(p1.x - p2.x) + abs(p1.y - p2.y);
}

ll cross_product(Point p1, Point p2, Point p3) {
    return (ll)(p2.x - p1.x) * (ll)(p3.y - p1.y) - (ll)(p3.x - p1.x) * (ll)(p2.y - p1.y);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    fin >> n;
    for(int i = 1; i <= n; i++) {
        fin >> points[i].x >> points[i].y;
    }
    points[n + 1] = points[1];

    for(int i = 1; i <= n; i++) {
        int iprev = (i == 1 ? n : i - 1);
        int inext = (i == n ? 1 : i + 1);
        ll cross = cross_product(points[iprev], points[i], points[inext]);
        int angle = (cross > 0 ? ANGLE_PLUS : ANGLE_MINUS);
        v[++ind] = angle;
        v[++ind] = get_distance(points[i], points[inext]);
    }

    for(int i = 1; i <= ind; i++) {
        ll h = 0;
        for(int j = i; j <= ind; j++) {
            h = ((ll) h * BASE + v[j]) % MOD;
            mp[h]++;
        }
    }

    for(int i = 2; i <= n + 1; i++) {
        sp[i] = sp[i - 1] + get_distance(points[i], points[i - 1]);
    }

    for(int i = 2; i <= n; i++) {
        int min_dist = min(sp[i], sp[n + 1] - sp[i]);
        ll h = v[2 * i - 1];
        int j = i;
        while(j <= n && mp[h] > 1) {
            h = ((ll) h * BASE + v[2 * j]) % MOD;
            h = ((ll) h * BASE + v[2 * j + 1]) % MOD;
            j++;
        }
        int min_dist_no = sp[j] - sp[i] + min(sp[j], sp[n + 1] - sp[j]);
        answer = max(answer, min_dist_no - min_dist);
    }
    fout << answer << '\n';
    return 0;
}
