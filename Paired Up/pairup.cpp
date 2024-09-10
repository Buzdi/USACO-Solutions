#include <fstream>
#include <algorithm>

using namespace std;

ifstream cin("pairup.in");
ofstream cout("pairup.out");

const int NMAX = 1e5;

int n, L, R, answer;
pair<int, int> a[NMAX + 1];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> a[i].second >> a[i].first;
    }
    sort(a + 1, a + n + 1);

    L = 1, R = n;
    while(L < R) {
        answer = max(answer, a[L].first + a[R].first);
        if(a[L].second < a[R].second) {
            a[R].second -= a[L].second;
            L++;
        }
        else if(a[L].second > a[R].second) {
            a[L].second -= a[R].second;
            R--;
        }
        else {
            L++;
            R--;
        }
    }
    cout << answer << '\n';


    return 0;
}