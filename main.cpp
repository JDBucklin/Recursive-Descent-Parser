#include <iostream>
#include <regex>

using namespace std;

class Expr {
    public:
    virtual int Eval() = 0;
};

class Number : public Expr {
    public:
    Number(int value) {
        this->value = value;
    }

    int Eval() {
        return value;
    }

    private:
    int value;
};

class Add : public Expr {
    public:
    Add(Expr* lval, Expr* rval) {
        this->lval = lval;
        this->rval = rval;
    }

    int Eval() {
        return lval->Eval() + rval->Eval();
    }

    private:
    Expr* lval;
    Expr* rval;
};


int main(int argc, char* argv[]) {
    Expr *temp = new Add(new Number(5), new Add(new Number(7), new Number(9)));
    cout << temp->Eval() << endl;
}