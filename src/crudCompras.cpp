#include "../include/crudCompras.h"
#include "../include/compra.h"


void CrudCompras::inclusao(FILE *arquivoIndice, FILE *arquivoDados, FILE *arquivoID, FILE *arquivoIndiceClientes, FILE *arquivoDadosClientes){

    Compra *c = new Compra();
   	CompraEntrada ce;
    char aceita = 'A';

	c->lerDadosCompra(arquivoID);

    unsigned short idCliente = c->get_idCliente();

    // Verificando se cliente existe
    Cliente *cl = new Cliente();
    cl = ClienteEntrada::recuperaCliente(arquivoDadosClientes, TabelaHash::lerIndice(arquivoIndiceClientes, idCliente, TabelaHash::geraHash(idCliente)));

    while ( cl->get_id() == 65535 ) { // 65535 igual -1 em complemento de 2

        std::cout << "\n=== Cliente nao existe! ===\n" << std::endl;

        std::cout << "Digite o ID do cliente da compra: ";
        std::cin >> idCliente;

        c->set_idCliente(idCliente);

        idCliente = c->get_idCliente();
        cl = ClienteEntrada::recuperaCliente(arquivoDadosClientes, TabelaHash::lerIndice(arquivoIndiceClientes, idCliente, TabelaHash::geraHash(idCliente)));
    }

    // Mostra categoria
    cl->exibeDadosCliente();


    unsigned short idProduto;
    std::cout << "Digite o ID do produto da compra: ";
    std::cin >> idProduto;

    unsigned short quantidadeProduto;
    std::cout << "Digite a quantidade de produtos da compra: ";
    std::cin >> quantidadeProduto;

    c->set_idProduto(idProduto);
    c->set_quantidadeProduto(quantidadeProduto);

    c->set_preco(quantidadeProduto * c->get_preco());

    std::cout << "\nDeseja confirmar a compra? (s/n): ";
    std::cin >> aceita;

    if(aceita == 'n')
        return;


    EntradaIndice *entrada = new EntradaIndice();
    entrada->lapide = '$';
    entrada->id = c->get_id();
    entrada->endereco = ce.armazenaCompra(arquivoDados, c);

    TabelaHash::escreveIndice(arquivoIndice, entrada, TabelaHash::geraHash(c->get_id() - 48));

    rewind(arquivoDados);
    rewind(arquivoIndice);
}

void CrudCompras::busca(FILE *arquivoIndice, FILE *arquivoDados, FILE *arquivoIndiceClientes, FILE *arquivoDadosClientes, FILE *arquivoIndiceProdutos, FILE *arquivoDadosProdutos, FILE *arquivoIndiceCategorias, FILE *arquivoDadosCategorias, unsigned short id) {

    Compra *c = new Compra();

    c = CompraEntrada::recuperaCompra(arquivoDados, TabelaHash::lerIndice(arquivoIndice, id, TabelaHash::geraHash(id)));

    c->exibeDadosCompra(arquivoIndiceClientes, arquivoDadosClientes, arquivoIndiceProdutos, arquivoDadosProdutos, arquivoIndiceCategorias, arquivoDadosCategorias);

    rewind(arquivoDados);
    rewind(arquivoIndice);
}

void CrudCompras::alteracao(FILE *arquivoIndice, FILE *arquivoDados, FILE *arquivoID, FILE *arquivoIndiceClientes, FILE *arquivoDadosClientes, FILE *arquivoIndiceProdutos, FILE *arquivoDadosProdutos, FILE *arquivoIndiceCategorias, FILE *arquivoDadosCategorias, unsigned short id) {

    Compra *c = new Compra();
    CompraEntrada ce;
    char confirmacao;

    unsigned long int endereco = TabelaHash::lerIndice(arquivoIndice, id, TabelaHash::geraHash(id));

    c = CompraEntrada::recuperaCompra(arquivoDados, endereco);

    c->exibeDadosCompra(arquivoIndiceClientes, arquivoDadosClientes, arquivoIndiceProdutos, arquivoDadosProdutos, arquivoIndiceCategorias, arquivoDadosCategorias);

    std::cout << std::endl;

    c->lerDadosCompra(arquivoID);

    unsigned short idCliente = c->get_idCliente();

    // Verificando se cliente existe
    Cliente *cl = new Cliente();
    cl = ClienteEntrada::recuperaCliente(arquivoDadosClientes, TabelaHash::lerIndice(arquivoIndiceClientes, idCliente, TabelaHash::geraHash(idCliente)));

    while ( cl->get_id() == 65535 ) { // 65535 igual -1 em complemento de 2

        std::cout << "\n=== Cliente nao existe! ===\n" << std::endl;

        std::cout << "Digite o ID da categoria do produto: ";
        std::cin >> idCliente;

        c->set_idCliente(idCliente);

        idCliente = c->get_idCliente();
        cl = ClienteEntrada::recuperaCliente(arquivoDadosClientes, TabelaHash::lerIndice(arquivoIndiceClientes, idCliente, TabelaHash::geraHash(idCliente)));
    }

    // Mostra categoria
    cl->exibeDadosCliente();


    std::cout << "\nDeseja alterar essa compra? (s/n) ";
    std::cin >> confirmacao;

    if (confirmacao == 'n') {
        rewind(arquivoDados);
        return;
    }

    EntradaIndice *entrada = new EntradaIndice();
    entrada->lapide = '$';
    entrada->id = c->get_id();
    entrada->endereco = ce.armazenaCompra(arquivoDados, c);

    TabelaHash::escreveIndice(arquivoIndice, entrada, TabelaHash::geraHash(c->get_id() - 48));

    rewind(arquivoDados);
    rewind(arquivoIndice);


    // Marcando registro alterado como excluido
    fseek(arquivoDados, endereco, SEEK_SET);
    fputc((byte)'*', arquivoDados);
    fflush(arquivoDados);

    rewind(arquivoDados);
}

void CrudCompras::exclusao(FILE *arquivoIndice, FILE *arquivoDados, FILE *arquivoIndiceClientes, FILE *arquivoDadosClientes, FILE *arquivoIndiceProdutos, FILE *arquivoDadosProdutos, FILE *arquivoIndiceCategorias, FILE *arquivoDadosCategorias, unsigned short id) {
    
    Compra* c = new Compra();
    char confirmacao;

    unsigned long int endereco = TabelaHash::lerIndice(arquivoIndice, id, TabelaHash::geraHash(id));

    c = CompraEntrada::recuperaCompra(arquivoDados, endereco);

    c->exibeDadosCompra(arquivoIndiceClientes, arquivoDadosClientes, arquivoIndiceProdutos, arquivoDadosProdutos, arquivoIndiceCategorias, arquivoDadosCategorias);

    std::cout << "\nDeseja excluir esse cliente? (s/n) ";
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