#include <bits/stdc++.h>
#define ll long long

using namespace std;

ifstream fin("triangles.in");
ofstream fout("triangles.out");

const int NMAX = 300;

int n;
bitset<NMAX + 1> bs[NMAX + 1][NMAX + 1];
int answer[NMAX + 1];

struct Point {
    int x, y;
}points[NMAX + 1];

ll cross_product(Point p1, Point p2, Point p3) {
    return (ll)(p2.x - p1.x) * (p3.y - p1.y) - (ll)(p3.x - p1.x) * (p2.y - p1.y);
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    fin >> n;
    for(int i = 1; i <= n; i++) {
        fin >> points[i].x >> points[i].y;
    }

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            for(int k = 1; k <= n; k++) {
                if(i != j && j != k && cross_product(points[i], points[j], points[k]) > 0) {
                    bs[i][j].set(k);
                }
            }
        }
    }

    for(int i = 1; i <= n; i++) {
        for(int j = i + 1; j <= n; j++) {
            for(int k = j + 1; k <= n; k++) {
                int t[3] = {i, j, k};
                if(cross_product(points[t[0]], points[t[1]], points[t[2]]) < 0) {
                    swap(t[1], t[2]);
                }
                int v = (bs[t[0]][t[1]] & bs[t[1]][t[2]] & bs[t[2]][t[0]]).count();
                answer[v]++;
            }
        }
    }

    for(int i = 0; i <= n - 3; i++) {
        fout << answer[i] << '\n';
    }
    return 0;
}
