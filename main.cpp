#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace Token {

    enum TokenType {integer, add, multiply, openParen, closeParen};

    class Token {
        public:
        virtual ~Token() {};
        virtual void print() = 0;
        virtual TokenType getType() = 0;
        virtual int getValue() {
            return 0;
        }
    };

    class Integer : public Token {
        public:
        Integer(int value) {
            this->value = value;
        }
        void print() {
            cout << value;
        }
        TokenType getType() {
            return integer;
        }
        int getValue() {
            return value;
        }

        private:
        int value;
    };

    class Add : public Token {
        public:
        void print() {cout << "+";}
        TokenType getType() {
            return add;
        }
    };

    class Multiply : public Token {
        public:
        void print() {cout << "*";}
        TokenType getType() {
            return multiply;
        }
    };

    class OpenParen : public Token {
        public:
        void print() {cout << "(";}
        TokenType getType() {
            return openParen;
        }
    };

    class CloseParen : public Token {
        public:
        void print() {cout << ")";}
        TokenType getType() {
            return closeParen;
        }
    };
};

class Lexer {
    public:
    ~Lexer() {
        tokens.clear();
    }

    void Tokenize(string input) {
        tokens.clear();
        currentToken = 0;
        int pos = 0;
        while(pos != input.length()) {
            if (input[pos] == ' ') {
                pos++;
            } else if (isdigit(input[pos])) {
                int startPos = pos++;
                while(pos != input.length() && isdigit(input[pos])) {
                    pos++;
                }
                tokens.push_back(new Token::Integer(stoi(input.substr(startPos, pos - startPos))));
            } else if (input[pos] == '+') {
                tokens.push_back(new Token::Add());
                pos++;
            } else if (input[pos] == '*') {
                tokens.push_back(new Token::Multiply());
                pos++;
            } else if (input[pos] == '(') {
                tokens.push_back(new Token::OpenParen());
                pos++;
            } else if (input[pos] == ')') {
                tokens.push_back(new Token::CloseParen());
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

        for(Token::Token* token : tokens) {
            token->print();
        }
        cout << endl;
    }

    void readToken() {
        if (tokens.size() == 0) {
            return;
        }
        currentToken++;
    }

    bool currentTokenIs(Token::TokenType type) {
        if (tokens.size() == 0 || currentToken >= tokens.size()) {
            return false;
        }
        return type == tokens[currentToken]->getType();
    }

    int currentTokenValue() {
        return tokens[currentToken]->getValue();
    }

    bool allTokensRead() {
        return currentToken >= tokens.size();
    }

    private:
    int currentToken = 0;
    vector<Token::Token*> tokens;
};

class Expr {
    public:
    virtual ~Expr() {};
    virtual int Eval() = 0;
};

class Add : public Expr {
    public:
    Add(Expr* lVal, Expr* rVal) {
        this->lVal = lVal;
        this->rVal = rVal;
    }

    int Eval() {
        if (!lVal || !rVal) {
            return 0;
        }
        return lVal->Eval() + rVal->Eval();
    }

    private:
    Expr* lVal;
    Expr* rVal;
};

class Multiply : public Expr {
    public:
    Multiply(Expr* lVal, Expr* rVal) {
        this->lVal = lVal;
        this->rVal = rVal;
    }

    int Eval() {
        if (!lVal || !rVal) {
            return 0;
        }
        return lVal->Eval() * rVal->Eval();
    }

    private:
    Expr* lVal;
    Expr* rVal;
};

class Integer : public Expr {
    public:
    Integer(int value) {
        this->value = value;
    }
    int Eval() {
        return value;
    }

    private:
    int value;
};

// The grammar for this parser is as follows:
// E -> TE`
// E -> T
// E`-> + TE`
// E`-> (END)
// T -> NT`
// T -> N
// T`-> * NT`
// T`-> (END)
// N -> Int
// N -> (E)
// In the ParseE and ParseT functions, the while loop accounts for E` and T`
// in the grammar. It is what allows it to repeat and keep consuming addition
// or multiplication symbols.
class Parser {
    public:
    void Parse(Lexer *lexer) {
        e = ParseE(lexer);
        if(!e || !lexer->allTokensRead()) {
            cout << "unable to parse expression" << endl;
            e = NULL;
        }
    }

    Expr* ParseE(Lexer *lexer) {
        Expr* lVal = ParseT(lexer);
        if (!lVal) {
            return NULL;
        }
        while(true) {
            if (lexer->currentTokenIs(Token::add)) {
                lexer->readToken();
                Expr *rVal = ParseT(lexer);
                if (!rVal) {
                    return NULL;
                }
                lVal = new Add(lVal, rVal);
            } else {
                return lVal;
            }
        }
    }

    Expr* ParseT(Lexer *lexer) {
        Expr* lVal = ParseN(lexer);
        if (!lVal) {
            return NULL;
        }
        while(true) {
            if (lexer->currentTokenIs(Token::multiply)) {
                lexer->readToken();
                Expr* rVal = ParseN(lexer);
                if (!rVal) {
                    return NULL;
                }
                lVal = new Multiply(lVal, rVal);
            } else {
                return lVal;
            }
        }
    }

    Expr* ParseN(Lexer *lexer) {
        if (lexer->currentTokenIs(Token::integer)) {
            Expr* n = new Integer(lexer->currentTokenValue());
            lexer->readToken();
            return n;
        } else if (lexer->currentTokenIs(Token::openParen)) {
            lexer->readToken();
            Expr* n = ParseE(lexer);
            if (!n) {
                return NULL;
            }
            if (lexer->currentTokenIs(Token::closeParen)) {
                lexer->readToken();
            }
            return n;
        }
        return NULL;
    }

    void Eval() {
        if (!e) {
            return;
        }
        cout << e->Eval() << endl;
    }

    private:
    Expr* e = NULL;
};

int main(int argc, char* argv[]) {
    std::string input;
    Lexer lexer = Lexer();
    Parser parser = Parser();

    while(1) {
        cout << "Enter expression: ";
        getline(std::cin, input);
        lexer.Tokenize(input);
        parser.Parse(&lexer);
        parser.Eval();
    }
}