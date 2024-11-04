#include <fstream>
#include <algorithm>
#include <map>

using namespace std;

ifstream cin("cowpatibility.in");
ofstream cout("cowpatibility.out");

struct Array {
    int a[5] = {0};

    Array(int *v) {
        for(int i = 0; i < 5; i++) {
            a[i] = v[i];
        }
    }

    bool operator < (const Array &other) const {
        for(int i = 0; i < 5; i++) {
            if(a[i] < other.a[i]) {
                return true;
            }
            if(a[i] > other.a[i]) {
                return false;
            }
        }
        return false;
    }
};

int n, total_answer;
int v[5];
map<Array, int> mp;

int main()
{
    cin >> n;
    for(int i = 1; i <= n; i++) {
        for(int j = 0; j < 5; j++) {
            cin >> v[j];
        }

        int answer = 0;
        for(int mask = 1; mask < (1 << 5); mask++) {
            int ind = 0;
            int a[5] = {0};
            for(int j = 0; j < 5; j++) {
                if((mask >> j) & 1) {
                    a[ind++] = v[j];
                }
            }

            sort(a, a + ind);
            int sz = __builtin_popcount(mask);
            answer += (sz % 2 == 1 ? 1 : -1) * mp[a];
        }

        for(int mask = 1; mask < (1 << 5); mask++) {
            int ind = 0;
            int a[5] = {0};
            for(int j = 0; j < 5; j++) {
                if((mask >> j) & 1) {
                    a[ind++] = v[j];
                }
            }
            sort(a, a + ind);
            mp[a]++;
        }
        total_answer += (i - 1 - answer);
    }
    cout << total_answer << '\n';

    return 0;
}
