#include "../include/crudCategorias.h"

void CrudCategorias::inclusao(FILE *arquivoIndice, FILE *arquivoDados, FILE *arquivoID) {

    Categoria *c = new Categoria();
   	CategoriaEntrada ce;
    char aceita = 'A';

	c->lerDadosCategoria(arquivoID);

    std::cout << "\nDeseja confirmar a categoria? (s/n): ";
    std::cin >> aceita;

    if(aceita == 'n')
        return;


    EntradaIndice *entrada = new EntradaIndice();
    entrada->lapide = '$';
    entrada->id = c->get_id();
    entrada->endereco = ce.armazenaCategoria(arquivoDados, c);

    TabelaHash::escreveIndice(arquivoIndice, entrada, TabelaHash::geraHash(c->get_id() - 48));

    rewind(arquivoDados);
    rewind(arquivoIndice);
}

void CrudCategorias::busca(FILE *arquivoIndice, FILE *arquivoDados, unsigned short id) {

    Categoria *c = new Categoria();

    c = CategoriaEntrada::recuperaCategoria(arquivoDados, TabelaHash::lerIndice(arquivoIndice, id, TabelaHash::geraHash(id)));

    c->exibeDadosCategoria();

    rewind(arquivoDados);
    rewind(arquivoIndice);
}

void CrudCategorias::alteracao(FILE *arquivoIndice, FILE *arquivoDados, FILE *arquivoID, unsigned short id) {

    Categoria *c = new Categoria();
    CategoriaEntrada ce;
    char confirmacao;

    unsigned long int endereco = TabelaHash::lerIndice(arquivoIndice, id, TabelaHash::geraHash(id));

    c = CategoriaEntrada::recuperaCategoria(arquivoDados, endereco);

    c->exibeDadosCategoria();

    if( c->get_id() == 65535 ) {
        rewind(arquivoDados);
        return;
    }

    std::cout << std::endl;

    c->lerDadosCategoria(arquivoID);

    std::cout << "\nDeseja alterar essa categoria? (s/n) ";
    std::cin >> confirmacao;

    if (confirmacao == 'n') {
        rewind(arquivoDados);
        return;
    }

    EntradaIndice *entrada = new EntradaIndice();
    entrada->lapide = '$';
    entrada->id = c->get_id();
    entrada->endereco = ce.armazenaCategoria(arquivoDados, c);

    TabelaHash::escreveIndice(arquivoIndice, entrada, TabelaHash::geraHash(c->get_id() - 48));

    rewind(arquivoDados);
    rewind(arquivoIndice);


    // Marcando registro alterado como excluido
    fseek(arquivoDados, endereco, SEEK_SET);
    fputc((byte)'*', arquivoDados);
    fflush(arquivoDados);

    rewind(arquivoDados);
}

void CrudCategorias::exclusao(FILE *arquivoIndice, FILE *arquivoDados, FILE *arquivoIndiceProdutos, FILE *arquivoDadosProdutos, FILE *arquivoIDProdutos, unsigned short id) {
    
    Categoria* c = new Categoria();
    char confirmacao;

    unsigned long int endereco = TabelaHash::lerIndice(arquivoIndice, id, TabelaHash::geraHash(id));

    c = CategoriaEntrada::recuperaCategoria(arquivoDados, endereco);

    if ( CrudProdutos::existeProdutosNaCategoria(arquivoIndiceProdutos, arquivoDadosProdutos, arquivoIDProdutos, c->get_id() - 48) ) {
        
        std::cout << std::endl;
        std::cout << "===== Nao foi possivel Excluir!!! ======" << std::endl;
        std::cout << "===== Categoria nao esta vazia!!! ======" << std::endl;
        std::cout << std::endl;

        rewind(arquivoDados);
        return;
    }

    c->exibeDadosCategoria();

    if( c->get_id() == 65535 ) {
        rewind(arquivoDados);
        return;
    }

    std::cout << "\nDeseja excluir essa categoria? (s/n) ";
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
