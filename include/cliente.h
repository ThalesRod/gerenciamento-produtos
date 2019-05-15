#ifndef CLIENTE_H
#define CLIENTE_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include <stdio.h>

typedef unsigned char byte;


class Cliente {

	unsigned short id;
	std::string nome;
	std::string email;

	public:
		// Getters
		unsigned short get_id();
		std::string get_nome();
		std::string get_email();
		
		// Setters
		void set_id(unsigned short novoId);
		void set_append_nome(char c);
		void set_append_email(char c);
		
		void lerDadosCliente(FILE *arquivoID);
		void exibeDadosCliente();		
};

class ClienteEntrada {

	char lapide;
	unsigned short tamanhoVetorDeBytes;
	std::vector<byte> vetorDeBytes;

	public:
		unsigned long int armazenaCliente(FILE *arquivoDados, Cliente *cliente);
		static Cliente* recuperaCliente(FILE *arquivoDados, unsigned long int endereco);
	
	private:
		std::vector<byte> clienteParaBytes(Cliente* cliente);
		static Cliente* bytesParaCliente(std::vector<byte> vetorDeBytes);
};

#endif