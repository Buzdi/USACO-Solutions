#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#define ll long long

using namespace std;

const int NMAX = 2e5;

struct Query {
    int type;
    int time;
    int x;
    int cnt;

    void read() {
        cin >> type >> time >> x >> cnt;
    }
}queries[NMAX + 1];

int n, answer;
map<int, int> mp;

bool cmpQueries(const Query &a, const Query &b) {
    if(a.x - a.time < b.x - b.time) {
        return true;
    }
    if(a.x - a.time == b.x - b.time && a.type > b.type) {
        return true;
    }
    return false;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> n;
	for(int i = 1; i <= n; i++) {
        queries[i].read();
	}
	sort(queries + 1, queries + n + 1, cmpQueries);

    for(int i = 1; i <= n; i++) {
        auto [type, time, x, cnt] = queries[i];
        if(type == 2) {
            mp[x + time] += cnt;
        }
        else {
            while(cnt) {
                auto it = mp.lower_bound(x + time);
                if(it == mp.end()) {
                    cnt = 0;
                }
                else if(cnt >= it->second) {
                    cnt -= it->second;
                    answer += it->second;
                    mp.erase(it);
                }
                else {
                    it->second -= cnt;
                    answer += cnt;
                    cnt = 0;
                }
            }
        }
    }
    cout << answer << '\n';

	return 0;
}
