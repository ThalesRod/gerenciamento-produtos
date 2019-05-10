#include "../include/tabela.h"


void TabelaHash::inicializa(FILE *arquivoIndice) {

    arquivoIndice = fopen("database/dados.index", "wb");

    EntradaIndice entradaVazia;
    entradaVazia.lapide = '#';
    entradaVazia.id = 0;
    entradaVazia.endereco = 0;

    for (short i=0; i < PROFUNDIDADE_TABELA; ++i) {
        fwrite(&entradaVazia, sizeof(EntradaIndice), 1, arquivoIndice);
    }

    fclose(arquivoIndice);
}

short TabelaHash::geraHash(unsigned short id) {

	return id % PROFUNDIDADE_TABELA;
}

void TabelaHash::escreveIndice(FILE *arquivoIndice, EntradaIndice *entrada, short pos) {


    unsigned long int enderecoIndice = TAM_BUCKET * pos;

    unsigned long int enderecoPrimeiraLapide = enderecoIndice;

    // Desloca o ponteiro ate a primeira lapide
    fseek(arquivoIndice, enderecoPrimeiraLapide, SEEK_SET);

    // Verificando se a posicao ja esta ocupada
    if ( fgetc(arquivoIndice) == '$' ) {
        std::cout << "Banco de Dados Cheio!!!" << std::endl;
        return;
    }

    rewind(arquivoIndice);
    // Fim da verificacao

    // Desloca o ponteiro novamente ate a primeira lapide

    byte* entradaBytes = (byte*)entrada;
    for(short i=0; i<16; ++i) {
        fseek(arquivoIndice, enderecoIndice + i, SEEK_SET);
        fputc(entradaBytes[i], arquivoIndice);
    }

    rewind(arquivoIndice);
}

unsigned long int TabelaHash::lerIndice(FILE *arquivoIndice, unsigned short id, short pos) {

    fseek(arquivoIndice, TAM_BUCKET * pos, SEEK_SET);

	unsigned long int endereco = -1;

    EntradaIndice entrada;
    fread(&entrada, sizeof(EntradaIndice), 1, arquivoIndice);

    endereco = entrada.endereco;

    rewind(arquivoIndice);
    return endereco;
}