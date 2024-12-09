#include <fstream>
#include <map>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

ifstream cin("promote.in");
ofstream cout("promote.out");

typedef tree<
int,
null_type,
less<int>,
rb_tree_tag,
tree_order_statistics_node_update> ordered_set;

const int NMAX = 1e5;

int n;
int a[NMAX + 1];
int answer[NMAX + 1];
vector<int> g[NMAX + 1];
ordered_set s;

void DFS(int node, int dad = 0) {
    answer[node] -= s.size() - s.order_of_key(a[node] + 1);
    s.insert(a[node]);

    for(int next_node : g[node]) {
        if(next_node != dad) {
            DFS(next_node, node);
        }
    }
    answer[node] += s.size() - s.order_of_key(a[node] + 1);
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    for(int i = 2; i <= n; i++) {
        int x;
        cin >> x;
        g[i].push_back(x);
        g[x].push_back(i);
    }

    DFS(1);
    for(int i = 1; i <= n; i++) {
        cout << answer[i] << '\n';
    }

    return 0;
}
