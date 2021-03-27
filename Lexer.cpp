#include "Lexer.h"

using namespace std;

Lexer::~Lexer() {
    tokens.clear();
}

void Lexer::Tokenize(string input) {
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

void Lexer::printTokens() {
    if (tokens.empty()) {
        cout << "no tokens to print" << endl;
        return;
    }

    for(Token::Token* token : tokens) {
        token->print();
    }
    cout << endl;
}

void Lexer::readToken() {
    if (tokens.size() == 0) {
        return;
    }
    currentToken++;
}

bool Lexer::currentTokenIs(Token::TokenType type) {
    if (tokens.size() == 0 || currentToken >= tokens.size()) {
        return false;
    }
    return type == tokens[currentToken]->getType();
}

int Lexer::currentTokenValue() {
    return tokens[currentToken]->getValue();
}

bool Lexer::allTokensRead() {
    return currentToken >= tokens.size();
}