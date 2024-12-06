#include <fstream>
#define ll long long

using namespace std;

ifstream cin("haircut.in");
ofstream cout("haircut.out");

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

int n, ind;
ll total_inversions;
int a[NMAX + 1];
ll inversions[NMAX + 2];
ll answer[NMAX + 1];

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i]++;
    }

    aib.Initialize(n + 1);
    for(int i = 1; i <= n; i++) {
        inversions[a[i]] += i - 1 - aib.Query(a[i]);
        aib.Update(a[i], 1);
    }

    for(int i = 1; i <= n + 1; i++) {
        total_inversions += inversions[i];
    }

    for(int i = n; i >= 1; i--) {
        total_inversions -= inversions[i];
        answer[++ind] = total_inversions;
    }

    for(int i = n; i >= 1; i--) {
        cout << answer[i] << '\n';
    }

    return 0;
}
