#ifndef CRUDCLIENTES_H
#define CRUDCLIENTES_H

#include "../include/cliente.h"
#include "../include/tabela.h"

#include <iostream>
#include <stdio.h>

class CrudClientes {

	public:
		void inclusao(FILE *arquivoIndice, FILE *arquivoDados, FILE *arquivoID);
		static void busca(FILE *arquivoIndice, FILE *arquivoDados, unsigned short id);
		void alteracao(FILE *arquivoIndice, FILE *arquivoDados, FILE *arquivoID, unsigned short id);
		void exclusao(FILE *arquivoIndice, FILE *arquivoDados, unsigned short id);
		void listar(FILE *arquivoIndice, FILE *arquivoDados, FILE *arquivoID);
};

#endif