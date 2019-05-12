#ifndef CRUDPRODUTOS_H
#define CRUDPRODUTOS_H

#include "../include/produto.h"
#include "../include/categoria.h"
#include "../include/tabela.h"

#include <iostream>
#include <stdio.h>

class CrudProdutos {

	public:
		void inclusao(FILE *arquivoIndice, FILE *arquivoDados, FILE *arquivoID, FILE *arquivoIndiceCategorias, FILE *arquivoDadosCategorias);
		void busca(FILE *arquivoIndice, FILE *arquivoDados, FILE *arquivoIndiceCategorias, FILE *arquivoDadosCategorias, unsigned short id);
		void alteracao(FILE *arquivoIndice, FILE *arquivoDados, FILE *arquivoID, FILE *arquivoIndiceCategorias, FILE *arquivoDadosCategorias, unsigned short id);
		void exclusao(FILE *arquivoIndice, FILE *arquivoDados, FILE *arquivoIndiceCategorias, FILE *arquivoDadosCategorias, unsigned short id);
		void listar(FILE *arquivoIndice, FILE *arquivoDados, FILE *arquivoID);
		static bool existeProdutosNaCategoria(FILE *arquivoIndice, FILE *arquivoDados, FILE *arquivoID, unsigned short idCategoria);
};

#endif