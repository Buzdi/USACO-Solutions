#include <iostream>
#include <cmath>
#include <set>
#include <map>
#include <vector>
#include <algorithm>
#define ll long long

using namespace std;

struct Interval {
    int left, right;
};

bool cmpIntervals(const Interval &a, const Interval &b) {
    if(a.right < b.right) {
        return true;
    }
    if(a.right == b.right && a.left < b.left) {
        return true;
    }
    return false;
}

void test_case() {
    int n;
    cin >> n;

    vector<Interval> intervals(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> intervals[i].left >> intervals[i].right;
    }
    sort(intervals.begin() + 1, intervals.end(), cmpIntervals);

    set<int> s;
    map<int, bool> mp;
    s.insert(1);
    for(int i = 1; i <= n; i++) {
        if(s.find(intervals[i].left) == s.end() && mp.find(intervals[i].left) == mp.end()) {
            mp[intervals[i].left] = 1;
            if(mp.find(intervals[i].left + 1) == mp.end()) {
                s.insert(intervals[i].left + 1);
            }
        }
        else {
            auto it = s.lower_bound(intervals[i].left);
            if(*it > intervals[i].right) {
                cout << "NO" << '\n';
                return;
            }
            int value = *it;
            s.erase(it);
            mp[value] = 1;
            if(mp.find(value + 1) == mp.end()) {
                s.insert(value + 1);
            }
        }
    }
    cout << "YES" << '\n';
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T;
    cin >> T;
    while(T--) {
        test_case();
    }

    return 0;
}
