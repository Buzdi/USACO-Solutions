#include <fstream>
#include <cassert>

#define ll long long

using namespace std;

ifstream cin("superbull.in");
ofstream cout("superbull.out");

const int NMAX = 2000;

int n;
ll total_w;
int a[NMAX + 1];
int cost[NMAX + 1];
bool done[NMAX + 1];

int main()
{
    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    for(int i = 1; i <= n; i++) {
        cost[i] = -1;
    }
    cost[1] = 0;
    for(int step = 1; step <= n; step++) {
        int max_node = 0;
        for(int i = 1; i <= n; i++) {
            if(!done[i] && (max_node == 0 || cost[i] > cost[max_node])) {
                max_node = i;
            }
        }

        assert(cost[max_node] != -1);
        total_w += cost[max_node];
        done[max_node] = 1;

        for(int i = 1; i <= n; i++) {
            if(!done[i] && (a[i] ^ a[max_node]) > cost[i]) {
                cost[i] = a[i] ^ a[max_node];
//                cout << max_node << ' ' << i << '\n';
            }
        }
//        cout << '\n';
    }
    cout << total_w << '\n';
//    for(int i = 1; i <= n; i++) {
//        cout << cost[i] << ' ';
//    }

    return 0;
}
