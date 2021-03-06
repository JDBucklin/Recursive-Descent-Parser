// This file contains the declaration of the Expr classes

class Expr {
    public:
    virtual ~Expr();
    virtual int Eval() = 0;
};

class Add : public Expr {
    public:
    Add(Expr* lVal, Expr* rVal);
    ~Add();
    int Eval();

    private:
    Expr* lVal;
    Expr* rVal;
};

class Multiply : public Expr {
    public:
    Multiply(Expr* lVal, Expr* rVal);
    ~Multiply();
    int Eval();

    private:
    Expr* lVal;
    Expr* rVal;
};

class Integer : public Expr {
    public:
    Integer(int value);
    int Eval();

    private:
    int value;
};