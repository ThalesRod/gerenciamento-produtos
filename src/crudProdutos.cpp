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

    std::cout << "Nome: " << p->get_nome() << std::endl;
    std::cout << "Descricao: " << p->get_descricao() << std::endl;
    std::cout << "Preco: " << p->get_preco() << std::endl;

}

void CrudProdutos::alteracao(FILE *arquivoIndice, FILE *arquivoDados, FILE *arquivoID, unsigned long int endereco) {

}

void CrudProdutos::exclusao(FILE *arquivoDados, unsigned long int endereco) {

}
