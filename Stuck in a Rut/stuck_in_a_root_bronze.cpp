#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int NMAX = 50;

struct Cow {
    int x, y, ind;
};

int n;
vector<Cow> east_cows, north_cows;
int stop_pos[NMAX + 1];
int rut_distance[NMAX + 1];

bool cmpE(Cow a, Cow b) {
    return a.y < b.y;
}

bool cmpN(Cow a, Cow b) {
    return a.x < b.x;
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

    for(int i = 1; i <= n; i++) {
        stop_pos[i] = -1;
        rut_distance[i] = -1;
    }

    for(auto &east_cow : east_cows) {
        for(auto &north_cow : north_cows) {
            if(stop_pos[east_cow.ind] == -1 && stop_pos[north_cow.ind] == -1 && east_cow.x < north_cow.x && east_cow.y > north_cow.y) {
                int north_distance = east_cow.y - north_cow.y;
                int east_distance = north_cow.x - east_cow.x;

                if(north_distance < east_distance) {
                    stop_pos[east_cow.ind] = north_cow.x;
                }
                else if(north_distance > east_distance) {
                    stop_pos[north_cow.ind] = east_cow.y;
                }
            }
        }
    }

    for(auto &east_cow : east_cows) {
        if(stop_pos[east_cow.ind] != -1) {
            rut_distance[east_cow.ind] = stop_pos[east_cow.ind] - east_cow.x;
        }
    }
    for(auto &north_cow : north_cows) {
        if(stop_pos[north_cow.ind] != -1) {
            rut_distance[north_cow.ind] = stop_pos[north_cow.ind] - north_cow.y;
        }
    }

    for(int i = 1; i <= n; i++) {
        if(rut_distance[i] == -1) {
            cout << "Infinity" << '\n';
        }
        else {
            cout << rut_distance[i] << '\n';
        }
    }

    return 0;
}