#include <iostream>
#include <regex>
#include <string>
#include <functional>

using namespace std;

void compute(string& input, regex pattern, char opp) {
    smatch match;
    function<int(int, int)> operation;

    switch(opp) {
    case '+': {
        operation = [] (int op1, int op2) {
            return op1 + op2;
        };
        break;
    }
    case '*': {
        operation = [] (int op1, int op2) {
            return op1 * op2;
        };
        break;
    }
    };

    while(regex_search(input, match, pattern)) {
        int op1 = stoi(match[1].str());
        int op2 = stoi(match[2].str());
        string result = to_string(operation(op1, op2));
        input.replace(match.position(), match.length(), result);
        cout << input << endl;
    }
    return;
}

int main(int argc, char* argv[]) {
    std::smatch match;
    std::regex add("(\\d+)\\s*\\+\\s*(\\d+)");
    std::regex mult("(\\d+)\\s*\\*\\s*(\\d+)");
    std::string input;

    while(1) {
        cout << "Enter expression: ";
        getline(std::cin, input);
        compute(input, mult, '*');
        compute(input, add, '+');
        // input = regex_replace(input, std::regex("\\("), "");
        // input = regex_replace(input, std::regex("\\)"), "");
        // cout << input << endl;
        // compute(input, mult, '*');
        // compute(input, add, '+');
    }
}