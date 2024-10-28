#include <fstream>
#include <algorithm>

using namespace std;

ifstream cin("angry.in");
ofstream cout("angry.out");

const int NMAX = 5e4;

int n, ind;
int a[NMAX + 1];
int prefix_min_r[NMAX + 1];
int sufix_min_r[NMAX + 1];

bool Check(int length) {
    int ind = 1;
    for(int i = 1; i <= n; i++) {
        while(a[i] - a[ind] > length) {
            ind++;
        }
        int need_r = max(prefix_min_r[ind], sufix_min_r[i]) + 1;
        if(need_r * 2 <= length) {
            return true;
        }
    }
    return false;
}

int main()
{
    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    sort(a + 1, a + n + 1);

    ind = 1;
    prefix_min_r[1] = 0;
    for(int i = 2; i <= n; i++) {
        prefix_min_r[i] = max(prefix_min_r[i - 1] + 1, a[i] - a[i - 1]);

        while(ind < i && prefix_min_r[ind + 1] + 1 <= prefix_min_r[i - 1]) {
            ind++;
        }

        if(prefix_min_r[ind] + 1 == prefix_min_r[i - 1]) {
            prefix_min_r[i] = min(prefix_min_r[i], max(prefix_min_r[ind] + 1, a[i] - a[ind]));
        }
    }

    ind = n;
    sufix_min_r[n] = 0;
    for(int i = n - 1; i >= 1; i--) {
        sufix_min_r[i] = max(sufix_min_r[i + 1] + 1, a[i + 1] - a[i]);

        while(ind > i && sufix_min_r[ind - 1] + 1 <= sufix_min_r[i + 1]) {
            ind--;
        }

        if(sufix_min_r[ind] + 1 == sufix_min_r[i + 1]) {
            sufix_min_r[i] = min(sufix_min_r[i], max(sufix_min_r[ind] + 1, a[ind] - a[i]));
        }
    }

    int left = 1, right = 2e9, answer = -1;
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
    cout << answer / 2 << (answer % 2 == 1 ? ".5" : ".0");

    return 0;
}
