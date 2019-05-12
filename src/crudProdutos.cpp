#include "../include/crudProdutos.h"


void CrudProdutos::inclusao(FILE *arquivoIndice, FILE *arquivoDados, FILE *arquivoID, FILE *arquivoIndiceCategorias, FILE *arquivoDadosCategorias){

    Produto *p = new Produto();
   	ProdutoEntrada pe;
    char aceita = 'A';

	p->lerDadosProduto(arquivoID);

    unsigned short idCategoria = p->get_idCategoria();

    // Verificando se categoria existe
    Categoria *c = new Categoria();
    c = CategoriaEntrada::recuperaCategoria(arquivoDadosCategorias, TabelaHash::lerIndice(arquivoIndiceCategorias, idCategoria, TabelaHash::geraHash(idCategoria)));

    while ( c->get_id() == 65535 ) { // 65535 igual -1 em complemento de 2

        std::cout << "\n=== Categoria nao existe! ===\n" << std::endl;

        std::cout << "Digite o ID da categoria do produto: ";
        std::cin >> idCategoria;

        p->set_idCategoria(idCategoria);

        idCategoria = p->get_idCategoria();
        c = CategoriaEntrada::recuperaCategoria(arquivoDadosCategorias, TabelaHash::lerIndice(arquivoIndiceCategorias, idCategoria, TabelaHash::geraHash(idCategoria)));
    }

    // Mostra categoria
    c->exibeDadosCategoria();


    std::cout << "\nDeseja confirmar o produto (s/n): ";
    std::cin >> aceita;

    if(aceita == 'n')
        return;


    EntradaIndice *entrada = new EntradaIndice();
    entrada->lapide = '$';
    entrada->id = p->get_id();
    entrada->endereco = pe.armazenaProduto(arquivoDados, p);

    TabelaHash::escreveIndice(arquivoIndice, entrada, TabelaHash::geraHash(p->get_id() - 48));

    rewind(arquivoDados);
    rewind(arquivoIndice);
}

void CrudProdutos::busca(FILE *arquivoIndice, FILE *arquivoDados, FILE *arquivoIndiceCategorias, FILE *arquivoDadosCategorias, unsigned short id) {

    Produto *p = new Produto();

    p = ProdutoEntrada::recuperaProduto(arquivoDados, TabelaHash::lerIndice(arquivoIndice, id, TabelaHash::geraHash(id)));

    p->exibeDadosProduto(arquivoIndiceCategorias, arquivoDadosCategorias);

    rewind(arquivoDados);
    rewind(arquivoIndice);
}

void CrudProdutos::alteracao(FILE *arquivoIndice, FILE *arquivoDados, FILE *arquivoID, FILE *arquivoIndiceCategorias, FILE *arquivoDadosCategorias, unsigned short id) {

    Produto *p = new Produto();
    ProdutoEntrada pe;
    char confirmacao;

    unsigned long int endereco = TabelaHash::lerIndice(arquivoIndice, id, TabelaHash::geraHash(id));

    p = ProdutoEntrada::recuperaProduto(arquivoDados, endereco);

    p->exibeDadosProduto(arquivoIndiceCategorias, arquivoDadosCategorias);

    std::cout << std::endl;

    p->lerDadosProduto(arquivoID);

    unsigned short idCategoria = p->get_idCategoria();

    // Verificando se categoria existe
    Categoria *c = new Categoria();
    c = CategoriaEntrada::recuperaCategoria(arquivoDadosCategorias, TabelaHash::lerIndice(arquivoIndiceCategorias, idCategoria, TabelaHash::geraHash(idCategoria)));

    while ( c->get_id() == 65535 ) { // 65535 igual -1 em complemento de 2

        std::cout << "\n=== Categoria nao existe! ===\n" << std::endl;

        std::cout << "Digite o ID da categoria do produto: ";
        std::cin >> idCategoria;

        p->set_idCategoria(idCategoria);

        idCategoria = p->get_idCategoria();
        c = CategoriaEntrada::recuperaCategoria(arquivoDadosCategorias, TabelaHash::lerIndice(arquivoIndiceCategorias, idCategoria, TabelaHash::geraHash(idCategoria)));
    }

    // Mostra categoria
    c->exibeDadosCategoria();


    std::cout << "\nDeseja alterar esse produto? (s/n) ";
    std::cin >> confirmacao;

    if (confirmacao == 'n') {
        rewind(arquivoDados);
        return;
    }

    EntradaIndice *entrada = new EntradaIndice();
    entrada->lapide = '$';
    entrada->id = p->get_id();
    entrada->endereco = pe.armazenaProduto(arquivoDados, p);

    TabelaHash::escreveIndice(arquivoIndice, entrada, TabelaHash::geraHash(p->get_id() - 48));

    rewind(arquivoDados);
    rewind(arquivoIndice);


    // Marcando registro alterado como excluido
    fseek(arquivoDados, endereco, SEEK_SET);
    fputc((byte)'*', arquivoDados);
    fflush(arquivoDados);

    rewind(arquivoDados);
}

void CrudProdutos::exclusao(FILE *arquivoIndice, FILE *arquivoDados, FILE *arquivoIndiceCategorias, FILE *arquivoDadosCategorias, unsigned short id) {
    
    Produto* p = new Produto();
    char confirmacao;

    unsigned long int endereco = TabelaHash::lerIndice(arquivoIndice, id, TabelaHash::geraHash(id));

    p = ProdutoEntrada::recuperaProduto(arquivoDados, endereco);

    p->exibeDadosProduto(arquivoIndiceCategorias, arquivoDadosCategorias);

    std::cout << "\nDeseja excluir esse produto? (s/n) ";
    std::cin >> confirmacao;

    if (confirmacao == 'n') {
        rewind(arquivoDados);
        return;
    }

    // Marcando registro como excluido
    fseek(arquivoDados, endereco, SEEK_SET);
    fputc((byte)'*', arquivoDados);
    fflush(arquivoDados);

    rewind(arquivoDados);
}

void CrudProdutos::listar(FILE *arquivoIndice, FILE *arquivoDados, FILE *arquivoID) {

    Produto *p = new Produto();

    auto lerId = 
    [](FILE *arquivoID) {
        unsigned short id;

        rewind(arquivoID);
        id = (unsigned short)fgetc(arquivoID);
        
        rewind(arquivoID);
        
        return id;
    };

    unsigned short ultimoID = lerId(arquivoID);

    for (int id = 0; id < ultimoID - 48 -1; ++id) {

        p = ProdutoEntrada::recuperaProduto(arquivoDados, TabelaHash::lerIndice(arquivoIndice, id, TabelaHash::geraHash(id)));

        p->exibeDadosProduto(NULL, NULL);
    }

    std::cout << "Total: " << ultimoID - 48 -1 << " produtos\n" << std::endl;

    rewind(arquivoDados);
    rewind(arquivoIndice);
}

bool CrudProdutos::existeProdutosNaCategoria(FILE *arquivoIndice, FILE *arquivoDados, FILE *arquivoID, unsigned short idCategoria) {

    Produto *p = new Produto();

    auto lerId = 
    [](FILE *arquivoID) {
        unsigned short id;

        rewind(arquivoID);
        id = (unsigned short)fgetc(arquivoID);
        
        rewind(arquivoID);
        
        return id;
    };

    unsigned short ultimoID = lerId(arquivoID);

    for (int id = 0; id < ultimoID - 48; ++id) {

        p = ProdutoEntrada::recuperaProduto(arquivoDados, TabelaHash::lerIndice(arquivoIndice, id, TabelaHash::geraHash(id)));

        if ( p->get_idCategoria() == idCategoria ) {
            
            rewind(arquivoDados);
            rewind(arquivoIndice);

            return true;
        }
    }

    rewind(arquivoDados);
    rewind(arquivoIndice);

    return false;
}