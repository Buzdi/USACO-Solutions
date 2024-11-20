#include <fstream>
#include <algorithm>
#define ll long long

using namespace std;

ifstream cin("radio.in");
ofstream cout("radio.out");

const int NMAX = 1000;
const int INF = 2e9;

struct Point {
    int x, y;
    void Read() {
        cin >> x >> y;
    }
};

int n, m;
int dp[NMAX + 1][NMAX + 1];
Point points_a[NMAX + 1], points_b[NMAX + 1];

int Square(int x) {
    return x * x;
}

int Distance(Point p1, Point p2) {
    return Square(p1.x - p2.x) + Square(p1.y - p2.y);
}

void GetDirection(char x, int &dx, int &dy) {
    if(x == 'N') {
        dx = 0;
        dy = 1;
    }
    if(x == 'E') {
        dx = 1;
        dy = 0;
    }
    if(x == 'S') {
        dx = 0;
        dy = -1;
    }
    if(x == 'W') {
        dx = -1;
        dy = 0;
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;
    points_a[0].Read();
    points_b[0].Read();

    for(int i = 1; i <= n; i++) {
        char x;
        cin >> x;
        int dx, dy;
        GetDirection(x, dx, dy);
        points_a[i].x = points_a[i - 1].x + dx;
        points_a[i].y = points_a[i - 1].y + dy;
    }

    for(int i = 1; i <= m; i++) {
        char x;
        cin >> x;
        int dx, dy;
        GetDirection(x, dx, dy);
        points_b[i].x = points_b[i - 1].x + dx;
        points_b[i].y = points_b[i - 1].y + dy;
    }

    for(int i = 0; i <= n; i++) {
        for(int j = 0; j <= m; j++) {
            dp[i][j] = INF;
        }
    }
    dp[0][0] = 0;

    for(int i = 0; i <= n; i++) {
        for(int j = 0; j <= m; j++) {
            int curent_distance = Distance(points_a[i], points_b[j]);
            if(i - 1 >= 0 && dp[i - 1][j] != INF) {
                dp[i][j] = min(dp[i][j], dp[i - 1][j] + curent_distance);
            }
            if(j - 1 >= 0 && dp[i][j - 1] != INF) {
                dp[i][j] = min(dp[i][j], dp[i][j - 1] + curent_distance);
            }
            if(i - 1 >= 0 && j - 1 >= 0 && dp[i - 1][j - 1] != INF) {
                dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + curent_distance);
            }
        }
    }
    cout << dp[n][m];

    return 0;
}
