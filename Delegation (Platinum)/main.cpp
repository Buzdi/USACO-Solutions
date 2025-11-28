#include <fstream>
#include <algorithm>
#include <vector>
#include <cassert>

#define ll long long
#define ull unsigned long long
#define cin fin
#define cout fout

using namespace std;

ifstream fin("deleg.in");
ofstream fout("deleg.out");

const int NMAX = 1e5;

int n;
vector<int> g[NMAX + 1];

bool CanPair(vector<int>& path_lengths, int without_pos, int min_length) {
    if (path_lengths.size() == 1) {
        return true;
    }

    int left = 0, right = path_lengths.size() - 1;
    while (left < right) {
        if (left == without_pos) {
            left++;
        }
        else if (right == without_pos) {
            right--;
        }
        else if (path_lengths[left] + path_lengths[right] < min_length) {
            return false;
        }
        else {
            left++;
            right--;
        }
    }
    return true;
}

int GetPathLengthUp(vector<int>& path_lengths, int min_length) {
    int left = 0, right = path_lengths.size() - 1, pos = -1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (CanPair(path_lengths, mid, min_length)) {
            pos = mid;
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }

    if (pos == -1) {
        return -1;
    }
    return path_lengths[pos];
}

int DFS(int node, int min_length, int dad = 0) {
    vector<int> path_lengths;
    for (int next_node : g[node]) {
        if (next_node != dad) {
            int path_length = DFS(next_node, min_length, node);
            if (path_length == -1) {
                return -1;
            }
            path_lengths.push_back(path_length);
        }
    }
    sort(path_lengths.begin(), path_lengths.end());

    if(node == 1) {
        if(path_lengths.size() % 2 == 1) {
            int last_path = path_lengths.back();
            if(last_path < min_length) {
                return 0;
            }
            path_lengths.pop_back();
            return CanPair(path_lengths, -1, min_length);
        }
        return CanPair(path_lengths, -1, min_length);
    }

    if (path_lengths.size() == 0) {
        return 1;
    }

    if (path_lengths.size() % 2 == 1) {
        int path_length_up = GetPathLengthUp(path_lengths, min_length);
        if(path_length_up == -1) {
            return -1;
        }
        return path_length_up + 1;
    }

    int last_path = path_lengths.back();
    if (last_path >= min_length) {
        path_lengths.pop_back();
        int path_length_up = GetPathLengthUp(path_lengths, min_length);
        if (path_length_up != -1) {
            return path_length_up + 1;
        }
        path_lengths.push_back(last_path);
    }
    return (CanPair(path_lengths, -1, min_length) ? 1 : -1);
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    for (int i = 1; i <= n - 1; i++) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    int left = 1, right = n - 1, answer = -1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (DFS(1, mid) > 0) {
            answer = mid;
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    cout << answer << '\n';

    return 0;
}
