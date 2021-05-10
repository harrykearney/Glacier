#include <iostream>

#include <map>
#include <regex>
#include <string>
#include <fstream>
#include <stdlib.h>
using namespace std;

map<string, string> stringVariables;
map<string, int> integerVariables;

bool replace(std::string& str, const std::string& from, const std::string& to) {
    size_t start_pos = str.find(from);
    if(start_pos == std::string::npos)
        return false;
    str.replace(start_pos, from.length(), to);
    return true;
}

void printString(const string fullString) {
    string varname = fullString.substr(1, string::npos);
    cout << stringVariables.find(varname)->second;
}

void newStringVariable(const string fullString) {
    string varname;
    string varvalue;

    varname = fullString.substr(6, string::npos);
    varname = varname.substr(0, varname.find("="));
    varname = varname.substr(1, string::npos - 1);
    varname = varname.substr(0, varname.size() - 1);

    varvalue = fullString.substr(fullString.find("\""), fullString.size());
    varvalue = varvalue.substr(1, varvalue.size()-2);

    stringVariables[varname] = varvalue;
}

inline void evaluate(const string fullString) {
    string expression;

    expression = fullString.substr(fullString.find("\""), fullString.size());
    expression = expression.substr(1, expression.size() - 2);
    string newexpression = "python3 evaluate.py \"" + expression + "\"";

    system(newexpression.c_str());

    string answer;
    ifstream expressionFile("evaluation.txt");
    if (expressionFile.is_open()) {
        while (getline(expressionFile, answer)) {
            cout << answer << endl;
        }
    }
}

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
    if (fullString.find("{") != string::npos && fullString.find("}") != string::npos) {
        string varname;
        varname = fullString.substr(fullString.find(" ") + 1, string::npos);

        varname = varname.substr(varname.find("{"), varname.find("}") + 2);
        varname = varname.substr(1, varname.size() - 2);
        varname = varname.substr(0, varname.size() - 1);

        replace(fullString, "{" + varname + "}", stringVariables.find(varname)->second);
        fullString = fullString.substr(11, fullString.size() - 1);
        fullString = fullString.substr(0, fullString.size() - 1);
        cout << fullString << endl;
    } else {
        string content;

        content = fullString.substr(fullString.find("\""), fullString.size());
        content = content.substr(1, content.size() - 2);

        cout << content << endl;
    }
}

void print(string fullString) {
    string content;

    content = fullString.substr(fullString.find("\""), fullString.size());
    content = content.substr(1, content.size()-2);

    cout << content;
}

void newLine() {
    cout << endl;
}

int main(int argc, char* argv[]) {;
    if (endsWith(argv[1], ".xg") == 0) {
        cout << "Glacier Error: File provided is not of .xg file format." << endl;
        exit(1);
    }

    ifstream codeFile(argv[1]);
    string line;

    while (getline (codeFile, line)) {
        if (startsWith(line, "//") || line == "") {}
        else if (startsWith(line, "PRINTLINE")) {
            printLine(line);
        }
        else if (startsWith(line, "PRINT")) {
            print(line);
        }
        else if (startsWith(line, "NEWLINE")) {
            newLine();
        }
        else if (startsWith(line, "EVALUATE")) {
            evaluate(line);
        }
        else if (startsWith(line, "STRING")) {
            newStringVariable(line);
        }
        else if (startsWith(line, "$")) {
            printString(line);
        }
        else {
            cout << "UNKNOWN Command" + line.substr(0, line.find(" ")) << endl;
            exit(1);
        }
}}