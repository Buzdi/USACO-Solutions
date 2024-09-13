#include <fstream>
#include <algorithm>
#include <vector>
#include <cassert>
#include <set>
#include <map>
#define ll long long
//#define int long long

using namespace std;

ifstream cin("snowboots.in");
ofstream cout("snowboots.out");

const int NMAX = 2e5;

struct Query {
    int snow, step, ind;
}queries[NMAX + 1];

int n, m, ID, value, max_length;
int a[NMAX + 1];
map<int, int> mp;
vector<int> pos[NMAX + 1];
int answer[NMAX + 1];
int T[NMAX + 1];
bool visited[NMAX + 1];

bool cmpQuery(const Query &a, const Query &b) {
    return a.snow > b.snow;
}

int GetRoot(int node) {
    int aux = node;
    while(T[node] > 0) {
        node = T[node];
    }
    int root = node;
    node = aux;
    while(node != root) {
        aux = T[node];
        T[node] = root;
        node = aux;
    }
    return root;
}

void Unite(int x, int y) {
    int root_x = GetRoot(x);
    int root_y = GetRoot(y);
    if(root_x == root_y) {
        return;
    }

    if(-T[root_x] < -T[root_y]) {
        swap(root_x, root_y);
    }
    T[root_x] += T[root_y];
    T[root_y] = root_x;
    max_length = max(max_length, -T[root_x]);
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> n >> m;
	for(int i = 1; i <= n; i++) {
        cin >> a[i];
	}
	for(int i = 1; i <= m; i++) {
        cin >> queries[i].snow >> queries[i].step;
        queries[i].ind = i;
	}

    for(int i = 1; i <= n; i++) {
        mp[a[i]] = 1;
    }
    for(int i = 1; i <= m; i++) {
        mp[queries[i].snow] = 1;
    }

    for(auto &x : mp) {
        x.second = ++ID;
    }

    for(int i = 1; i <= n; i++) {
        a[i] = mp[a[i]];
    }
    for(int i = 1; i <= m; i++) {
        queries[i].snow = mp[queries[i].snow];
    }
    sort(queries + 1, queries + m + 1, cmpQuery);

    for(int i = 1; i <= n; i++) {
        pos[a[i]].push_back(i);
    }

    for(int i = 1; i <= n; i++) {
        T[i] = -1;
    }

    value = ID;
    for(int i = 1; i <= m; i++) {
        while(value >= 1 && value > queries[i].snow) {
            for(int curent_pos : pos[value]) {
                visited[curent_pos] = 1;
                max_length = max(max_length, 1);
                if(curent_pos - 1 >= 1 && visited[curent_pos - 1]) {
                    Unite(curent_pos - 1, curent_pos);
                }
                if(curent_pos + 1 <= n && visited[curent_pos + 1]) {
                    Unite(curent_pos, curent_pos + 1);
                }
            }
            value--;
        }
        answer[queries[i].ind] = (max_length < queries[i].step);
    }

    for(int i = 1; i <= m; i++) {
        cout << answer[i] << '\n';
    }
	return 0;
}
