#include "../include/produto.h"
#include "../include/categoria.h"
#include "../include/tabela.h"
#include "../include/crudProdutos.h"
#include "../include/crudCategorias.h"

#include <iostream>
#include <stdio.h>

char menu(){

    char RespostaMenu;

    std::cout << "Opcoes produtos:\n " << std::endl;

    std::cout << "[I] - Inclusao - Produto" << std::endl;
    std::cout << "[A] - Alteracao - Produto" << std::endl;
    std::cout << "[E] - Exclusao - Produto" << std::endl;
    std::cout << "[B] - Busca - Produto" << std::endl;
    std::cout << "[L] - Listar - Produto" << std::endl;

    std::cout << "\nOpcoes categorias:\n " << std::endl;

    std::cout << "[1] - Inclusao - Categoria" << std::endl;
    std::cout << "[2] - Alteracao - Categoria" << std::endl;
    std::cout << "[3] - Exclusao - Categoria" << std::endl;
    std::cout << "[4] - Busca - Categoria" << std::endl;

    std::cout << "\n[S] - Sair" << std::endl;

    std::cout << "Qual a opcao desejada: ";
    std::cin >> RespostaMenu;

    return RespostaMenu;
}

int main(int argc, char const *argv[]) {

	FILE *arquivoDados;
    FILE *arquivoIndice;
    FILE *arquivoID;

    FILE *arquivoDadosCategorias;
    FILE *arquivoIndiceCategorias;
    FILE *arquivoIDCategorias;

    // Iniciando os Bancos de Dados de Produtos

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

    // Iniciando os Bancos de Dados de Categorias

    arquivoDadosCategorias = fopen("database/categorias.db", "r+b");

    if (arquivoDadosCategorias == NULL) {
        arquivoDadosCategorias = fopen("database/categorias.db", "wb");
        fclose(arquivoDadosCategorias);
        arquivoDadosCategorias = fopen("database/categorias.db", "r+b");
    }

    arquivoIDCategorias = fopen("database/categorias.id", "r+b");

    if (arquivoIDCategorias == NULL) {
        arquivoIDCategorias = fopen("database/categorias.id", "wb");
        fputc((byte)'0', arquivoIDCategorias);
        fclose(arquivoIDCategorias);

        arquivoIDCategorias = fopen("database/categorias.id", "r+b");
    }

    arquivoIndiceCategorias = fopen("database/categorias.index", "r+b");

    if (arquivoIndiceCategorias == NULL) {
        arquivoIndiceCategorias = fopen("database/categorias.index", "wb");
    
        TabelaHash::inicializa(arquivoIndiceCategorias);
    
        fclose(arquivoIndiceCategorias);

        arquivoIndiceCategorias = fopen("database/categorias.index", "r+b");
    }




    CrudProdutos *crudProdutos = new CrudProdutos();
    CrudCategorias *crudCategorias = new CrudCategorias();

    char MenuResp;

    while(true) {
        MenuResp = menu();

        // Opcoes Produto

        if(MenuResp=='I'){
            getchar();
            crudProdutos->inclusao(arquivoIndice, arquivoDados, arquivoID, arquivoIndiceCategorias, arquivoDadosCategorias);
            std::cout << std::endl;
        }

        if(MenuResp=='E'){
            std::cout << "Digite o ID: ";
            unsigned short id;
            std::cin >> id;
            crudProdutos->exclusao(arquivoIndice, arquivoDados, arquivoIndiceCategorias, arquivoDadosCategorias, id);
        }

        if(MenuResp=='A'){
            std::cout << "Digite o ID: ";
            unsigned short id;
            std::cin >> id;
            getchar();
            crudProdutos->alteracao(arquivoIndice, arquivoDados, arquivoID, arquivoIndiceCategorias, arquivoDadosCategorias, id);
        }

        if(MenuResp=='B'){
            std::cout << "Digite o ID: ";
            unsigned short id;
            std::cin >> id;
            crudProdutos->busca(arquivoIndice, arquivoDados, arquivoIndiceCategorias, arquivoDadosCategorias, id);
        }

        if(MenuResp=='L'){
            crudProdutos->listar(arquivoIndice, arquivoDados, arquivoID);
        }

        // Opcoes Categoria

        if(MenuResp=='1'){
            getchar();
            crudCategorias->inclusao(arquivoIndiceCategorias, arquivoDadosCategorias, arquivoIDCategorias);
            std::cout << std::endl;
        }

        if(MenuResp=='3'){
            std::cout << "Digite o ID: ";
            unsigned short id;
            std::cin >> id;
            crudCategorias->exclusao(arquivoIndiceCategorias, arquivoDadosCategorias, arquivoIndice, arquivoDados, arquivoID, id);
        }

        if(MenuResp=='2'){
            std::cout << "Digite o ID: ";
            unsigned short id;
            std::cin >> id;
            getchar();
            crudCategorias->alteracao(arquivoIndiceCategorias, arquivoDadosCategorias, arquivoIDCategorias, id);
        }

        if(MenuResp=='4'){
            std::cout << "Digite o ID: ";
            unsigned short id;
            std::cin >> id;
            crudCategorias->busca(arquivoIndiceCategorias, arquivoDadosCategorias, id);
        }

        if(MenuResp == 'S')
            break;
    }

    fclose(arquivoDados);
    fclose(arquivoID);
    fclose(arquivoIndice);

    fclose(arquivoDadosCategorias);
    fclose(arquivoIDCategorias);
    fclose(arquivoIndiceCategorias);

	return 0;
}