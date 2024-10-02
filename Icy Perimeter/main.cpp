#include <fstream>
#include <queue>

using namespace std;

ifstream cin("perimeter.in");
ofstream cout("perimeter.out");

const int NMAX = 1000;
const int di[] = {0, 0, 1, -1};
const int dj[] = {1, -1, 0, 0};

int n, curent_area, curent_perimeter, max_area, min_perimeter;
char a[NMAX + 1][NMAX + 1];
bool visited[NMAX + 1][NMAX + 1];

bool InMat(int i, int j) {
    return i >= 1 && i <= n && j >= 1 && j <= n;
}

void Fill(int istart, int jstart) {
    curent_area = curent_perimeter = 0;

    queue<pair<int, int>> Q;
    visited[istart][jstart] = 1;
    Q.push({istart, jstart});
    while(!Q.empty()) {
        auto [i, j] = Q.front();
        Q.pop();

        /// Area
        curent_area++;

        for(int d = 0; d < 4; d++) {
            int inou = i + di[d];
            int jnou = j + dj[d];
            if(InMat(inou, jnou) && a[inou][jnou] == '#' && !visited[inou][jnou]) {
                visited[inou][jnou] = 1;
                Q.push({inou, jnou});
            }
            if(!InMat(inou, jnou) || a[inou][jnou] == '.') { /// Perimeter
                curent_perimeter++;
            }
        }
    }
}

int main()
{
    cin >> n;
    cin.get();
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            cin >> a[i][j];
        }
    }

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            if(!visited[i][j] && a[i][j] == '#') {
                Fill(i, j);
                if(curent_area > max_area) {
                    max_area = curent_area;
                    min_perimeter = curent_perimeter;
                }
                else if(curent_area == max_area && curent_perimeter < min_perimeter) {
                    min_perimeter = curent_perimeter;
                }
            }
        }
    }
    cout << max_area << ' ' << min_perimeter;

    return 0;
}
