#include <fstream>
#include <algorithm>

using namespace std;

ifstream cin("diamond.in");
ofstream cout("diamond.out");

const int NMAX = 1e5;

int n, k, L, R, answer;
int a[NMAX + 1];
int best_prefix[NMAX + 1];
int best_sufix[NMAX + 1];

int main()
{
    cin >> n >> k;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    sort(a + 1, a + n + 1);

    L = 1;
    for(int i = 1; i <= n; i++) {
        while(a[i] - a[L] > k) {
            L++;
        }
        best_prefix[i] = i - L + 1;
    }

    R = n;
    for(int i = n; i >= 1; i--) {
        while(a[R] - a[i] > k) {
            R--;
        }
        best_sufix[i] = R - i + 1;
    }

    for(int i = 2; i <= n; i++) {
        best_prefix[i] = max(best_prefix[i], best_prefix[i - 1]);
    }
    for(int i = n - 1; i >= 1; i--) {
        best_sufix[i] = max(best_sufix[i], best_sufix[i + 1]);
    }

    for(int i = 1; i <= n - 1; i++) {
        answer = max(answer, best_prefix[i] + best_sufix[i + 1]);
    }
    cout << answer << '\n';

    return 0;
}
