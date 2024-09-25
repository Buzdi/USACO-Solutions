#include <fstream>
#include <algorithm>
#include <cassert>
#include <cmath>
#include <vector>
#define ll long long

using namespace std;

ifstream cin("moocast.in");
ofstream cout("moocast.out");

const int NMAX = 200;

struct Point {
    int x, y, p;
    void read() {
        cin >> x >> y >> p;
    }
}points[NMAX + 1];

int n, answer;
bool visited[NMAX + 1];

int Square(int x) {
    return x * x;
}

int Distance(Point p1, Point p2) {
    return Square(p1.x - p2.x) + Square(p1.y - p2.y);
}

void DFS(int node) {
    visited[node] = 1;
    for (int next_node = 1; next_node <= n; next_node++) {
        if (next_node != node && !visited[next_node] && Distance(points[node], points[next_node]) <= points[node].p * points[node].p) {
            DFS(next_node);
        }
    }
}

int GetCows(int start) {
    for (int i = 1; i <= n; i++) {
        visited[i] = 0;
    }
    DFS(start);
    
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        cnt += visited[i];
    }
    return cnt;
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        points[i].read();
    }

    for (int i = 1; i <= n; i++) {
        answer = max(answer, GetCows(i));
    }
    cout << answer << '\n';

    return 0;
}
