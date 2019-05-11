#include "../include/produto.h"
#include "../include/tabela.h"
#include "../include/crudProdutos.h"

void CrudProdutos::inclusao(FILE *arquivoIndice, FILE *arquivoDados, FILE *arquivoID){

    Produto *p = new Produto();
   	ProdutoEntrada pe;
    char aceita = 'A';

	p->lerDadosProduto(arquivoID);

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

void CrudProdutos::busca(FILE *arquivoIndice, FILE *arquivoDados, unsigned short id) {

    Produto *p = new Produto();

    p = ProdutoEntrada::recuperaProduto(arquivoDados, TabelaHash::lerIndice(arquivoIndice, id, TabelaHash::geraHash(id)));

    p->exibeDadosProduto();

    rewind(arquivoDados);
    rewind(arquivoIndice);
}

void CrudProdutos::alteracao(FILE *arquivoIndice, FILE *arquivoDados, FILE *arquivoID, unsigned short id) {

    Produto *p = new Produto();
    ProdutoEntrada pe;
    char confirmacao;

    unsigned long int endereco = TabelaHash::lerIndice(arquivoIndice, id, TabelaHash::geraHash(id));

    p = ProdutoEntrada::recuperaProduto(arquivoDados, endereco);

    p->exibeDadosProduto();

    std::cout << std::endl;

    p->lerDadosProduto(arquivoID);

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

void CrudProdutos::exclusao(FILE *arquivoIndice, FILE *arquivoDados, unsigned short id) {
    
    Produto* p = new Produto();
    char confirmacao;

    unsigned long int endereco = TabelaHash::lerIndice(arquivoIndice, id, TabelaHash::geraHash(id));

    p = ProdutoEntrada::recuperaProduto(arquivoDados, endereco);

    p->exibeDadosProduto();

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
