#ifndef CRUDCATEGORIAS_H
#define CRUDCATEGORIAS_H

#include "../include/categoria.h"
#include "../include/tabela.h"
#include "../include/crudProdutos.h"

#include <iostream>
#include <stdio.h>

class CrudCategorias {

	public:
		void inclusao(FILE *arquivoIndice, FILE *arquivoDados, FILE *arquivoID);
		static void busca(FILE *arquivoIndice, FILE *arquivoDados, unsigned short id);
		void alteracao(FILE *arquivoIndice, FILE *arquivoDados, FILE *arquivoID, unsigned short id);
		void exclusao(FILE *arquivoIndice, FILE *arquivoDados, FILE *arquivoIndiceProdutos, FILE *arquivoDadosProdutos, FILE *arquivoIDProdutos, unsigned short id);

};

#endif