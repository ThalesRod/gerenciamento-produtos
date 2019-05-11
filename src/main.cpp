#include "../include/produto.h"
#include "../include/tabela.h"
#include "../include/crudProdutos.h"

#include <iostream>
#include <stdio.h>

char menu(){

    char RespostaMenu;

    std::cout << "Opcoes: " << std::endl;
    std::cout << "[I] - Inclusao" << std::endl;
    std::cout << "[A] - Alteracao" << std::endl;
    std::cout << "[E] - exclusao" << std::endl;
    std::cout << "[B] - Busca" << std::endl;
    std::cout << "[S] - Sair" << std::endl;
    std::cout << "Qual a opcao desejada: ";
    std::cin >> RespostaMenu;

    return RespostaMenu;
}

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


    CrudProdutos *crudProdutos = new CrudProdutos();

    char MenuResp;

    while(true) {
        MenuResp = menu();

        if(MenuResp=='I'){
            getchar();
            crudProdutos->inclusao(arquivoIndice, arquivoDados, arquivoID);
            std::cout << std::endl;
        }

        if(MenuResp=='E'){
            std::cout << "Digite o ID: ";
            unsigned short id;
            std::cin >> id;
            crudProdutos->exclusao(arquivoIndice, arquivoDados, id);
        }

        if(MenuResp=='A'){
            std::cout << "Digite o ID: ";
            unsigned short id;
            std::cin >> id;
            getchar();
            crudProdutos->alteracao(arquivoIndice, arquivoDados, arquivoID, id);
        }

        if(MenuResp=='B'){
            std::cout << "Digite o ID: ";
            unsigned short id;
            std::cin >> id;
            crudProdutos->busca(arquivoIndice, arquivoDados, id);
        }
        if(MenuResp == 'S')
            break;
    }

    fclose(arquivoDados);
    fclose(arquivoID);
    fclose(arquivoIndice);

	return 0;
}