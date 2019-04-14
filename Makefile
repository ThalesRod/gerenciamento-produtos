all: 

compile: src/main.cpp
	g++ -c -Wall src/*.cpp
	mv *.o build/
	g++ -g -Wall build/*.o -o bin/gerenciamentoProdutos

run: bin/gerenciamentoProdutos
	./bin/gerenciamentoProdutos
