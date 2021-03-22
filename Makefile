build:
	g++ -std=c++11 main.cpp -o calculator

run: build
	./calculator

clean:
	rm calculator
