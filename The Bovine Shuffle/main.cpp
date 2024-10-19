#include <fstream>

using namespace std;

ifstream cin("shuffle.in");
ofstream cout("shuffle.out");

const int NMAX = 1e5;

int n, answer;
int a[NMAX + 1];
int visited[NMAX + 1];

void Floyd(int i) {
    visited[i] = 1;
    int x = i, y = i;
    do{
        x = a[x];
        if(visited[x] == 2) {
            return;
        }
        y = a[a[y]];
        visited[x] = 1;
    }while(x != y);

    x = i;
    while(x != y) {
        x = a[x];
        y = a[y];
        visited[y] = 1;
    }

    int first = x;
    x = first;
    do
    {
        visited[x] = 2;
        x = a[x];
    }while(x != first);
}

int main()
{
    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    for(int i = 1; i <= n; i++) {
        if(!visited[i]) {
            Floyd(i);
        }
    }

    for(int i = 1; i <= n; i++) {
        if(visited[i] == 2) {
            answer++;
        }
    }
    cout << answer << '\n';

    return 0;
}
