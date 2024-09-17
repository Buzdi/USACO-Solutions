#include <fstream>
#include <algorithm>
#include <cassert>
#include <queue>

using namespace std;

ifstream cin("meetings.in");
ofstream cout("meetings.out");

const int NMAX = 5e4;

struct Cow {
	int w, x, d;
	void read() {
		cin >> w >> x >> d;
	}
}cows[NMAX + 1];

int n, l, ind_left, ind_end, end_time, total_w, curent_w, answer;
pair<int, int> end_cows[NMAX + 1];
int to_right_x[NMAX + 1], ind_to_right;

bool cmpCows(const Cow &a, const Cow &b) {
	return a.x < b.x;
}

signed main() {
	cin >> n >> l;
	for(int i = 1; i <= n; i++) {
		cows[i].read();
	}
	sort(cows + 1, cows + n + 1, cmpCows);

	ind_left = 1;
	for(int i = 1; i <= n; i++) {
		if(cows[i].d == -1) {
			end_cows[++ind_end] = {cows[i].x, cows[ind_left].w};
			ind_left++;
		}
	}

	for(int i = 1; i <= n; i++) {
		if(cows[i].d == 1) {
			end_cows[++ind_end] = {l - cows[i].x, cows[ind_left].w};
			ind_left++;
		}
	}

	sort(end_cows + 1, end_cows + n + 1);
	for(int i = 1; i <= n; i++) {
		total_w += cows[i].w;
	}

	for(int i = 1; i <= n && !end_time; i++) {
		curent_w += end_cows[i].second;
		if(curent_w >= total_w / 2 + total_w % 2) {
			end_time = end_cows[i].first;
		}
	}
	
	for(int i = 1; i <= n; i++) {
		if(cows[i].d == 1) {
			to_right_x[++ind_to_right] = cows[i].x;
		}
		else {
			int pos = lower_bound(to_right_x + 1, to_right_x + ind_to_right + 1, cows[i].x - 2 * end_time) - to_right_x;
			if(pos != ind_to_right + 1) {
				answer += ind_to_right - pos + 1;
			}
		}
	}
	cout << answer << '\n';

	return 0;
}