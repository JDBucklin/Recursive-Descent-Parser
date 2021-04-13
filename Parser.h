// This file contains the declaration of the Parser class

#include "Lexer.h"
#include "Expr.h"

// The grammar for this parser:
// E -> TE`
// E -> T
// E`-> + TE`
// E`-> END
// T -> NT`
// T -> N
// T`-> * NT`
// T`-> END
// N -> Int
// N -> (E)
// In the ParseE and ParseT functions, the while loop accounts for E` and T`
// in the grammar. It is what allows it to repeat and keep consuming addition
// or multiplication symbols.
class Parser {
    public:
    void Parse(Lexer *lexer);
    void Eval();

    private:
    Expr* ParseE(Lexer *lexer);
    Expr* ParseT(Lexer *lexer);
    Expr* ParseN(Lexer *lexer);
    Expr* e = NULL;
};