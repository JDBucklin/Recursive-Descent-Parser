// This file contains the implemenation of the Expr classes

#include "Expr.h"

//
// Expr class functions
//
Expr::~Expr() {};

//
// Add class functions
//
// Constructor
// parameters:
// lVal, rVal: expressions to add together
Add::Add(Expr* lVal, Expr* rVal) {
    this->lVal = lVal;
    this->rVal = rVal;
}

// Destructor
Add::~Add() {
    if (this->lVal) {
        delete this->lVal;
    }
    if (this->rVal) {
        delete this->rVal;
    }
}

// Eval adds the result of two expressions
// returns 0 if either expression is empty
int Add::Eval() {
    if (!lVal || !rVal) {
        return 0;
    }
    return lVal->Eval() + rVal->Eval();
}

//
// Multiply class functions
//
// Constructor
// parameters:
// lVal, rVal: expressions to multiply together
Multiply::Multiply(Expr* lVal, Expr* rVal) {
    this->lVal = lVal;
    this->rVal = rVal;
}

// Destructor
Multiply::~Multiply() {
    if (this->lVal) {
        delete this->lVal;
    }
    if (this->rVal) {
        delete this->rVal;
    }
}

// Eval multiplies the result of two expressions
// returns 0 if either expression is empty
int Multiply::Eval() {
    if (!lVal || !rVal) {
        return 0;
    }
    return lVal->Eval() * rVal->Eval();
}

//
// Integer class functions
//
// Constructor
// parameters:
// value: integer value
Integer::Integer(int value) {
    this->value = value;
}

// Eval returns the value stored in the Integer object
int Integer::Eval() {
    return value;
}