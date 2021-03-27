// This file contains the implemenation of the Lexer class

#include "Lexer.h"

using namespace std;

// ~Lexer clears all elements stored in tokens vector
// Note: The documenation for vector.clear() states that
// it calls the deconstructor for the objects stored in the
// vector. So there is an assumption here that is how it
// works. If it isn't, then there should be a loop to delete
// all elements in the vector. Valgrind doesn't work on my machine
// so I can't check for memory leaks locally and I'm trusting it.
Lexer::~Lexer() {
    tokens.clear();
}

// Tokenize scans through the input string and converts each element
// to a token so that it can be parsed. If an invalid token is given
// as input then all tokens that have been read are deleted and the
// user is notified.
// parameters:
// input: an input string that contains a mathematical expression
//        input should only consist of numbers, spaces, (, ), +, *
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

// printTokens prints the tokens read in from Tokenize
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

// readToken advances the currentToken counter to be the index
// of the next token.
void Lexer::readToken() {
    if (tokens.size() == 0) {
        return;
    }
    currentToken++;
}

// currentTokenIs returns true if the index of currentToken matches
// the passed in token type, false otherwise.
// parameters:
// type: the token type to compare currentToken to
bool Lexer::currentTokenIs(Token::TokenType type) {
    if (tokens.size() == 0 || currentToken >= tokens.size()) {
        return false;
    }
    return type == tokens[currentToken]->getType();
}

// currentTokenValue returns the integer value for a token
// This will only return a non-zero value if the token is of
// type integer.
int Lexer::currentTokenValue() {
    return tokens[currentToken]->getValue();
}

// allTokensRead returns true if every token in the tokens vector
// have been read, false otherwise.
bool Lexer::allTokensRead() {
    return currentToken >= tokens.size();
}