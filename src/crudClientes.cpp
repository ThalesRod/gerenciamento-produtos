#include "../include/crudClientes.h"


void CrudClientes::inclusao(FILE *arquivoIndice, FILE *arquivoDados, FILE *arquivoID){

    Cliente *c = new Cliente();
   	ClienteEntrada ce;
    char aceita = 'A';

	c->lerDadosCliente(arquivoID);

    std::cout << "\nDeseja confirmar o cliente (s/n): ";
    std::cin >> aceita;

    if(aceita == 'n')
        return;


    EntradaIndice *entrada = new EntradaIndice();
    entrada->lapide = '$';
    entrada->id = c->get_id();
    entrada->endereco = ce.armazenaCliente(arquivoDados, c);

    TabelaHash::escreveIndice(arquivoIndice, entrada, TabelaHash::geraHash(c->get_id() - 48));

    rewind(arquivoDados);
    rewind(arquivoIndice);
}

void CrudClientes::busca(FILE *arquivoIndice, FILE *arquivoDados, unsigned short id) {

    Cliente *c = new Cliente();

    c = ClienteEntrada::recuperaCliente(arquivoDados, TabelaHash::lerIndice(arquivoIndice, id, TabelaHash::geraHash(id)));

    c->exibeDadosCliente();

    rewind(arquivoDados);
    rewind(arquivoIndice);
}

void CrudClientes::alteracao(FILE *arquivoIndice, FILE *arquivoDados, FILE *arquivoID, unsigned short id) {

    Cliente *c = new Cliente();
    ClienteEntrada ce;
    char confirmacao;

    unsigned long int endereco = TabelaHash::lerIndice(arquivoIndice, id, TabelaHash::geraHash(id));

    c = ClienteEntrada::recuperaCliente(arquivoDados, endereco);

    c->exibeDadosCliente();

    std::cout << std::endl;

    c->lerDadosCliente(arquivoID);

    std::cout << "\nDeseja alterar esse cliente? (s/n) ";
    std::cin >> confirmacao;

    if (confirmacao == 'n') {
        rewind(arquivoDados);
        return;
    }

    EntradaIndice *entrada = new EntradaIndice();
    entrada->lapide = '$';
    entrada->id = c->get_id();
    entrada->endereco = ce.armazenaCliente(arquivoDados, c);

    TabelaHash::escreveIndice(arquivoIndice, entrada, TabelaHash::geraHash(c->get_id() - 48));

    rewind(arquivoDados);
    rewind(arquivoIndice);


    // Marcando registro alterado como excluido
    fseek(arquivoDados, endereco, SEEK_SET);
    fputc((byte)'*', arquivoDados);
    fflush(arquivoDados);

    rewind(arquivoDados);
}

void CrudClientes::exclusao(FILE *arquivoIndice, FILE *arquivoDados, unsigned short id) {
    
    Cliente* c = new Cliente();
    char confirmacao;

    unsigned long int endereco = TabelaHash::lerIndice(arquivoIndice, id, TabelaHash::geraHash(id));

    c = ClienteEntrada::recuperaCliente(arquivoDados, endereco);

    c->exibeDadosCliente();

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

void CrudClientes::listar(FILE *arquivoIndice, FILE *arquivoDados, FILE *arquivoID) {

    Cliente *c = new Cliente();

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

        c = ClienteEntrada::recuperaCliente(arquivoDados, TabelaHash::lerIndice(arquivoIndice, id, TabelaHash::geraHash(id)));

        c->exibeDadosCliente();
    }

    std::cout << "Total: " << ultimoID - 48 -1 << " clientes\n" << std::endl;

    rewind(arquivoDados);
    rewind(arquivoIndice);
}