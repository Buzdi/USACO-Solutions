#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int NMAX = 1090;

struct Cow {
    int x, y, ind;
};

int n, root;
vector<Cow> east_cows, north_cows;
int parent[NMAX + 1];
vector<int> G[NMAX + 1];
int answer[NMAX + 1];

bool cmpE(Cow a, Cow b) {
    return a.y < b.y;
}

bool cmpN(Cow a, Cow b) {
    return a.x < b.x;
}

int GetRoot(int node) {
    while(parent[node]) {
        node = parent[node];
    }
    return node;
}

void DFS(int node) {
    answer[node] = 1;
    for(int next_node : G[node]) {
        DFS(next_node);
        answer[node] += answer[next_node];
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    for(int i = 1; i <= n; i++) {
        char dir;
        int x, y;
        cin >> dir >> x >> y;
        if(dir == 'E') {
            east_cows.push_back({x, y, i});
        }
        else {
            north_cows.push_back({x, y, i});
        }
    }
    sort(east_cows.begin(), east_cows.end(), cmpE);
    sort(north_cows.begin(), north_cows.end(), cmpN);

    for(auto &east_cow : east_cows) {
        for(auto &north_cow : north_cows) {
            if(!parent[east_cow.ind] && !parent[north_cow.ind] && east_cow.x < north_cow.x && east_cow.y > north_cow.y) {
                int north_distance = east_cow.y - north_cow.y;
                int east_distance = north_cow.x - east_cow.x;

                if(north_distance < east_distance) {
                    parent[east_cow.ind] = north_cow.ind;
                    G[north_cow.ind].push_back(east_cow.ind);
                }
                else if(north_distance > east_distance) {
                    parent[north_cow.ind] = east_cow.ind;
                    G[east_cow.ind].push_back(north_cow.ind);
                }
            }
        }
    }
    
    for(int i = 1; i <= n; i++) {
        if(!answer[i]) {
            DFS(i);
        }
    }
    for(int i = 1; i <= n; i++) {
        cout << answer[i] - 1 << '\n';
    }

    return 0;
}