#include <fstream>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

ifstream cin("bphoto.in");
ofstream cout("bphoto.out");

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

const int NMAX = 1e5;

int n, answer;
int a[NMAX + 1];
int L[NMAX + 1], R[NMAX + 1];
ordered_set s;

int main()
{
    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    for(int i = 1; i <= n; i++) {
        L[i] = i - 1 - s.order_of_key(a[i]);
        s.insert(a[i]);
    }

    s.clear();
    for(int i = n; i >= 1; i--) {
        R[i] = n - i - s.order_of_key(a[i]);
        s.insert(a[i]);
    }

    for(int i = 1; i <= n; i++) {
        if(max(L[i], R[i]) > 2 * min(L[i], R[i])) {
            answer++;
        }
    }
    cout << answer << '\n';

    return 0;
}
