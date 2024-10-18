#include <fstream>
#include <vector>

using namespace std;

ifstream cin("clocktree.in");
ofstream cout("clocktree.out");

const int NMAX = 2500;

int n;
vector<int> G[NMAX + 1];
int a[NMAX + 1];
int sum_group[2];
int cnt_group[2];

void DFS(int node, int colour, int dad = 0) {
    cnt_group[colour]++;
    sum_group[colour] += a[node];
    for(int next_node : G[node]) {
        if(next_node != dad) {
            DFS(next_node, colour ^ 1, node);
        }
    }
}

int main()
{
    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    for(int i = 1; i <= n - 1; i++) {
        int a, b;
        cin >> a >> b;
        G[a].push_back(b);
        G[b].push_back(a);
    }

    DFS(1, 0);
    if(sum_group[0] % 12 == sum_group[1] % 12) {
        cout << n << '\n';
    }
    else if(sum_group[0] % 12 == (sum_group[1] + 1) % 12) {
        cout << cnt_group[0] << '\n';
    }
    else if((sum_group[0] + 1) % 12 == sum_group[1] % 12) {
        cout << cnt_group[1] << '\n';
    }
    else {
        cout << 0 << '\n';
    }

    return 0;
}
