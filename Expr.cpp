#include "Expr.h"

//
// Expr class functions
//
Expr::~Expr() {};

//
// Add class functions
//
Add::Add(Expr* lVal, Expr* rVal) {
    this->lVal = lVal;
    this->rVal = rVal;
}

int Add::Eval() {
    if (!lVal || !rVal) {
        return 0;
    }
    return lVal->Eval() + rVal->Eval();
}

//
// Multiply class functions
//
Multiply::Multiply(Expr* lVal, Expr* rVal) {
    this->lVal = lVal;
    this->rVal = rVal;
}

int Multiply::Eval() {
    if (!lVal || !rVal) {
        return 0;
    }
    return lVal->Eval() * rVal->Eval();
}

//
// Integer class functions
//
Integer::Integer(int value) {
    this->value = value;
}

int Integer::Eval() {
    return value;
}