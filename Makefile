all: 

compile: src/main.cpp
	g++ -c -Wall -std=c++11 src/*.cpp
	mv *.o build/
	g++ -g -Wall build/*.o -o bin/gerenciamentoProdutos

run: bin/gerenciamentoProdutos
	./bin/gerenciamentoProdutos
