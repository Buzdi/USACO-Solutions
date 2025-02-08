#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define ll long long
#define ld long double

using namespace std;
using namespace __gnu_pbds;

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

ifstream fin("marathon.in");
ofstream fout("marathon.out");

const int NMAX = 1e5;

struct TreeNode {
    int sum, mini;
    TreeNode() : sum(0), mini(2e9) {}
    TreeNode(int sum, int mini) : sum(sum), mini(mini) {} 
};

struct AINT {
    TreeNode aint[4 * NMAX + 1];

    TreeNode UpdateNode(TreeNode left, TreeNode right) {
        TreeNode answer;
        answer.sum = left.sum + right.sum;
        answer.mini = min(left.mini, right.mini);
        return answer;
    }

    void Build(int node, int left, int right, int* x, int* y = NULL) {
        if(left == right) {
            if(y == NULL) {
                aint[node].sum = abs(x[left] - x[left + 1]);
            }
            else {
                aint[node].mini = -abs(x[left] - x[left + 1]) - abs(x[left + 1] - x[left + 2]) + abs(x[left] - x[left + 2]);
                aint[node].mini += -abs(y[left] - y[left + 1]) - abs(y[left + 1] - y[left + 2]) + abs(y[left] - y[left + 2]);
            }
            return;
        }

        int mid = (left + right) / 2;
        Build(node * 2, left, mid, x, y);
        Build(node * 2 + 1, mid + 1, right, x, y);
        aint[node] = UpdateNode(aint[node * 2], aint[node * 2 + 1]);
    }

    void Update(int node, int left, int right, int pos, int* x, int* y = NULL) {
        if(left == right) {
            if(y == NULL) {
                aint[node].sum = abs(x[left] - x[left + 1]);
            }
            else {
                aint[node].mini = -abs(x[left] - x[left + 1]) - abs(x[left + 1] - x[left + 2]) + abs(x[left] - x[left + 2]);
                aint[node].mini += -abs(y[left] - y[left + 1]) - abs(y[left + 1] - y[left + 2]) + abs(y[left] - y[left + 2]);
            }
            return;
        }

        int mid = (left + right) / 2;
        if(pos <= mid) {
            Update(node * 2, left, mid, pos, x, y);
        }
        else {
            Update(node * 2 + 1, mid + 1, right, pos, x, y);
        }
        aint[node] = UpdateNode(aint[node * 2], aint[node * 2 + 1]);
    }

    TreeNode Query(int node, int left, int right, int Qleft, int Qright) {
        if(left >= Qleft && right <= Qright) {
            return aint[node];
        }

        int mid = (left + right) / 2;
        if(mid >= Qright) {
            return Query(node * 2, left, mid, Qleft, Qright);
        }
        if(mid + 1 <= Qleft) {
            return Query(node * 2 + 1, mid + 1, right, Qleft, Qright);
        }
        TreeNode left_node = Query(node * 2, left, mid, Qleft, Qright);
        TreeNode right_node = Query(node * 2 + 1, mid + 1, right, Qleft, Qright);
        return UpdateNode(left_node, right_node);
    }
}aint[3];

int n, q;
int x[2][NMAX + 1];

void Update(int type, int pos, int value = 0) {
    if(type <= 1) {
        x[type][pos] = value;
        if(pos + 1 <= n) {
            aint[type].Update(1, 1, n - 1, pos, x[type]);
        }
        if(pos - 1 >= 1) {
            aint[type].Update(1, 1, n - 1, pos - 1, x[type]);
        }
        return;
    }

    if(pos + 2 <= n) {
        aint[2].Update(1, 1, n - 2, pos, x[0], x[1]);
    }
    if(pos - 1 >= 1 && pos + 1 <= n) {
        aint[2].Update(1, 1, n - 2, pos - 1, x[0], x[1]);
    }
    if(pos - 2 >= 1) {
        aint[2].Update(1, 1, n - 2, pos - 2, x[0], x[1]);
    }
}

int Query(int left, int right) {
    int sum_abs = aint[0].Query(1, 1, n - 1, left, right - 1).sum + aint[1].Query(1, 1, n - 1, left, right - 1).sum;
    int min_change = aint[2].Query(1, 1, n - 2, left, right - 2).mini;
    return sum_abs + min_change;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    fin >> n >> q;
    for(int i = 1; i <= n; i++) {
        fin >> x[0][i] >> x[1][i];
    }

    aint[0].Build(1, 1, n - 1, x[0]);
    aint[1].Build(1, 1, n - 1, x[1]);
    aint[2].Build(1, 1, n - 2, x[0], x[1]);
    while(q--) {
        char type;
        fin >> type;
        if(type == 'U') {
            int p, x, y;
            fin >> p >> x >> y;
            Update(0, p, x);
            Update(1, p, y);
            Update(2, p);
        }
        else {
            int left, right;
            fin >> left >> right;
            if(left == right) {
                fout << 0 << '\n';
            }
            else if(left + 1 == right) {
                fout << abs(x[0][left] - x[0][right]) + abs(x[1][left] + x[1][right]) << '\n';
            }
            else {
                fout << Query(left, right) << '\n';
            }
        }
    }

    return 0;
}