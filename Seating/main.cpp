#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define ll long long
#define ld long double

using namespace std;
using namespace __gnu_pbds;

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

ifstream fin("seating.in");
ofstream fout("seating.out");

const int NMAX = 5e5;

struct TreeNode {
    int max_length;
    int prefix_length;
    int suffix_length;
    bool full;
};

struct AINT {
    TreeNode aint[4 * NMAX + 1];
    int lazy[4 * NMAX + 1];

    TreeNode UpdateNode(TreeNode left, TreeNode right) {
        TreeNode answer;
        answer.max_length = max({left.max_length, right.max_length, left.suffix_length + right.prefix_length});
        answer.prefix_length = left.prefix_length + (left.full ? right.prefix_length : 0);
        answer.suffix_length = right.suffix_length + (right.full ? left.suffix_length : 0);
        answer.full = left.full && right.full;
        return answer;
    }

    void UpdateLazy(int node, int left, int right) {
        if(lazy[node] != -1) {
            if(lazy[node] == 0) {
                aint[node].max_length = aint[node].prefix_length = aint[node].suffix_length = right - left + 1;
                aint[node].full = 1;
            }
            else {
                aint[node].max_length = aint[node].prefix_length = aint[node].suffix_length = aint[node].full = 0;
            }

            if(left != right) {
                lazy[node * 2] = lazy[node];
                lazy[node * 2 + 1] = lazy[node];
            }
            lazy[node] = -1;
        }
    }

    void Build(int node, int left, int right) {
        if(left == right) {
            aint[node].max_length = aint[node].prefix_length = aint[node].suffix_length = aint[node].full = 1;
            lazy[node] = -1;
            return;
        }

        int mid = (left + right) / 2;
        Build(node * 2, left, mid);
        Build(node * 2 + 1, mid + 1, right);
        aint[node] = UpdateNode(aint[node * 2], aint[node * 2 + 1]);
    }
    
    void Update(int node, int left, int right, int Uleft, int Uright, int value) {
        if(left >= Uleft && right <= Uright) {
            lazy[node] = value;
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

    int GetPos(int node, int left, int right, int x) {    
        int mid = (left + right) / 2;
        UpdateLazy(node, left, right);
        UpdateLazy(node * 2, left, mid);
        UpdateLazy(node * 2 + 1, mid + 1, right);

        if(aint[node * 2].max_length >= x) {
            return GetPos(node * 2, left, mid, x);
        }
        if(aint[node * 2].suffix_length + aint[node * 2 + 1].prefix_length >= x) {
            assert(mid - aint[node * 2].suffix_length + 1 >= 1);
            return mid - aint[node * 2].suffix_length + 1;
        }
        if(aint[node * 2 + 1].max_length >= x) {
            return GetPos(node * 2 + 1, mid + 1, right, x);
        }
        return 0;
    }
}aint;

int n, m, answer;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    fin >> n >> m;
    aint.Build(1, 1, n);
    while(m--) {
        char type;
        fin >> type;
        if(type == 'A') {
            int x;
            fin >> x;
            int pos = aint.GetPos(1, 1, n, x);
            if(pos != 0) {
                aint.Update(1, 1, n, pos, pos + x - 1, 1);
            }
            else {
                answer++;
            }
        }
        else {
            int left, right;
            fin >> left >> right;
            aint.Update(1, 1, n, left, right, 0);
        }
    }
    fout << answer << '\n';

    return 0;
}