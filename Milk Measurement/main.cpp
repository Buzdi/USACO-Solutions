#include <fstream>
#include <algorithm>
#include <vector>
#include <cassert>
#include <set>
#include <map>
#define ll long long

using namespace std;

ifstream cin("measurement.in");
ofstream cout("measurement.out");

const int NMAX = 1e5;
const int INF = 1e9;

struct Event {
    int t, ID, add_value;
    void Read() {
        cin >> t >> ID >> add_value;
    }
}events[NMAX + 1];

int n, G, changes;
pair<int, int> last;
map<int, int> milk;
map<int, int> display;

bool cmpEvents(const Event &a, const Event &b) {
    return a.t < b.t;
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> n >> G;
    for(int i = 1; i <= n; i++) {
        events[i].Read();
    }
    sort(events + 1, events + n + 1, cmpEvents);

    display[G] = INF;
    for(int i = 1; i <= n; i++) {
        milk[events[i].ID] = G;
    }

    for(int i = 1; i <= n; i++) {
        int ID = events[i].ID;
        int add_value = events[i].add_value;

        int value = milk[ID];
        bool was_top = (value == display.rbegin()->first);
        int previous_count = display[value];
        display[value]--;
        if(display[value] == 0) {
            display.erase(value);
        }

        value += add_value;
        milk[ID] = value;
        display[value]++;

        bool is_top = (value == display.rbegin()->first);
        int curent_count = display[value];
        if((was_top && (!is_top || curent_count != previous_count)) || (!was_top && is_top)) {
            changes++;
        }
    }
    cout << changes << '\n';
	return 0;
}
