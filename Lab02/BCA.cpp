#include <bits/stdc++.h>
using namespace std;

int m, n;
vector<vector<int>> preferences;
vector<pair<int, int>> conflicts;
vector<int> courseAssignment;
int maxLoad = INT_MAX;
vector<vector<bool>> conflictMatrix;

bool canAssign(int teacher, int course) {
    for (int i = 0; i < n; ++i) {
        if (courseAssignment[i] == teacher && conflictMatrix[i + 1][course]) {
            return false;
        }
    }
    return find(preferences[teacher].begin(), preferences[teacher].end(), course) != preferences[teacher].end();
}

void backtrack(int courseIndex, vector<int> &load, int currentMaxLoad) {
    if (currentMaxLoad >= maxLoad) return; // Pruning

    if (courseIndex == n) {
        maxLoad = min(maxLoad, currentMaxLoad);
        return;
    }

    for (int teacher = 0; teacher < m; ++teacher) {
        if (canAssign(teacher, courseIndex + 1)) {
            courseAssignment[courseIndex] = teacher;
            load[teacher]++;
            backtrack(courseIndex + 1, load, max(currentMaxLoad, load[teacher]));
            load[teacher]--;
            courseAssignment[courseIndex] = -1;
        }
    }
}

int main() {
    cin >> m >> n;
    preferences.resize(m);
    courseAssignment.resize(n, -1);
    conflictMatrix.resize(n + 1, vector<bool>(n + 1, false));

    for (int i = 0; i < m; ++i) {
        int k;
        cin >> k;
        preferences[i].resize(k);
        for (int j = 0; j < k; ++j) {
            cin >> preferences[i][j];
        }
    }

    int k;
    cin >> k;
    for (int i = 0; i < k; ++i) {
        int c1, c2;
        cin >> c1 >> c2;
        conflictMatrix[c1][c2] = true;
        conflictMatrix[c2][c1] = true;
    }

    vector<int> load(m, 0);
    backtrack(0, load, 0);

    if (maxLoad == INT_MAX) {
        cout << -1 << endl;
    } else {
        cout << maxLoad << endl;
    }

    return 0;
}
