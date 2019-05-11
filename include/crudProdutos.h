#ifndef CRUDPRODUTOS_H
#define CRUDPRODUTOS_H

#include <iostream>
#include <stdio.h>

class CrudProdutos {

	public:
		void inclusao(FILE *arquivoIndice, FILE *arquivoDados, FILE *arquivoID);
		void busca(FILE *arquivoIndice, FILE *arquivoDados, unsigned short id);
		void alteracao(FILE *arquivoIndice, FILE *arquivoDados, FILE *arquivoID, unsigned short id);
		void exclusao(FILE *arquivoIndice, FILE *arquivoDados, unsigned short id);

};

#endif