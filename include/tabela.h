#ifndef TABELA_H
#define TABELA_H

#include <iostream>

#define PROFUNDIDADE_TABELA 80
#define TAM_BUCKET sizeof(EntradaIndice)

typedef unsigned char byte;

typedef struct EntradaIndice {
    char lapide;
    unsigned short id;
    unsigned long int endereco;

} EntradaIndice;


class TabelaHash {

	public:
		static void inicializa(FILE *arquivoIndice);
		static short geraHash(unsigned short id);

		static void escreveIndice(FILE *arquivoIndice, EntradaIndice *entrada, short pos);
		static unsigned long int lerIndice(FILE *arquivoIndice, unsigned short id, short pos);
};

#endif