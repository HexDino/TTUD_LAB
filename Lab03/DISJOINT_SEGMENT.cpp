#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<pair<int, int>> segments(n);

    for (int i = 0; i < n; ++i) {
        cin >> segments[i].first >> segments[i].second;
    }

    sort(segments.begin(), segments.end(), [](pair<int, int> a, pair<int, int> b) {
        return a.second < b.second;
    });

    int res = 0;
    int last = -1;

    for (const auto& segment : segments) {
        if (segment.first > last) {
            res++;
            last = segment.second;
        }
    }

    cout << res << endl;

    return 0;
}
