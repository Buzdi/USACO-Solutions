#include <fstream>
#include <algorithm>

using namespace std;

ifstream cin("lifeguards.in");
ofstream cout("lifeguards.out");

const int NMAX = 1e5;
const int INF = 2e9;

int n, ind_values, ind, total, mini;
pair<int, int> a[NMAX + 1];
int values[2 * NMAX + 1];
int width[2 * NMAX + 1];
int mars[2 * NMAX + 1];
int sp1[2 * NMAX + 1];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> a[i].first >> a[i].second;
    }

    for(int i = 1; i <= n; i++) {
        values[++ind_values] = a[i].first;
        values[++ind_values] = a[i].second;
    }

    sort(values + 1, values + ind_values + 1);
    ind = 1;
    for(int i = 2; i <= ind_values; i++) {
        if(values[i] != values[i - 1]) {
            values[++ind] = values[i];
        }
    }
    ind_values = ind;

    for(int i = 1; i <= n; i++) {
        a[i].first = lower_bound(values + 1, values + ind_values + 1, a[i].first) - values;
        a[i].second = lower_bound(values + 1, values + ind_values + 1, a[i].second) - values;

        mars[a[i].first]++;
        mars[a[i].second]--;
    }

    for(int i = 1; i <= ind_values; i++) {
        mars[i] += mars[i - 1];
    }

    for(int i = 1; i < ind_values; i++) {
        width[i] = values[i + 1] - values[i];
    }

    for(int i = 1; i <= ind_values; i++) {
        total += (mars[i] > 0 ? width[i] : 0);
    }

    for(int i = 1; i <= ind_values; i++) {
        sp1[i] = sp1[i - 1] + (mars[i] == 1 ? width[i] : 0);
    }

    mini = INF;
    for(int i = 1; i <= n; i++) {
        mini = min(mini, sp1[a[i].second - 1] - sp1[a[i].first - 1]);
    }
    cout << total - mini << '\n';


    return 0;
}