#ifndef PRODUTO_H
#define PRODUTO_H

#include "../include/crudCategorias.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include <stdio.h>

typedef unsigned char byte;


class Produto {

	unsigned short id;
	std::string nome;
	std::string descricao;
	float preco;
	unsigned short idCategoria;

	public:
		// Getters
		unsigned short get_id();
		std::string get_nome();
		std::string get_descricao();
		float get_preco();
		unsigned short get_idCategoria();
		
		// Setters
		void set_id(unsigned short novoId);
		void set_preco(float novoPreco);
		void set_append_nome(char c);
		void set_append_descricao(char c);
		void set_idCategoria(unsigned short novoId);
		
		void lerDadosProduto(FILE *arquivoID);
		void exibeDadosProduto(FILE *arquivoIndiceCategorias, FILE *arquivoDadosCategorias);		
};

class ProdutoEntrada {

	char lapide;
	unsigned short tamanhoVetorDeBytes;
	std::vector<byte> vetorDeBytes;

	public:
		unsigned long int armazenaProduto(FILE *arquivoDados, Produto *produto);
		static Produto* recuperaProduto(FILE *arquivoDados, unsigned long int endereco);
	
	private:
		std::vector<byte> produtoParaBytes(Produto* produto);
		void floatBytesCopy(float paramFloat, std::vector<byte> &vetorDeBytes);
		static Produto* bytesParaProduto(std::vector<byte> vetorDeBytes);
};

#endif