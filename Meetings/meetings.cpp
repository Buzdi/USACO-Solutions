#include <fstream>
#include <algorithm>
#include <cassert>
#define int long long
using namespace std;

ifstream cin("meetings.in");
ofstream cout("meetings.out");

const int NMAX = 5e4;

struct Cow {
	int w, x, d;
	void Read() {
		cin >> w >> x >> d;
	}
}cows[NMAX + 1];

int n, L, total_w, ended_w, meetings, ind_left, ind_right;
pair<int, int> distances_to_end[NMAX + 1];

bool cmp_cows(const Cow& a, const Cow& b) {
	return a.x < b.x;
}

signed main() {
	cin >> n >> L;
	for(int i = 1; i <= n; i++) {
		cows[i].Read();
	}
	sort(cows + 1, cows + n + 1, cmp_cows);

	for(int i = 1; i <= n; i++) {
		total_w += cows[i].w;
	}

	for(int i = 1; i <= n; i++) {
		if(cows[i].d == -1) {
			distances_to_end[i] = {cows[i].x, -i};
		}
		else {
			distances_to_end[i] = {L - cows[i].x, i};
		}
	}
	sort(distances_to_end + 1, distances_to_end + n + 1);

	ind_left = 1, ind_right = n;
	for(int i = 1; i <= n && ended_w < total_w / 2 + total_w % 2; i++) {
		auto [distance, pos] = distances_to_end[i];
		if(pos < 0) {
			pos = -pos;

			meetings += pos - ind_left;
			ended_w += cows[ind_left].w;
			ind_left++;
			cows[pos].d = 1;
		}
		else {

			meetings += ind_right - pos;
			ended_w += cows[ind_right].w;
			ind_right--;
			cows[pos].d = -1;
		}
	}
	assert(meetings % 2 == 0);
	cout << meetings << '\n';

	return 0;
}