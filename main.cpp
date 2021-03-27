#include <iostream>
#include <string>
#include <vector>
#include "Parser.h"

using namespace std;

int main(int argc, char* argv[]) {
    string input;
    Lexer lexer = Lexer();
    Parser parser = Parser();

    while(true) {
        cout << "Enter expression: ";
        getline(cin, input);
        lexer.Tokenize(input);
        parser.Parse(&lexer);
        parser.Eval();
    }
}