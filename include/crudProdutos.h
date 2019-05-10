#ifndef CRUDPRODUTOS_H
#define CRUDPRODUTOS_H

#include <iostream>
#include <stdio.h>

class CrudProdutos {

	public:
		void inclusao(FILE *arquivoIndice, FILE *arquivoDados, FILE *arquivoID);
		void busca(FILE *arquivoIndice, FILE *arquivoDados, unsigned short id);
		void alteracao(FILE *arquivoIndice, FILE *arquivoDados, FILE *arquivoID, unsigned long int endereco);
		void exclusao(FILE *arquivoDados, unsigned long int endereco);

};

#endif