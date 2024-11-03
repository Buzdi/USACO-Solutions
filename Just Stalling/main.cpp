#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;

const int NMAX = 20;

int n;
int a[NMAX + 1];
int b[NMAX + 1];
ll answer;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int i = 1; i <= n; i++) {
        cin >> b[i];
    }
    sort(a + 1, a + n + 1);
    sort(b + 1, b + n + 1);

    int R = n;
    answer = 1;
    for(int i = n; i >= 1; i--) {
        while(R >= 1 && a[i] <= b[R]) {
            R--;
        }
        answer *= n - R - (n - i);
    }
    cout << answer << '\n';
    return 0;
}
