build:
	g++ -std=c++11 main.cpp Token.cpp Lexer.cpp Expr.cpp Parser.cpp -o calculator

run: build
	./calculator

clean:
	rm calculator
