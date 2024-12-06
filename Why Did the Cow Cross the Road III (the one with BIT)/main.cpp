#include <fstream>
#define ll long long

using namespace std;

ifstream cin("circlecross.in");
ofstream cout("circlecross.out");

const int NMAX = 5e4;

struct AIB {
    int n;
    int aib[2 * NMAX + 1];

    void Initialize(int n) {
        this->n = n;
        for(int i = 1; i <= n; i++) {
            aib[i] = 0;
        }
    }

    void Update(int pos, int value) {
        for(int i = pos; i <= n; i += i & (-i)) {
            aib[i] += value;
        }
    }

    int Query(int pos) {
        int answer = 0;
        for(int i = pos; i >= 1; i -= i & (-i)) {
            answer += aib[i];
        }
        return answer;
    }
}aib;

int n;
ll answer;
int a[2 * NMAX + 1];
int pos[NMAX + 1];

int main()
{
    cin >> n;
    for(int i = 1; i <= 2 * n; i++) {
        cin >> a[i];
    }

    aib.Initialize(2 * n);
    for(int i = 1; i <= 2 * n; i++) {
        if(pos[a[i]] == 0) {
            pos[a[i]] = i;
            aib.Update(i, 1);
        }
        else {
            answer += aib.Query(i) - aib.Query(pos[a[i]]);
            aib.Update(pos[a[i]], -1);
        }
    }
    cout << answer << '\n';

    return 0;
}
