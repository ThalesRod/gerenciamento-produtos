#ifndef COMPRA_H
#define COMPRA_H

#include "../include/crudClientes.h"
#include "../include/crudProdutos.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include <stdio.h>

typedef unsigned char byte;


class Compra {

	unsigned short id;
	std::string dataCompra;
	float preco;
	unsigned short idCliente;
	unsigned short idProduto;
	unsigned short quantidadeProduto;

	public:
		// Getters
		unsigned short get_id();
		std::string get_dataCompra();
		float get_preco();
		unsigned short get_idCliente();
		unsigned short get_idProduto();
		unsigned short get_quantidadeProduto();
		
		// Setters
		void set_id(unsigned short novoId);
		void set_preco(float novoPreco);
		void set_append_dataCompra(char c);
		void set_idCliente(unsigned short novoId);
		void set_idProduto(unsigned short novoId);
		void set_quantidadeProduto(unsigned short novaQuantidade);
		
		void lerDadosCompra(FILE *arquivoID);
		void exibeDadosCompra(FILE *arquivoIndiceClientes, FILE *arquivoDadosClientes, FILE *arquivoIndice, FILE *arquivoDados, FILE *arquivoIndiceCategorias, FILE *arquivoDadosCategorias);
};

class CompraEntrada {

	char lapide;
	unsigned short tamanhoVetorDeBytes;
	std::vector<byte> vetorDeBytes;

	public:
		unsigned long int armazenaCompra(FILE *arquivoDados, Compra *compra);
		static Compra* recuperaCompra(FILE *arquivoDados, unsigned long int endereco);
	
	private:
		std::vector<byte> compraParaBytes(Compra* compra);
		void floatBytesCopy(float paramFloat, std::vector<byte> &vetorDeBytes);
		static Compra* bytesParaCompra(std::vector<byte> vetorDeBytes);
};

#endif