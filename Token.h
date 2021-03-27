// This file contains the declaration of the Token classes

namespace Token {

    enum TokenType {integer, add, multiply, openParen, closeParen};

    class Token {
        public:
        virtual ~Token();
        virtual void print() = 0;
        virtual TokenType getType() = 0;
        virtual int getValue();
    };

    class Integer : public Token {
        public:
        Integer(int value);
        void print();
        TokenType getType();
        int getValue();

        private:
        int value;
    };

    class Add : public Token {
        public:
        void print();
        TokenType getType();
    };

    class Multiply : public Token {
        public:
        void print();
        TokenType getType();
    };

    class OpenParen : public Token {
        public:
        void print();
        TokenType getType();
    };

    class CloseParen : public Token {
        public:
        void print();
        TokenType getType();
    };
};