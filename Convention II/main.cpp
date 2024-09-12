#include <fstream>
#include <algorithm>
#include <vector>
#include <queue>
#define ll long long

using namespace std;

ifstream cin("convention2.in");
ofstream cout("convention2.out");

const int NMAX = 1e5;

struct Cow {
    int start_time, duration_time, index;
    void Read() {
        cin >> start_time >> duration_time;
    }
    bool operator < (const Cow &other) const {
        return other.index < index;
    }
}cows[NMAX + 1];

int n, curent_time, ind, answer;
priority_queue<Cow> pq;

bool cmpCows(const Cow &a, const Cow &b) {
    return a.start_time < b.start_time;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

    cin >> n;
    for(int i = 1; i <= n; i++) {
        cows[i].Read();
        cows[i].index = i;
    }
    sort(cows + 1, cows + n + 1, cmpCows);

    ind = 1;
    while(ind <= n) {
        curent_time = cows[ind].start_time;
        while(ind <= n && cows[ind].start_time == curent_time) {
            pq.push(cows[ind]);
            ind++;
        }

        while(!pq.empty()) {
            Cow curent_cow = pq.top();
            pq.pop();

            answer = max(answer, curent_time - curent_cow.start_time);
            curent_time += curent_cow.duration_time;
            while(ind <= n && cows[ind].start_time <= curent_time) {
                pq.push(cows[ind]);
                ind++;
            }
        }
    }
    cout << answer << '\n';

	return 0;
}
