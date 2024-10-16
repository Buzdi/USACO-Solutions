#include <fstream>
#include <queue>
#include <map>
#include <set>

using namespace std;

ifstream cin("multimoo.in");
ofstream cout("multimoo.out");

const int NMAX = 250;
const int di[] = {0, 0, 1, -1};
const int dj[] = {1, -1, 0, 0};

int n, components, answer1, answer2;
int a[NMAX + 1][NMAX + 1];
int component[NMAX + 1][NMAX + 1];
int component_size[NMAX * NMAX + 1];
int values[NMAX * NMAX + 1];
map<pair<int, int>, set<int>> visited;
vector<int> G[NMAX * NMAX + 1];

bool InMat(int i, int j) {
    return i >= 1 && i <= n && j >= 1 && j <= n;
}

void Fill(int istart, int jstart) {
    queue<pair<int, int>> Q;
    components++;
    component[istart][jstart] = components;
    component_size[components]++;
    values[components] = a[istart][jstart];
    Q.push({istart, jstart});
    while(!Q.empty()) {
        auto [i, j] = Q.front();
        Q.pop();

        for(int d = 0; d < 4; d++) {
            int inou = i + di[d];
            int jnou = j + dj[d];
            if(InMat(inou, jnou) && a[inou][jnou] == a[i][j] && !component[inou][jnou]) {
                component[inou][jnou] = components;
                component_size[components]++;
                Q.push({inou, jnou});
            }
        }
    }
}

int FillComponents(int start_node, pair<int, int> active) {
    queue<int> Q;
    visited[active].insert(start_node);
    int curent_size = component_size[start_node];
    Q.push(start_node);
    while(!Q.empty()) {
        int node = Q.front();
        Q.pop();

        for(int next_node : G[node]) {
            if((values[next_node] == active.first || values[next_node] == active.second) && !visited[active].count(next_node)) {
                visited[active].insert(next_node);
                curent_size += component_size[next_node];
                Q.push(next_node);
            }
        }
    }
    return curent_size;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            cin >> a[i][j];
        }
    }

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            if(!component[i][j]) {
                Fill(i, j);
            }
        }
    }

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            for(int d = 0; d < 4; d++) {
                int inou = i + di[d];
                int jnou = j + dj[d];
                if(InMat(inou, jnou) && component[i][j] && component[inou][jnou]) {
                    G[component[i][j]].push_back(component[inou][jnou]);
                    G[component[inou][jnou]].push_back(component[i][j]);
                }
            }
        }
    }

    for(int i = 1; i <= components; i++) {
        answer1 = max(answer1, component_size[i]);
    }

    for(int node = 1; node <= components; node++) {
        for(int next_node : G[node]) {
            pair<int, int> active = {values[node], values[next_node]};
            if(active.first > active.second) {
                swap(active.first, active.second);
            }
            if(visited[active].count(node)) {
                continue;
            }

            int answer_here = FillComponents(node, active);
            answer2 = max(answer2, answer_here);
        }
    }
    cout << answer1 << '\n' << answer2 << '\n';

    return 0;
}
