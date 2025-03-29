#include <fstream>
#include <map>
#include <algorithm>
#define ll long long

using namespace std;

ifstream cin("boards.in");
ofstream cout("boards.out");

const int PMAX = 1e5;
const int INF = 2e9;

struct Event {
    int x, y, type, pos;
    bool operator < (const Event &other) const {
        if(x < other.x) {
            return true;
        }
        if(x == other.x && y < other.y) {
            return true;
        }
        return false;
    }
}events[2 * PMAX + 1];

struct AINT {
    int aint[8 * PMAX + 1];

    void Initialize(int n) {
        for(int i = 1; i <= 4 * n; i++) {
            aint[i] = INF;
        }
    }

    void Update(int node, int left, int right, int pos, int value) {
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

    int Query(int node, int left, int right, int Qleft, int Qright) {
        if(left > Qright || right < Qleft) {
            return INF;
        }
        if(left >= Qleft && right <= Qright) {
            return aint[node];
        }

        int mid = (left + right) / 2;
        return min(Query(node * 2, left, mid, Qleft, Qright), Query(node * 2 + 1, mid + 1, right, Qleft, Qright));
    }
}aint;

int n, p, ID, ind, total_answer;
int answer[PMAX + 1];
map<int, int> mp;

int main()
{
    cin >> n >> p;
    mp[0] = 1;
    for(int i = 1; i <= p; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;

        y1++;
        y2++;

        mp[y1] = 1;
        mp[y2] = 1;

        events[++ind] = {x1, y1, 1, i};
        events[++ind] = {x2, y2, 2, i};
    }
    sort(events + 1, events + ind + 1);
    for(auto &x : mp) {
        x.second = ++ID;
    }

    aint.Initialize(ID);
    aint.Update(1, 1, ID, mp[0], 0);
    for(int i = 1; i <= ind; i++) {
        auto [x, y, type, pos] = events[i];
        if(type == 1) {
            answer[pos] = x + y + aint.Query(1, 1, ID, 1, mp[y]);
        }
        else {
            aint.Update(1, 1, ID, mp[y], answer[pos] - x - y);
        }
    }
    cout << aint.aint[1] + 2 * n;

    return 0;
}
