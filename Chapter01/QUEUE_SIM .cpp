#include <iostream>
#include <queue>
#include <string>
#include <sstream>
using namespace std;

int main() {
    queue<int> q;  
    string line;
    while (getline(cin, line) && line != "#") {
        istringstream iss(line);
        string operation;
        iss >> operation;
        if (operation == "PUSH") {
            int v;
            iss >> v;
            q.push(v);
        }
        else if (operation == "POP") { 
            if (q.empty()) {
                cout << "NULL\n";
            }
            else {
                cout << q.front() << '\n'; 
                q.pop();
            }
        }
    }
    return 0;
}
