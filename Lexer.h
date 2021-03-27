
#include <iostream>
#include <vector>
#include <string>
#include "Token.h"

class Lexer {
    public:
    ~Lexer();
    void Tokenize(std::string input);
    void printTokens();
    void readToken();
    bool currentTokenIs(Token::TokenType type);
    int currentTokenValue();
    bool allTokensRead();

    private:
    int currentToken = 0;
    std::vector<Token::Token*> tokens;
};