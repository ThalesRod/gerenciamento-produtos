#include "../include/produto.h"
#include "../include/tabela.h"
#include "../include/crudProdutos.h"

#include <iostream>

int main(int argc, char const *argv[]) {

	FILE *arquivoDados;
    FILE *arquivoIndice;
    FILE *arquivoID;

    // Iniciando os Bancos de Dados

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

    arquivoIndice = fopen("database/dados.index", "r+b");

    if (arquivoIndice == NULL) {
        arquivoIndice = fopen("database/dados.index", "wb");
    
        TabelaHash::inicializa(arquivoIndice);
    
        fclose(arquivoIndice);

        arquivoIndice = fopen("database/dados.index", "r+b");
    }

	// Produto *p = new Produto();
    // ProdutoEntrada pe;

	// p->lerDadosProduto(arquivoID);
	// pe.armazenaProduto(arquivoDados, p);

	// p = ProdutoEntrada::recuperaProduto(arquivoDados, 56);
	// p->exibeDadosProduto();

    CrudProdutos *crud = new CrudProdutos();
    crud->inclusao(arquivoIndice, arquivoDados, arquivoID);


    fclose(arquivoDados);
    fclose(arquivoID);
    fclose(arquivoIndice);

	return 0;
}