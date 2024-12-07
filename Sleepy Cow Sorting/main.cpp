#include <fstream>

using namespace std;

ifstream cin("sleepy.in");
ofstream cout("sleepy.out");

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

int n, length;
bool stop;
int a[NMAX + 1];
int answer[NMAX + 1];

int main()
{
    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    aib.Initialize(n);
    aib.Update(a[n], 1);
    length = 1;
    for(int i = n - 1; i >= 1 && !stop; i--) {
        if(a[i] < a[i + 1]) {
            aib.Update(a[i], 1);
            length++;
        }
        else {
            stop = true;
        }
    }

    for(int i = 1; i <= n - length; i++) {
        int curent_length = length + i - 1;
        answer[i] = n - curent_length - 1 + aib.Query(a[i] - 1);
        aib.Update(a[i], 1);
    }

    cout << n - length << '\n';
    for(int i = 1; i <= n - length; i++) {
        cout << answer[i];
        if(i < n - length) {
            cout << ' ';
        }
    }

    return 0;
}
