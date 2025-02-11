#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

// #define int long long
#define ll long long
#define ld long double

using namespace std;
using namespace __gnu_pbds;

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

ifstream fin("cardgame.in");
ofstream fout("cardgame.out");

const int NMAX = 1e5;

struct TreeNode {
    int points, a, b;
    TreeNode() : points(0), a(0), b(0) {}
    TreeNode(int points, int a, int b) : points(points), a(a), b(b) {}
};

struct AINT {
    TreeNode aint[4 * NMAX + 1];

    void Initialize(int n) {
        for(int i = 1; i <= 4 * n; i++) {
            aint[i] = TreeNode(0, 0, 0);
        }
    }

    TreeNode UpdateNode(TreeNode left, TreeNode right) {
        TreeNode answer;
        answer.points = left.points + right.points + min(left.a, right.b);
        answer.a = left.a + right.a - min(left.a, right.b);
        answer.b = left.b + right.b - min(left.a, right.b);
        return answer;
    }

    void Update(int node, int left, int right, int pos, TreeNode value) {
        if(left == right) {
            aint[node] = value;
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

int n, ind;
int a[NMAX + 1];
int b[NMAX + 1];
bool freq[NMAX + 1];
int answer[NMAX + 1][2];

void ReadInput() {
    fin >> n;
    for(int i = 1; i <= n; i++) {
        fin >> a[i];
        freq[a[i]] = 1;
    }
}

void GetB() {
    // We need to choose the biggest values for the high card game and the lowest ones for the low card game
    // This is the optimal strategy
    for(int i = 2 * n; i >= 1; i--) {
        if(!freq[i]) {
            b[++ind] = i;
        }
    }
    // Now B is sorted in decreasing order
}

void Solve(int a[], int b[], int w) {
    // Now we just solve the high card game case using a segment tree
    aint.Initialize(2 * n);
    for(int i = 1; i <= n; i++) {
        aint.Update(1, 1, 2 * n, b[i], TreeNode(0, 0, 1));
        aint.Update(1, 1, 2 * n, a[i], TreeNode(0, 1, 0));
        answer[i][w] = aint.aint[1].points;
    }
}

void Switch() {
    // Reverse the arrays so we can get the best answer on the suffix this time
    reverse(a + 1, a + n + 1);
    reverse(b + 1, b + n + 1);

    // The low card game is equivalent to a high card game
    // if we switch each value with the one from the other array
    // it's like switching roles
    // if FJ puts a card now (which was Bessie's at the beginning)
    // then I should put a card greater than that (which is actually one of the FJ's cards)
    // this way BESSIE wins points, not FJ
    // so the strategy remains
    for(int i = 1; i <= n; i++) {
        a[i] = 2 * n - a[i] + 1;
        b[i] = 2 * n - b[i] + 1;
    }    
}

int GetAnswer() {
    int max_answer = 0;
    for(int i = 0; i <= n; i++) {
        max_answer = max(max_answer, answer[i][0] + answer[n - i][1]);
    }
    return max_answer;
}

signed main() {
    ios::sync_with_stdio(0);
    fin.tie(0);
    fout.tie(0);

    ReadInput();
    GetB();
    Solve(a, b, 0);
    Switch();
    Solve(a, b, 1);
    fout << GetAnswer() << '\n';

    return 0;
}