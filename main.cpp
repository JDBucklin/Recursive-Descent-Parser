#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Token {
    public:
    virtual ~Token() {};
    virtual void print() = 0;
};

class Integer : public Token {
    public:
    Integer(int value) {
        this->value = value;
    }
    void print() {
        cout << value;
    }
    private:
    int value;
};

class Add : public Token {
    public:
    void print() {cout << "+";}
};

class Multiply : public Token {
    public:
    void print() {cout << "*";}
};

class OpenParen : public Token {
    public:
    void print() {cout << "(";}
};

class CloseParen : public Token {
    public:
    void print() {cout << ")";}
};

class Lexer {
    public:
    ~Lexer() {
        tokens.clear();
    }

    void Tokenize(string input) {
        tokens.clear();
        int pos = 0;
        while(pos != input.length()) {
            if (input[pos] == ' ') {
                pos++;
            } else if (isdigit(input[pos])) {
                int startPos = pos++;
                while(pos != input.length() && isdigit(input[pos])) {
                    pos++;
                }
                tokens.push_back(new Integer(stoi(input.substr(startPos, pos - startPos))));
            } else if (input[pos] == '+') {
                tokens.push_back(new Add());
                pos++;
            } else if (input[pos] == '*') {
                tokens.push_back(new Multiply());
                pos++;
            } else if (input[pos] == '(') {
                tokens.push_back(new OpenParen());
                pos++;
            } else if (input[pos] == ')') {
                tokens.push_back(new CloseParen());
                pos++;
            } else {
                cout << "unrecognized character in input: " << input[pos] << endl;
                tokens.clear();
                break;
            }
        }
    }

    void printTokens() {
        if (tokens.empty()) {
            cout << "no tokens to print" << endl;
            return;
        }

        for(Token* token : tokens) {
            token->print();
        }
        cout << endl;
    }

    private:
    vector<Token*> tokens;
};

int main(int argc, char* argv[]) {
    std::string input;
    Lexer lexer = Lexer();

    while(1) {
        cout << "Enter expression: ";
        getline(std::cin, input);
        lexer.Tokenize(input);
        lexer.printTokens();
    }
}