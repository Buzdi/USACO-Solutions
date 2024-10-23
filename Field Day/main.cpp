#include <iostream>
#include <queue>

using namespace std;

const int NMAX = 1e5;
const int CMAX = 18;

int n, c;
int a[NMAX + 1];
int min_distance[(1 << CMAX) + 1];
queue<int> Q;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> c >> n;
    for(int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        for(int j = 0; j < c; j++) {
            if(s[j] == 'G') {
                a[i] |= (1 << j);
            }
        }
    }

    for(int i = 1; i <= n; i++) {
        min_distance[a[i]] = 1;
        Q.push(a[i]);
    }

    while(!Q.empty()) {
        int curent_mask = Q.front();
        Q.pop();
        for(int i = 0; i < c; i++) {
            int next_mask = curent_mask ^ (1 << i);
            if(!min_distance[next_mask]) {
                min_distance[next_mask] = min_distance[curent_mask] + 1;
                Q.push(next_mask);
            }
        }
    }

    for(int i = 1; i <= n; i++) {
        int inverse_a = (a[i] ^ ((1 << c) - 1));
        cout << c - min_distance[inverse_a] + 1 << '\n';
    }

    return 0;
}
