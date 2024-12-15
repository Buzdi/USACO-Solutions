#include <fstream>
#include <queue>
#include <vector>
#include <cassert>

using namespace std;

ifstream cin("milkorder.in");
ofstream cout("milkorder.out");

const int NMAX = 1e5;
const int MMAX = 5e4;

int n, m;
vector<int> a[MMAX + 1];
vector<int> g[NMAX + 1];
int topsort[NMAX + 1];
int indegree[NMAX + 1];

bool Check(int pos) {
    for(int i = 1; i <= n; i++) {
        g[i].clear();
        indegree[i] = 0;
    }

    for(int i = 1; i <= pos; i++) {
        for(int j = 0; j < (int) a[i].size() - 1; j++) {
            g[a[i][j]].push_back(a[i][j + 1]);
            indegree[a[i][j + 1]]++;
        }
    }

    priority_queue<int> pq;
    for(int i = 1; i <= n; i++) {
        if(indegree[i] == 0) {
            pq.push(-i);
        }
    }

    int ind = 0;
    while(!pq.empty()) {
        int node = -pq.top();
        pq.pop();

        topsort[++ind] = node;
        for(int next_node : g[node]) {
            indegree[next_node]--;
            if(indegree[next_node] == 0) {
                pq.push(-next_node);
            }
        }
    }

    return ind == n;
}

int main()
{
    cin >> n >> m;
    for(int i = 1; i <= m; i++) {
        int k;
        cin >> k;
        for(int j = 1; j <= k; j++) {
            int x;
            cin >> x;
            a[i].push_back(x);
        }
    }

    int left = 0, right = m, answer = -1;
    while(left <= right) {
        int mid = (left + right) / 2;
        if(Check(mid)) {
            answer = mid;
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    assert(answer != -1);

    Check(answer);
    for(int i = 1; i <= n; i++) {
        cout << topsort[i];
        if(i < n) {
            cout << ' ';
        }
    }

    return 0;
}
