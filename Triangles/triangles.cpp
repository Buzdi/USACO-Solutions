#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#define ll long long

using namespace std;
// using namespace __gnu_pbds;

ifstream cin("triangles.in");
ofstream cout("triangles.out");

const int NMAX = 1e5;
const int VMAX = 1e4;
const int MOD = 1e9 + 7;

int n, answer;
vector<int> x_axis[2 * VMAX + 1];
int cnt_y[2 * VMAX + 1];
int sum_y[2 * VMAX + 1];

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    for(int i = 1; i <= n; i++) {
        int x, y;
        cin >> x >> y;
//        cout << x << ' ' << y << '\n';
        x += VMAX; y += VMAX;
//        cout << x << ' ' << y << '\n';
        x_axis[y].push_back(x);
    }

    for(int y = 0; y <= 2 * VMAX; y++) {
        int sum = 0;
        for(int x : x_axis[y]) {
            sum = (sum + x) % MOD;
        }

        int sum_x_left = 0;
        for(int i = 0; i < (int) x_axis[y].size(); i++) {
            int x = x_axis[y][i];
            int sum_x_right = ((sum - sum_x_left + MOD) % MOD - x + MOD) % MOD;
            int sum_y_down = sum_y[x];
            int cnt_x_left = i;
            int cnt_x_right = x_axis[y].size() - i - 1;
            int cnt_y_down = cnt_y[x];

//            cout << x << ' ' << y << ' ' << sum_x_left << ' ' << sum_x_right << ' ' << sum_y_down << ' ';

            /// Right-Down
            if(cnt_y_down && cnt_x_right) {
                answer = (answer + (ll) y * sum_x_right % MOD * cnt_y_down % MOD) % MOD;
                answer = (answer - (ll) sum_x_right * sum_y_down % MOD + MOD) % MOD;
                answer = (answer - (ll) x * y % MOD * cnt_x_right % MOD * cnt_y_down % MOD + MOD) % MOD;
                answer = (answer + (ll) x * sum_y_down % MOD * cnt_x_right % MOD) % MOD;
            }
            /// Left-down
            if(cnt_y_down && cnt_x_left) {
                answer = (answer + (ll) x * y % MOD * cnt_x_left % MOD * cnt_y_down % MOD) % MOD;
                answer = (answer - (ll) x * sum_y_down % MOD * cnt_x_left % MOD + MOD) % MOD;
                answer = (answer - (ll) y * sum_x_left % MOD * cnt_y_down % MOD + MOD) % MOD;
                answer = (answer + (ll) sum_x_left * sum_y_down % MOD) % MOD;
            }
//            cout << answer << '\n';
            sum_x_left = (sum_x_left + x) % MOD;
        }

        for(int x : x_axis[y]) {
            cnt_y[x] = (cnt_y[x] + 1) % MOD;
            sum_y[x] = (sum_y[x] + y) % MOD;
        }
    }

    for(int x = 0; x <= 2 * VMAX; x++) {
        cnt_y[x] = sum_y[x] = 0;
    }
//    cout << '\n';
    for(int y = 2 * VMAX; y >= 0; y--) {
        int sum = 0;
        for(int x : x_axis[y]) {
            sum = (sum + x) % MOD;
        }

        int sum_x_left = 0;
        for(int i = 0; i < (int) x_axis[y].size(); i++) {
            int x = x_axis[y][i];
            int sum_x_right = ((sum - sum_x_left + MOD) % MOD - x + MOD) % MOD;
            int sum_y_up = sum_y[x];
            int cnt_x_left = i;
            int cnt_x_right = x_axis[y].size() - i - 1;
            int cnt_y_up = cnt_y[x];

//            cout << x << ' ' << y << ' ' << sum_x_left << ' ' << sum_x_right << ' ' << sum_y_up << ' ' << cnt_left << ' ' << cnt_right << ' ';

            /// Right-Up
            if(cnt_y[x] && i < x_axis[y].size() - 1) {
                answer = (answer + (ll) sum_x_right * sum_y_up % MOD) % MOD;
                answer = (answer - (ll) y * sum_x_right % MOD * cnt_y_up % MOD + MOD) % MOD;
                answer = (answer - (ll) x * sum_y_up % MOD * cnt_x_right % MOD + MOD) % MOD;
                answer = (answer + (ll) x * y % MOD * cnt_x_right % MOD * cnt_y_up % MOD) % MOD;
            }
            /// Left-Up
            if(cnt_y[x] && i > 0) {
                answer = (answer + (ll) x * sum_y_up % MOD * cnt_x_left % MOD) % MOD;
                answer = (answer - (ll) x * y % MOD * cnt_x_left % MOD * cnt_y_up % MOD + MOD) % MOD;
                answer = (answer - (ll) sum_x_left * sum_y_up % MOD + MOD) % MOD;
                answer = (answer + (ll) y * sum_x_left % MOD * cnt_y_up % MOD) % MOD;
            }
//            cout << answer << '\n';
            sum_x_left = (sum_x_left + x) % MOD;
        }

        for(int x : x_axis[y]) {
            cnt_y[x] = (cnt_y[x] + 1) % MOD;
            sum_y[x] = (sum_y[x] + y) % MOD;
        }
    }
    cout << answer << '\n';

    return 0;
}
