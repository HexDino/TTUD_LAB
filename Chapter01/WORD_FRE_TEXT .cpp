#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <cctype>
#include <algorithm>

using namespace std;

string to_lowercase(const string& s) {
    string result = s;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

int main() {
    map<string, int> word_count;
    string line, word;

    while (getline(cin, line)) {
        istringstream iss(line);
        while (iss >> word) {
            word.erase(word.begin(), find_if(word.begin(), word.end(), [](unsigned char ch) {
                return isalnum(ch);
            }));
            word.erase(find_if(word.rbegin(), word.rend(), [](unsigned char ch) {
                return isalnum(ch);
            }).base(), word.end());

            if (!word.empty()) {
                word_count[to_lowercase(word)]++;
            }
        }
    }

    for (const auto& pair : word_count) {
        cout << pair.first << " " << pair.second << endl;
    }

    return 0;
}
