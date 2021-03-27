#include "Parser.h"

using namespace std;

void Parser::Parse(Lexer *lexer) {
    e = ParseE(lexer);
    if(!e || !lexer->allTokensRead()) {
        cout << "unable to parse expression" << endl;
        e = NULL;
    }
}

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
                return NULL;
            }
            lVal = new Add(lVal, rVal);
        } else {
            return lVal;
        }
    }
}

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
                return NULL;
            }
            lVal = new Multiply(lVal, rVal);
        } else {
            return lVal;
        }
    }
}

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
        if (lexer->currentTokenIs(Token::closeParen)) {
            lexer->readToken();
        }
        return n;
    }
    return NULL;
}

void Parser::Eval() {
    if (!e) {
        return;
    }
    cout << e->Eval() << endl;
}