#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <iomanip>

using namespace std;

bool isValidPhoneNumber(const string& number) {
    if (number.size() != 10) return false;
    for (char c : number) {
        if (!isdigit(c)) return false;
    }
    return true;
}

int timeToSeconds(const string& time) {
    int h, m, s;
    sscanf(time.c_str(), "%d:%d:%d", &h, &m, &s);
    return h * 3600 + m * 60 + s;
}

int main() {
    unordered_map<string, int> callsFrom;
    unordered_map<string, int> timeFrom;
    vector<string> callData;
    string line;
    int totalCalls = 0;
    bool allNumbersValid = true;

    while (getline(cin, line) && line != "#") {
        callData.push_back(line);
        stringstream ss(line);
        string type, from, to, date, fromTime, endTime;
        ss >> type >> from >> to >> date >> fromTime >> endTime;

        if (!isValidPhoneNumber(from) || !isValidPhoneNumber(to)) {
            allNumbersValid = false;
        }

        callsFrom[from]++;
        int duration = timeToSeconds(endTime) - timeToSeconds(fromTime);
        timeFrom[from] += duration;
        totalCalls++;
    }

    while (getline(cin, line) && line != "#") {
        stringstream ss(line);
        string query;
        ss >> query;

        if (query == "?check_phone_number") {
            cout << (allNumbersValid ? 1 : 0) << endl;
        } else if (query == "?number_calls_from") {
            string phoneNumber;
            ss >> phoneNumber;
            cout << callsFrom[phoneNumber] << endl;
        } else if (query == "?number_total_calls") {
            cout << totalCalls << endl;
        } else if (query == "?count_time_calls_from") {
            string phoneNumber;
            ss >> phoneNumber;
            cout << timeFrom[phoneNumber] << endl;
        }
    }

    return 0;
}