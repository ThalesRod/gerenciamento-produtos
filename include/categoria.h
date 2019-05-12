#ifndef CATEGORIA_H
#define CATEGORIA_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include <stdio.h>

typedef unsigned char byte;


class Categoria {

	unsigned short id;
	std::string nome;

	public:
		// Getters
		unsigned short get_id();
		std::string get_nome();

		// Setters
		void set_id(unsigned short novoId);
		void set_append_nome(char c);

		void lerDadosCategoria(FILE *arquivoID);
		void exibeDadosCategoria();		
};

class CategoriaEntrada {

	char lapide;
	unsigned short tamanhoVetorDeBytes;
	std::vector<byte> vetorDeBytes;

	public:
		unsigned long int armazenaCategoria(FILE *arquivoDados, Categoria *categoria);
		static Categoria* recuperaCategoria(FILE *arquivoDados, unsigned long int endereco);
	
	private:
		std::vector<byte> categoriaParaBytes(Categoria *categoria);
		static Categoria* bytesParaCategoria(std::vector<byte> vetorDeBytes);
};

#endif