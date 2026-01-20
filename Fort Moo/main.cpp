#include <bits/stdc++.h>

using namespace std;

ifstream fin("fortmoo.in");
ofstream fout("fortmoo.out");

const int NMAX = 200;

int n, m, answer;
int sp[NMAX + 1][NMAX + 1];

int get_sum(int i, int j1, int j2) {
    return sp[i][j2] - sp[i][j1 - 1];
}

int main()
{
    fin >> n >> m;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            char x;
            fin >> x;
            sp[i][j] = sp[i][j - 1] + (x == 'X');
        }
    }

    for(int j1 = 1; j1 <= m; j1++) {
        for(int j2 = j1; j2 <= m; j2++) {
            int last = 0;
            for(int i = 1; i <= n; i++) {
                int sum_here = get_sum(i, j1, j2);
                if(!sum_here) {
                    answer = max(answer, j2 - j1 + 1);
                }
                if(!sum_here && last) {
                    answer = max(answer, (j2 - j1 + 1) * (i - last + 1));
                }
                if(!sum_here && !last) {
                    last = i;
                }
                if(get_sum(i, j1, j1) || get_sum(i, j2, j2)) {
                    last = 0;
                }
            }
        }
    }
    fout << answer << '\n';
    return 0;
}
