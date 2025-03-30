#include <fstream>
#include <algorithm>

using namespace std;

ifstream cin("balancing.in");
ofstream cout("balancing.out");

const int NMAX = 1e5;
const int XMAX = 1e6;

struct AINT {
    int aint[4 * XMAX + 1] = {0};

    int operator[] (int pos) {
        return aint[pos];
    }

    void Update(int node, int left, int right, int pos, int value) {
        if(left == right) {
            aint[node] += value;
            return;
        }

        int mid = (left + right) / 2;
        if(pos <= mid) {
            Update(node * 2, left, mid, pos, value);
        }
        else {
            Update(node * 2 + 1, mid + 1, right, pos, value);
        }
        aint[node] = aint[node * 2] + aint[node * 2 + 1];
    }
}aint[2];

int n, i, answer;
pair<int, int> points[NMAX + 1];

int BS(int node = 1, int left = 1, int right = XMAX, int up_left = 0, int up_right = 0, int down_left = 0, int down_right = 0) {
    if(left == right) {
        /// Do something
        if(max(up_left + aint[0][node], up_right + aint[1][node]) < max(down_left + aint[0][node], down_right + aint[1][node])) {
            up_left += aint[0][node];
            up_right += aint[1][node];
        }
        else {
            down_left += aint[0][node];
            down_right += aint[1][node];
        }
        return max({up_left, up_right, down_left, down_right});
    }

    int mid = (left + right) / 2;
    if(max(up_left + aint[0][node * 2], up_right + aint[1][node * 2]) < max(down_left + aint[0][node * 2 + 1], down_right + aint[1][node * 2 + 1])) {
        return BS(node * 2 + 1, mid + 1, right, up_left + aint[0][node * 2], up_right + aint[1][node * 2], down_left, down_right);
    }
    return BS(node * 2, left, mid, up_left, up_right, down_left + aint[0][node * 2 + 1], down_right + aint[1][node * 2 + 1]);
}

int main()
{
    cin >> n;
    for(int i = 1; i <= n; i++) {
        int x, y;
        cin >> x >> y;
        points[i] = {x, y};
    }
    sort(points + 1, points + n + 1);

    for(int i = 1; i <= n; i++) {
        aint[1].Update(1, 1, XMAX, points[i].second, 1);
    }

    i = 1;
    answer = n;
    while(i <= n) {
        int j = i;
        while(j <= n && points[i].first == points[j].first) {
            aint[0].Update(1, 1, XMAX, points[j].second, 1);
            aint[1].Update(1, 1, XMAX, points[j].second, -1);
            j++;
        }
        answer = min(answer, BS());
        i = j;
    }
    cout << answer << '\n';

    return 0;
}
