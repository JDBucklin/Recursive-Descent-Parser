// This file contains the implemenation of the Parser class

#include "Parser.h"

using namespace std;

// Parse parses mathematical expression
// Parameters:
// lexer: lexer that has already tokenized a mathematical expression
void Parser::Parse(Lexer *lexer) {
    e = ParseE(lexer);
    if (!e) {
        cout << "unable to parse expression" << endl;
    } if (!lexer->allTokensRead()) {
        cout << "unable to parse expression" << endl;
        delete e;
        e = NULL;
    }
}

// ParseE parses the addition part of math expression
// Parameters:
// lexer: lexer that has already tokenized a mathematical expression
Expr* Parser::ParseE(Lexer *lexer) {
    Expr* lVal = ParseT(lexer);
    if (!lVal) {
        return NULL;
    }
    while(true) {
        if (lexer->currentTokenIs(Token::add)) {
            lexer->readToken();
            Expr *rVal = ParseT(lexer);
            if (!rVal) {
                if (lVal) {
                    delete lVal;
                }
                return NULL;
            }
            lVal = new Add(lVal, rVal);
        } else {
            return lVal;
        }
    }
}

// ParseT parses the multiplication part of math expression
// Parameters:
// lexer: lexer that has already tokenized a mathematical expression
Expr* Parser::ParseT(Lexer *lexer) {
    Expr* lVal = ParseN(lexer);
    if (!lVal) {
        return NULL;
    }
    while(true) {
        if (lexer->currentTokenIs(Token::multiply)) {
            lexer->readToken();
            Expr* rVal = ParseN(lexer);
            if (!rVal) {
                if (lVal) {
                    delete lVal;
                }
                return NULL;
            }
            lVal = new Multiply(lVal, rVal);
        } else {
            return lVal;
        }
    }
}

// ParseN parses the integer and parenthesis part of math expression
// Parameters:
// lexer: lexer that has already tokenized a mathematical expression
Expr* Parser::ParseN(Lexer *lexer) {
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
        // Get rid of closing paren
        if (!lexer->currentTokenIs(Token::closeParen)) {
            return NULL;
        }
        lexer->readToken();
        return n;
    }
    return NULL;
}

// Eval evaluates parse tree of mathematical expression
void Parser::Eval() {
    if (!e) {
        return;
    }
    cout << e->Eval() << endl;
}