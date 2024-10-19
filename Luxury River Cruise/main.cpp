#include <fstream>
#define ll long long
using namespace std;

ifstream cin("cruise.in");
ofstream cout("cruise.out");

const int NMAX = 1000;
const int MMAX = 500;
const int LGMAX = 30;

int n, m, k, answer;
int a[NMAX + 1][2];
int moves[MMAX + 1];
int nxt[NMAX + 1][LGMAX + 1];

int GetNext(int i) {
    int x = i;
    for(int i = 1; i <= m; i++) {
        x = a[x][moves[i]];
    }
    return x;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m >> k;
    for(int i = 1; i <= n; i++) {
        cin >> a[i][0] >> a[i][1];
    }
    for(int i = 1; i <= m; i++) {
        char x;
        cin >> x;
        moves[i] = (x == 'L' ? 0 : 1);
    }

    for(int i = 1; i <= n; i++) {
        nxt[i][0] = GetNext(i);
    }
    for(int k = 1; k <= LGMAX; k++) {
        for(int i = 1; i <= n; i++) {
            nxt[i][k] = nxt[nxt[i][k - 1]][k - 1];
        }
    }

    answer = 1;
    for(int bit = 0; bit <= LGMAX; bit++) {
        if((k >> bit) & 1) {
            answer = nxt[answer][bit];
        }
    }
    cout << answer << '\n';

    return 0;
}
