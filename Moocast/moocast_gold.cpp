#include <fstream>
#include <algorithm>
#include <cassert>
#include <cmath>
#include <vector>
#define ll long long

using namespace std;

ifstream cin("moocast.in");
ofstream cout("moocast.out");

const int NMAX = 1000;

struct Point {
    int x, y, p;
    void read() {
        cin >> x >> y;
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

void DFS(int node, int X) {
    visited[node] = 1;
    for (int next_node = 1; next_node <= n; next_node++) {
        if (next_node != node && !visited[next_node] && Distance(points[node], points[next_node]) <= X) {
            DFS(next_node, X);
        }
    }
}

bool Check(int X) {
    for (int i = 1; i <= n; i++) {
        visited[i] = 0;
    }
    DFS(1, X);
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            return false;
        }
    }
    return true;
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
    
    int left = 1, right = 1e9, answer = -1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (Check(mid)) {
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
