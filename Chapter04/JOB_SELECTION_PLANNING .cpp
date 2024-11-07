#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct Job {
    int deadline;
    int profit;
};

bool compare(Job a, Job b) {
    return a.profit > b.profit;
}

int main() {
    int n;
    cin >> n;
    vector<Job> jobs(n);
    int maxDeadline = 0;

    for (int i = 0; i < n; ++i) {
        cin >> jobs[i].deadline >> jobs[i].profit;
        maxDeadline = max(maxDeadline, jobs[i].deadline);
    }

    sort(jobs.begin(), jobs.end(), compare);

    vector<bool> slot(maxDeadline + 1, false);
    int totalProfit = 0;

    for (const auto& job : jobs) {
        for (int j = job.deadline; j > 0; --j) {
            if (!slot[j]) {
                slot[j] = true;
                totalProfit += job.profit;
                break;
            }
        }
    }

    cout << totalProfit << endl;
    return 0;
}
