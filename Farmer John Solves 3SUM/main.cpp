#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#define ll long long

using namespace std;
using namespace __gnu_pbds;

ifstream fin("threesum.in");
ofstream fout("threesum.out");

const int NMAX = 5000 + 5;

struct chash {
	// any random-ish large odd number will do
	const uint64_t C = uint64_t(2e18 * M_PI) + 71;
	// random 32-bit number
	const uint32_t RANDOM = chrono::steady_clock::now().time_since_epoch().count();
	size_t operator()(uint64_t x) const {
		return __builtin_bswap64((x ^ RANDOM) * C);
	}
};

int n, q;
int a[NMAX + 1];
ll answer[NMAX + 1][NMAX + 1];

int main()
{
    fin >> n >> q;
    for(int i = 1; i <= n; i++) {
        fin >> a[i];
    }

    for(int i = 1; i <= n; i++) {
        gp_hash_table<int, int, chash> mp({}, {}, {}, {}, {1 << 13});
        for(int j = i + 1; j <= n; j++) {
            answer[i][j] = mp[-a[i] - a[j]];
            mp[a[j]]++;
        }
    }

    for(int i = n; i >= 1; i--) {
        for(int j = 1; j <= n; j++) {
            answer[i][j] += answer[i + 1][j] + answer[i][j - 1] - answer[i + 1][j - 1];
        }
    }

    while(q--) {
        int x, y;
        fin >> x >> y;
        fout << answer[x][y] << '\n';
    }
    return 0;
}
