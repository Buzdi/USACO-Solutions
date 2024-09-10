#include <fstream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

ifstream cin("sort.in");
ofstream cout("sort.out");

const int NMAX = 1e5;

int n, ID, answer;
int a[NMAX + 1];
map<int, int> mp;
int aib[NMAX + 1];

void Update(int pos, int value) {
    for(int i = pos; i <= ID; i += i & (-i)) {
        aib[i] += value;
    }
}

int Query(int pos) {
    int answer = 0;
    for(int i = pos; i >= 1; i -= i & (-i)) {
        answer += aib[i];
    }
    return answer;
}

int main()
{
    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    for(int i = 1; i <= n; i++) {
        mp[a[i]] = 1;
    }
    for(auto &x : mp) {
        x.second = ++ID;
    }
    for(int i = 1; i <= n; i++) {
        a[i] = mp[a[i]];
    }

    for(int i = 1; i <= n; i++) {
        answer = max(answer, i - 1 - Query(a[i]));
        Update(a[i], 1);
    }
    cout << answer + 1 << '\n';

    return 0;
}
