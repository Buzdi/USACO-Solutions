#include <bits/stdc++.h>
#define ll long long

using namespace std;

ifstream fin("deleg.in");
ofstream fout("deleg.out");

const int NMAX = 1e5;

int n;
bool answer[NMAX + 1];
vector<int> g[NMAX + 1];

int DFS(int node, int d, int dad = 0) {
    vector<int> v;
    for(int next_node : g[node]) {
        if(next_node != dad) {
            int here = DFS(next_node, d, node);
            if(!here) {
                return 0;
            }
            v.push_back(here);
        }
    }

    multiset<int> s;
    int sz = v.size();
    for(int i = 0; i < sz; i++) {
        if(v[i] == d) {
            continue;
        }

        if(s.count(d - v[i])) {
            s.erase(s.find(d - v[i]));
        }
        else {
            s.insert(v[i]);
        }
    }

    if(s.size() >= 2) {
        return 0;
    }
    if(s.empty()) {
        return 1;
    }
    return *s.begin() + 1;
}

int main() {
    fin >> n;
    for(int i = 1; i <= n - 1; i++) {
        int a, b;
        fin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    for(int d = 1; d * d <= n - 1; d++) {
        if((n - 1) % d == 0) {
            answer[d] = DFS(1, d);
            if(d * d != n - 1) {
                answer[(n - 1) / d] = DFS(1, (n - 1) / d);
            }
        }
    }

    for(int i = 1; i <= n - 1; i++) {
        fout << answer[i];
    }
    return 0;
}
