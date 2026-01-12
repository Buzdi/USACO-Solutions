#include <iostream>
#include <string>
#include <vector>

#define ll long long

using namespace std;

const string word = "bessie";
const int CMAX = 26;
const int DIM = 14; // 2 * 6 + 2
const int NMAX = 200005;

int n, q;
string s;

struct Matrix {
    ll a[DIM][DIM];

    Matrix() {
        for(int i = 0; i < DIM; i++) {
            for(int j = 0; j < DIM; j++) {
                a[i][j] = 0;
            }
        }
    }

    // Optimized multiplication: skips zero entries
    Matrix operator* (const Matrix& other) const {
        Matrix rez;
        for(int i = 0; i < DIM; i++) {
            for(int k = 0; k < DIM; k++) {
                if (a[i][k] == 0) continue; // Optimization for sparsity
                for(int j = 0; j < DIM; j++) {
                    rez.a[i][j] += a[i][k] * other.a[k][j];
                }
            }
        }
        return rez;
    }
} mats[CMAX];

// Global arrays for the Segment Tree
// We only store matrices for internal nodes to save memory.
// Leaves are generated on-the-fly.
Matrix tree[NMAX];
int lc[NMAX]; // Left child index
int rc[NMAX]; // Right child index
int nodes_cnt = 0; // Counter for internal nodes

int h(int i, int j) {
    return i * 6 + j;
}

Matrix get_matrix(char x) {
    Matrix m;
    // Logic identical to original code
    if(x == word[5]) {
        m.a[h(0, 0)][h(0, 5)]++;
        m.a[h(1, 0)][h(1, 5)]++;
        m.a[h(1, 0)][h(0, 5)]++;
        m.a[h(2, 1)][h(1, 5)]++;
        m.a[h(2, 1)][h(0, 5)]++;
    }
    else {
        m.a[h(0, 5)][h(0, 5)]++;
        m.a[h(1, 5)][h(1, 5)]++;
        m.a[h(2, 1)][h(1, 5)]++;
    }

    for(int j = 0; j < 5; j++) {
        if(x == word[j]) {
            m.a[h(0, j + 1)][h(0, j)]++;
            m.a[h(1, j + 1)][h(1, j)]++;
            m.a[h(2, 1)][h(1, j)]++;
        }
        else {
            m.a[h(0, j)][h(0, j)]++;
            m.a[h(1, j)][h(1, j)]++;
            m.a[h(2, 1)][h(1, j)]++;
        }
    }

    m.a[h(2, 0)][h(2, 0)]++;
    if(x == word[0]) {
        m.a[h(0, 1)][h(2, 0)]++;
    }
    else {
        m.a[h(0, 0)][h(2, 0)]++;
    }

    m.a[h(2, 1)][h(2, 1)]++;
    return m;
}

// Helper: Retrieve matrix value.
// If id > 0, it's an internal node (stored in tree).
// If id < 0, it's a leaf (corresponds to index -id in string s).
Matrix get_val(int id) {
    if (id > 0) return tree[id];
    return mats[s[-id] - 'a'];
}

// Builds the tree and returns the node ID
int build(int left, int right) {
    if(left == right) {
        // Return negative index to represent a virtual leaf
        return -left;
    }

    int mid = (left + right) / 2;
    int id = ++nodes_cnt; // Allocate internal node

    lc[id] = build(left, mid);
    rc[id] = build(mid + 1, right);

    // Note: Original logic was Right * Left
    tree[id] = get_val(rc[id]) * get_val(lc[id]);
    return id;
}

void update(int id, int left, int right, int pos, char value) {
    if(left == right) {
        // Update the string directly.
        // The get_val function will pick up the new char via s[-id].
        s[pos] = value;
        return;
    }

    int mid = (left + right) / 2;
    if(pos <= mid) {
        update(lc[id], left, mid, pos, value);
    }
    else {
        update(rc[id], mid + 1, right, pos, value);
    }

    tree[id] = get_val(rc[id]) * get_val(lc[id]);
}

ll query(int root_id) {
    Matrix m = get_val(root_id);
    return m.a[h(2, 1)][h(2, 0)];
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> s;
    n = s.size();
    s = "$" + s; // 1-based indexing

    // Precompute the 26 basic matrices
    for(int i = 0; i < CMAX; i++) {
        mats[i] = get_matrix(char(i + 'a'));
    }

    // Build tree
    int root = build(1, n);

    cin >> q;
    cout << query(root) << '\n';

    while(q--) {
        int pos;
        char letter;
        cin >> pos >> letter;
        update(root, 1, n, pos, letter);
        cout << query(root) << '\n';
    }
    return 0;
}
