#include <fstream>
#include <vector>
#include <map>
#include <cassert>

using namespace std;

ifstream cin("lazy.in");
ofstream cout("lazy.out");

const int NMAX = 1e5;

struct AINT {
    int aint[8 * NMAX + 1] = {0};
    int lazy[8 * NMAX + 1] = {0};

    void Apply(int node, int left, int right, int parent_lazy) {
        if(parent_lazy == 0) {
            return;
        }
        aint[node] += parent_lazy;
        lazy[node] += parent_lazy;
    }

    void Push(int node, int left, int right) {
        int mid = (left + right) / 2;
        Apply(node * 2, left, mid, lazy[node]);
        Apply(node * 2 + 1, mid + 1, right, lazy[node]);
        lazy[node] = 0;
    }

    void Update(int node, int left, int right, int Uleft, int Uright, int value) {
        if(left > Uright || right < Uleft) {
            return;
        }
        if(left >= Uleft && right <= Uright) {
            Apply(node, left, right, value);
            return;
        }

        Push(node, left, right);
        int mid = (left + right) / 2;
        Update(node * 2, left, mid, Uleft, Uright, value);
        Update(node * 2 + 1, mid + 1, right, Uleft, Uright, value);
        aint[node] = max(aint[node * 2], aint[node * 2 + 1]);
    }
}aint;

struct Point {
    int x, y, v;
}points[NMAX + 1];

int n, k, max_x, max_y, l, answer, ID;
map<int, vector<int>> y_at_x;
map<int, int> mp;

void Update(int x, int sign) {
    if(y_at_x.find(x) == y_at_x.end()) {
        return;
    }

    for(int pos : y_at_x[x]) {
        int y = points[pos].y;
        int v = points[pos].v;

        int L = max(1, y - l + 1);
        int R = max(1, min(max_y - l + 1, y));
        L = mp[L];
        R = mp[R];
        aint.Update(1, 1, ID, L, R, sign * v);
    }
}

void Normalize() {
    for(int i = 1; i <= n; i++) {
        int y = points[i].y;
        int L = max(1, y - l + 1);
        int R = max(1, min(max_y - l + 1, y));
        mp[L] = 1;
        mp[R] = 1;
    }
    for(auto &x : mp) {
        x.second = ++ID;
    }
}

int main()
{
    cin >> n >> k;
    for(int i = 1; i <= n; i++) {
        int x, y, v;
        cin >> v >> x >> y;

        x = (x + 1) * 2;
        y = (y + 1) * 2;
        points[i] = {x, y, v};
    }

    for(int i = 1; i <= n; i++) {
        max_x = max(max_x, points[i].x);
    }

    for(int i = 1; i <= n; i++) {
        auto [x, y, v] = points[i];
        int new_x = x + y - 1;
        int new_y = max_x - x + y;
        points[i] = {new_x, new_y, v};
    }

    l = 4 * k + 1;
    for(int i = 1; i <= n; i++) {
        max_y = max(max_y, points[i].y);
        max_x = max(max_x, points[i].x);
    }
    Normalize();

    for(int i = 1; i <= n; i++) {
        y_at_x[points[i].x].push_back(i);
    }

    for(int x = 1; x <= max_x; x++) {
        Update(x, 1);
        if(x >= l) {
            answer = max(answer, aint.aint[1]);
            Update(x - l + 1, -1);
        }
    }
    answer = max(answer, aint.aint[1]);
    cout << answer << '\n';

    return 0;
}
