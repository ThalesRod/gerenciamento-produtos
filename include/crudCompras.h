#ifndef CRUDCOMPRAS_H
#define CRUDCOMPRAS_H

#include "../include/compra.h"
#include "../include/cliente.h"
#include "../include/tabela.h"

#include <iostream>
#include <stdio.h>

class CrudCompras {

	public:
		void inclusao(FILE *arquivoIndice, FILE *arquivoDados, FILE *arquivoID, FILE *arquivoIndiceClientes, FILE *arquivoDadosClientes);
		void busca(FILE *arquivoIndice, FILE *arquivoDados, FILE *arquivoIndiceClientes, FILE *arquivoDadosClientes, FILE *arquivoIndiceProdutos, FILE *arquivoDadosProdutos, FILE *arquivoIndiceCategorias, FILE *arquivoDadosCategorias, unsigned short id);
		void alteracao(FILE *arquivoIndice, FILE *arquivoDados, FILE *arquivoID, FILE *arquivoIndiceClientes, FILE *arquivoDadosClientes, FILE *arquivoIndiceProdutos, FILE *arquivoDadosProdutos, FILE *arquivoIndiceCategorias, FILE *arquivoDadosCategorias, unsigned short id);
		void exclusao(FILE *arquivoIndice, FILE *arquivoDados, FILE *arquivoIndiceClientes, FILE *arquivoDadosClientes, FILE *arquivoIndiceProdutos, FILE *arquivoDadosProdutos, FILE *arquivoIndiceCategorias, FILE *arquivoDadosCategorias, unsigned short id);
};

#endif