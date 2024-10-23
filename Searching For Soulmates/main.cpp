#include <iostream>
#define ll long long
using namespace std;

ll Solve(ll a, ll b) {
    if(a == b) {
        return 0;
    }
    if(a > b) {
        bool is_odd = a % 2;
        return is_odd + 1 + Solve((a + is_odd) / 2, b);
    }
    bool is_odd = b % 2;
    return min(b - a, is_odd + 1 + Solve(a, (b - is_odd) / 2));
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T;
    cin >> T;
    while(T--) {
        ll a, b;
        cin >> a >> b;
        cout << Solve(a, b) << '\n';
    }


    return 0;
}
