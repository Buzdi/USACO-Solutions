#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define ll long long
#define ld long double

using namespace std;
using namespace __gnu_pbds;

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

ifstream fin("haybales.in");
ofstream fout("haybales.out");

const int NMAX = 2e5;

struct TreeNode {
    ll sum, mini;
    TreeNode() : sum(0), mini(1e18) {}
    TreeNode(ll value) : sum(value), mini(value) {}
};

struct AINT {
    TreeNode aint[4 * NMAX + 1];
    ll lazy[4 * NMAX + 1] = {0};
  
    TreeNode UpdateNode(TreeNode left, TreeNode right) {
        TreeNode answer;
        answer.sum = left.sum + right.sum;
        answer.mini = min(left.mini, right.mini);
        return answer;
    }

    void ApplyLazy(int node, ll parent) {
        lazy[node] += parent;
    }

    void UpdateLazy(int node, int left, int right) {
        if(lazy[node] != 0) {
            aint[node].mini += lazy[node];
            aint[node].sum += (right - left + 1) * lazy[node];

            if(left != right) {
                ApplyLazy(node * 2, lazy[node]);
                ApplyLazy(node * 2 + 1, lazy[node]);
            }
            lazy[node] = 0;
        }
    }

    void Build(int node, int left, int right, int* a) {
        if(left == right) {
            aint[node] = TreeNode(a[left]);
            return;
        }

        int mid = (left + right) / 2;
        Build(node * 2, left, mid, a);
        Build(node * 2 + 1, mid + 1, right, a);
        aint[node] = UpdateNode(aint[node * 2], aint[node * 2 + 1]);
    }

    void Update(int node, int left, int right, int Uleft, int Uright, int value) {
        if(left >= Uleft && right <= Uright) {
            ApplyLazy(node, value);
            return;
        }

        UpdateLazy(node, left, right);
        int mid = (left + right) / 2;
        if(mid >= Uleft) {
            Update(node * 2, left, mid, Uleft, Uright, value);
        }
        if(mid + 1 <= Uright) {
            Update(node * 2 + 1, mid + 1, right, Uleft, Uright, value);
        }

        UpdateLazy(node * 2, left, mid);
        UpdateLazy(node * 2 + 1, mid + 1, right);
        aint[node] = UpdateNode(aint[node * 2], aint[node * 2 + 1]);
    }

    TreeNode Query(int node, int left, int right, int Qleft, int Qright) {
        UpdateLazy(node, left, right);
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
}aint;

int n, q;
int a[NMAX + 1];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    fin >> n >> q;
    for(int i = 1; i <= n; i++) {
        fin >> a[i];
    }

    aint.Build(1, 1, n, a);
    while(q--) {
        char type;
        fin >> type;
        if(type == 'P') {
            int left, right, value;
            fin >> left >> right >> value;
            aint.Update(1, 1, n, left, right, value);
        }
        else if(type == 'M') {
            int left, right;
            fin >> left >> right;
            fout << aint.Query(1, 1, n, left, right).mini << '\n';
        }
        else {
            int left, right;
            fin >> left >> right;
            fout << aint.Query(1, 1, n, left, right).sum << '\n';
        }
    }
    

    return 0;
}