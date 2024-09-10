#include <iostream>
#include <algorithm>
#include <vector>
#define ll long long

using namespace std;

const int INF = 1e9;

int n, answer, L, total_letters, curent_letters;
string s;
int f1[128], f2[128];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

    cin >> n >> s;
    for(char x : s) {
        f1[x]++;
    }

    for(int i = 0; i < 128; i++) {
        if(f1[i]) {
            total_letters++;
        }
    }

    answer = INF;
    for(int i = 0; i < n; i++) {
        if(f2[s[i]] == 0) {
            curent_letters++;
        }
        f2[s[i]]++;

        while(curent_letters == total_letters) {
            answer = min(answer, i - L + 1);
            f2[s[L]]--;
            if(f2[s[L]] == 0) {
                curent_letters--;
            }
            L++;
        }
    }
    cout << answer << '\n';

	return 0;
}
