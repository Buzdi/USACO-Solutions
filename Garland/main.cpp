#include <iostream>
#include <algorithm>

using namespace std;

const int NMAX = 1500;
const int CMAX = 26;

int n, Q;
string s;
int answer[NMAX + 1][CMAX + 1];

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> s >> Q;
    s = "%" + s;

    for(int j = 1; j <= n; j++) {
        for(int c = 0; c < 26; c++) {
            int left = 1, bad = 0;
            for(int i = 1; i <= n; i++) {
                int x = s[i] - 'a';
                if(x != c) {
                    bad++;
                }

                while(bad > j) {
                    int x = s[left] - 'a';
                    if(x != c) {
                        bad--;
                    }
                    left++;
                }

                answer[j][c] = max(answer[j][c], i - left + 1);
            }
        }
    }

    while(Q--) {
        int m;
        char c;
        cin >> m >> c;
        cout << answer[m][c - 'a'] << '\n';
    }

    return 0;
}
