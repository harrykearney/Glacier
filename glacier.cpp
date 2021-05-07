#include <iostream>
#include <string>
#include <fstream>
using namespace std;

inline bool endsWith(string const &value, string const &ending) {
    if (ending.size() > value.size()) return false;
    return equal(ending.rbegin(), ending.rend(), value.rbegin());
}

inline bool startsWith(string const &value, string const &ending) {
    if (value.find(ending) == 0) {
        return true;
    } else {
        return false;
    }
}

void printLine(string fullString) {
    string content;

    content = fullString.substr(fullString.find("\""), fullString.size());
    content = content.substr(1, content.size()-2);

    cout << content << endl;
}

int main(int argc, char* argv[]) {;
    if (endsWith(argv[1], ".xg") == 0) {
        cout << "Glacier Error: File provided is not of .xg file format." << endl;
        exit(1);
    }

    ifstream codeFile(argv[1]);
    string line;

    while (getline (codeFile, line)) {
        if (startsWith(line, "//")) {}
        else if (startsWith(line, "PRINTLINE")) {
            printLine(line);
    }
}}