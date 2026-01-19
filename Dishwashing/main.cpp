#include <bits/stdc++.h>

using namespace std;

ifstream fin("dishes.in");
ofstream fout("dishes.out");

const int NMAX = 1e5;
const int INF = 1e9;

int n;
int a[NMAX + 1];
int order[NMAX + 1];
bool freq[NMAX + 1];
stack<int> st[NMAX + 1];

int bs(int k, int start, int value) {
    int left = start, right = k, answer = -1;
    while(left <= right) {
        int mid = (left + right) / 2;
        if(st[mid].top() > value) {
            answer = mid;
            right = mid - 1;
        }
        else {
            left = mid + 1;
        }
    }
    assert(answer != -1);
    return answer;
}

bool check(int k) {
    fill(freq + 1, freq + n + 1, 0);
    for(int i = 1; i <= k; i++) {
        while(!st[i].empty()) {
            st[i].pop();
        }
        st[i].push(INF);
    }

    for(int i = 1; i <= k; i++) {
        freq[a[i]] = 1;
    }

    int ind = 0;
    for(int i = 1; i <= n; i++) {
        if(freq[i]) {
            order[++ind] = i;
        }
    }

    int first_ind_st = 1;
    int curent_ind = 1;
    for(int i = 1; i <= k; i++) {
        /// Pun element
        int pos = bs(k, first_ind_st, a[i]);
        st[pos].push(a[i]);

        /// Acum elimin ca un turbat
        while(!st[first_ind_st].empty() && st[first_ind_st].top() == order[curent_ind]) {
            st[first_ind_st].pop();
            if(st[first_ind_st].top() == INF) {
                first_ind_st++;
            }
            curent_ind++;
        }
    }
    return curent_ind > ind;
}

int main()
{
    fin >> n;
    for(int i = 1; i <= n; i++) {
        fin >> a[i];
    }

    int left = 1, right = n, answer = -1;
    while(left <= right) {
        int mid = (left + right) / 2;
        if(check(mid)) {
            answer = mid;
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    fout << answer << '\n';
    return 0;
}
