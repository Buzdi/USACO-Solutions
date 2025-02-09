#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define ll long long
#define ld long double

using namespace std;
using namespace __gnu_pbds;

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

ifstream fin("optmilk.in");
ofstream fout("optmilk.out");

const int NMAX = 4e4;

struct TreeNode {
    int aa, ab, ba, bb;
};

struct AINT {
    TreeNode aint[4 * NMAX + 1];

    TreeNode UpdateNode(TreeNode left, TreeNode right) {
        TreeNode answer;
        answer.aa = max({left.ab + right.aa, left.ab + right.ba, left.aa + right.ba});
        answer.ab = max({left.ab + right.ab, left.ab + right.bb, left.aa + right.bb});
        answer.ba = max({left.ba + right.ba, left.bb + right.aa, left.bb + right.ba});
        answer.bb = max({left.ba + right.bb, left.bb + right.ab, left.bb + right.bb});
        return answer;
    }

    void Build(int node, int left, int right, int* a) {
        if(left == right) {
            aint[node].aa = a[left];
            aint[node].ab = aint[node].ba = aint[node].bb = 0;
            return;
        }

        int mid = (left + right) / 2;
        Build(node * 2, left, mid, a);
        Build(node * 2 + 1, mid + 1, right, a);
        aint[node] = UpdateNode(aint[node * 2], aint[node * 2 + 1]);
    }

    void Update(int node, int left, int right, int pos, int value) {
        if(left == right) {
            aint[node].aa = value;
            aint[node].ab = aint[node].ba = aint[node].bb = 0;
            return;
        }

        int mid = (left + right) / 2;
        if(pos <= mid) {
            Update(node * 2, left, mid, pos, value);
        }
        else {
            Update(node * 2 + 1, mid + 1, right, pos, value);
        }
        aint[node] = UpdateNode(aint[node * 2], aint[node * 2 + 1]);
    }
}aint;

int n, q;
ll sum_answer;
int a[NMAX + 1];

signed main() {
    ios::sync_with_stdio(0);
    fin.tie(0);
    fout.tie(0);

    fin >> n >> q;
    for(int i = 1; i <= n; i++) {
        fin >> a[i];
    }

    aint.Build(1, 1, n, a);
    while(q--) {
        int pos, value;
        fin >> pos >> value;
        aint.Update(1, 1, n, pos, value);
        sum_answer += max({aint.aint[1].aa, aint.aint[1].bb, aint.aint[1].ab, aint.aint[1].ba});
    }
    fout << sum_answer << '\n';

    return 0;
}