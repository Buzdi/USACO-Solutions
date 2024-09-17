#include <fstream>
#include <algorithm>
#include <vector>
#include <map>
#include <queue>
#define ll long long

using namespace std;

ifstream cin("cowdance.in");
ofstream cout("cowdance.out");

const int NMAX = 1e4;

int n, t_max;
int a[NMAX + 1];

bool Check(int k) {
    priority_queue<int, vector<int>, greater<int>> pq;
    for(int i = 1; i <= k; i++) {
        pq.push(a[i]);
    }
    for(int i = k + 1; i <= n; i++) {
        int mini = pq.top();
        pq.pop();

        pq.push(mini + a[i]);
    }

    while(!pq.empty()) {
        int curent = pq.top();
        pq.pop();
        if(curent > t_max) {
            return false;
        }
    }
    return true;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> n >> t_max;
	for(int i = 1; i <= n; i++) {
        cin >> a[i];
	}

    int left = 1, right = n, answer = -1;
    while(left <= right) {
        int mid = (left + right) / 2;
        if(Check(mid)) {
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
