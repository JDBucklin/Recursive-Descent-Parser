// This file contains the implemenation of the Token classes

#include <iostream>
#include "Token.h"

using namespace std;

namespace Token {
    //
    // Token class functions
    //
    // Destructor
    Token::~Token() {};

    // getValue returns the integer value of a token
    // this is meant to be overriden in the Integer class
    int Token::getValue() {
        return 0;
    }

    //
    // Integer class functions
    //
    // Constructor
    // params:
    // value: integer value to store
    Integer::Integer(int value) {
        this->value = value;
    }

    // print prints out the stored integer value
    void Integer::print() {
        cout << value;
    }

    // getType returns token type
    TokenType Integer::getType() {
        return integer;
    }

    // getValue returns value of integer
    int Integer::getValue() {
        return value;
    }

    //
    // Add class functions
    //
    // print prints token symbol
    void Add::print() {
        cout << "+";
    }

    // getType returns token type
    TokenType Add::getType() {
        return add;
    }

    //
    // Multiply class functions
    //
    // print prints token symbol
    void Multiply::print() {
        cout << "*";
    }

    // getType returns token type
    TokenType Multiply::getType() {
        return multiply;
    }

    //
    // OpenParen class functions
    //
    // print prints token symbol
    void OpenParen::print() {
        cout << "(";
    }

    // getType returns token type
    TokenType OpenParen::getType() {
        return openParen;
    }

    //
    // CloseParen class functions
    //
    // print prints token symbol
    void CloseParen::print() {
        cout << ")";
    }

    // getType returns token type
    TokenType CloseParen::getType() {
        return closeParen;
    };
};