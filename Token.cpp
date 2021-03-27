#include <iostream>
#include "Token.h"

using namespace std;

namespace Token {
    //
    // Token class functions
    //
    Token::~Token() {};
    int Token::getValue() {
        return 0;
    }

    //
    // Integer class functions
    //
    Integer::Integer(int value) {
        this->value = value;
    }

    void Integer::print() {
        cout << value;
    }

    TokenType Integer::getType() {
        return integer;
    }

    int Integer::getValue() {
        return value;
    }

    //
    // Add class functions
    //
    void Add::print() {
        cout << "+";
    }

    TokenType Add::getType() {
        return add;
    }

    //
    // Multiply class functions
    //
    void Multiply::print() {
        cout << "*";
    }

    TokenType Multiply::getType() {
        return multiply;
    }

    //
    // OpenParen class functions
    //
    void OpenParen::print() {
        cout << "(";
    }

    TokenType OpenParen::getType() {
        return openParen;
    }

    //
    // CloseParen class functions
    //
    void CloseParen::print() {
        cout << ")";
    }

    TokenType CloseParen::getType() {
        return closeParen;
    };
};