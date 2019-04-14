#include "../include/produto.h"


int main(int argc, char const *argv[]) {

	FILE *arquivoDados;
    FILE *arquivoID;

	arquivoDados = fopen("database/dados.db", "r+b");

    if (arquivoDados == NULL) {
        arquivoDados = fopen("database/dados.db", "wb");
        fclose(arquivoDados);
		arquivoDados = fopen("database/dados.db", "r+b");
    }

    arquivoID = fopen("database/dados.id", "r+b");

    if (arquivoID == NULL) {
        arquivoID = fopen("database/dados.id", "wb");
        fputc((byte)'0', arquivoID);
        fclose(arquivoID);

        arquivoID = fopen("database/dados.id", "r+b");
    }


	Produto *p = new Produto();
	ProdutoEntrada pe;

	// p->lerDadosProduto(arquivoID);
	// pe.armazenaProduto(arquivoDados, p);

	p = pe.recuperaProduto(arquivoDados, 23);
	p->exibeDadosProduto();

    fclose(arquivoDados);
    fclose(arquivoID);

	return 0;
}