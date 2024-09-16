#include <iostream>
#include <algorithm>
#include <cassert>
#include <vector>
#define ll long long
#define int long long

using namespace std;

const int NMAX = 3e5;

struct Patch {
    int p, t;
    void read() {
        cin >> p >> t;
    }
    bool operator < (const Patch &other) const {
        return p < other.p;
    }
}patches[NMAX + 1];

struct Event {
    int pos;
    ll value;
    bool operator < (const Event &other) const {
        if(pos < other.pos) {
            return true;
        }
        if(pos == other.pos && value < 0) {
            return true;
        }
        return false;
    }
};

int k, m, n, ind;
ll answer, sum_values;
int cows[NMAX + 1];
vector<Event> events;

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> k >> m >> n;
    for(int i = 1; i <= k; i++) {
        patches[i].read();
    }
    for(int i = 1; i <= m; i++) {
        cin >> cows[i];
    }
    sort(patches + 1, patches + k + 1);

    for(int i = 1; i <= k; i++) {
        int pos = lower_bound(cows + 1, cows + m + 1, patches[i].p) - cows;
        if(pos == m + 1) {
            assert(cows[m] < patches[i].p);
            int distance = patches[i].p - cows[m];
            events.push_back({patches[i].p - distance, patches[i].t});
            events.push_back({patches[i].p + distance, -patches[i].t});
        }
        else if(pos == 1) {
            assert(cows[1] > patches[i].p);
            int distance = cows[1] - patches[i].p;
            events.push_back({patches[i].p - distance, patches[i].t});
            events.push_back({patches[i].p + distance, -patches[i].t});
        }
        else {
            assert(cows[pos - 1] < patches[i].p && patches[i].p < cows[pos]);
            int min_distance = min(cows[pos] - patches[i].p, patches[i].p - cows[pos - 1]);
            events.push_back({patches[i].p - min_distance, patches[i].t});
            events.push_back({patches[i].p + min_distance, -patches[i].t});
        }
    }

    sort(events.begin(), events.end());
    for(auto event : events) {
        cout << event.pos << ' ' << event.value << '\n';
        sum_values += event.value;
        answer = max(answer, sum_values);
    }
    cout << answer << '\n';

    return 0;
}
