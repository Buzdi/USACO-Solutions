#include <fstream>
#define ll long long

using namespace std;

ifstream cin("mincross.in");
ofstream cout("mincross.out");

const int NMAX = 1e5;

struct AIB {
    int n;
    int aib[NMAX + 1];

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
int a[NMAX + 1], b[NMAX + 1];
int pos_b[NMAX + 1];

ll Solve(int a[], int b[]) {
    for(int i = 1; i <= n; i++) {
        pos_b[b[i]] = i;
    }

    aib.Initialize(n);
    ll answer = 0;
    for(int i = 1; i <= n; i++) {
        answer += i - 1 - aib.Query(pos_b[a[i]]);
        aib.Update(pos_b[a[i]], 1);
    }

    ll min_answer = answer;
    for(int i = n; i >= 1; i--) {
        answer = answer + (pos_b[a[i]] - 1) - (n - pos_b[a[i]]);
        min_answer = min(min_answer, answer);
    }
    return min_answer;
}

int main()
{
    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int i = 1; i <= n; i++) {
        cin >> b[i];
    }
    cout << min(Solve(a, b), Solve(b, a)) << '\n';

    return 0;
}
