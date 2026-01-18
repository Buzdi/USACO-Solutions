#include <bits/stdc++.h>

using namespace std;

ifstream fin("art2.in");
ofstream fout("art2.out");

const int NMAX = 1e5;

int n, answer;
int a[NMAX + 1];
int b[NMAX + 1], ind;
int freq[NMAX + 1], freq2[NMAX + 1];
stack<int> st;

int main()
{
    fin >> n;
    for(int i = 1; i <= n; i++) {
        fin >> a[i];
    }

    for(int i = 1; i <= n; i++) {
        freq[a[i]]++;
        freq2[a[i]]++;
    }

    answer = 0;
    for(int i = 1; i <= n; i++) {
        if(a[i] == 0) {
            if(!st.empty()) {
                fout << -1 << '\n';
                return 0;
            }
        }
        else {
            if(freq[a[i]] == freq2[a[i]]) {
                st.push(a[i]);
                freq[a[i]]--;
                answer = max(answer, (int)st.size());
                if(!freq[a[i]]) {
                    st.pop();
                }
            }
            else if(st.top() != a[i]) {
                fout << -1 << '\n';
                return 0;
            }
            else {
                freq[a[i]]--;
                if(!freq[a[i]]) {
                    st.pop();
                }
            }
        }
    }
    if(!st.empty()) {
        fout << -1 << '\n';
        return 0;
    }
    fout << answer << '\n';
    return 0;
}
