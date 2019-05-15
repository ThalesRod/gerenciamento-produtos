#include "../include/cliente.h"

// =========== Metodos Cliente ============================

// ======= Getters

unsigned short Cliente::get_id() {
	return id;
}

std::string Cliente::get_nome() {
	return nome;
}

std::string Cliente::get_email() {
	return email;
}

// ======= Setters

void Cliente::set_id(unsigned short novoId) {
	id = novoId;
}

void Cliente::set_append_nome(char c) {
	nome += c;
}

void Cliente::set_append_email(char c) {
	email += c;
}

// ======= Metodos de manipulacao de Cliente

void Cliente::lerDadosCliente(FILE *arquivoID) {


	// Funcao lambda para ler o ID de um arquivo e incrementa-lo
	auto lerId = 
	[](FILE *arquivoID) {
    	unsigned short id;

		rewind(arquivoID);
		id = (unsigned short)fgetc(arquivoID);
		
		rewind(arquivoID);
		fputc((byte) id + 1, arquivoID);
		rewind(arquivoID);
		
		return id;
	};

	id = lerId(arquivoID);


	std::cout << "\n=== Dados do Cliente ===\n" << std::endl;

    std::cout << "Digite o nome do cliente: ";
    std::getline(std::cin, nome);

    std::cout << "Digite o email para o cliente: ";
    std::getline(std::cin, email);
}

void Cliente::exibeDadosCliente() {

	if( id == 65535 ) {
		std::cout << "\n=== Cliente nao encontrado! ===\n" << std::endl;
		return;
	}
	
	std::cout << "\n=== Cliente ===\n" << std::endl;

    std::cout << "Nome: "       << nome << std::endl;
	std::cout << "Email: "	<< email << std::endl;

    std::cout << std::endl;
}

// =========== Metodos ClienteEntrada ============================

// ======= Metodos para gravar no arquivo

unsigned long int ClienteEntrada::armazenaCliente(FILE *arquivoDados, Cliente *cliente) {

    unsigned long int endereco;

    // Transformando um Cliente em uma Entrada de Cliente para o arquivo

    // Criando um vetor de bytes com os dados do cliente
    vetorDeBytes = clienteParaBytes(cliente);

    lapide = ' ';
    tamanhoVetorDeBytes = vetorDeBytes.size();


    // Movendo o ponteiro para o final do arquivo e armazenando esse endereco
    fseek(arquivoDados, 0, SEEK_END);
    endereco = ftell(arquivoDados);


    // Armazenado os bytes da entrada de Cliente no arquivo de dados
    
    fputc((byte)lapide, arquivoDados);

    // Utilizando Binary Shift Right (operador ">>") para transformar um
    // unsigned short (tamanhoVetorDeBytes) que possui 2 bytes em 
    // dois bytes separados e armazena-los no arquivo de dados.  
    fputc((byte)(tamanhoVetorDeBytes >> 8), arquivoDados);
    fputc((byte)(tamanhoVetorDeBytes >> 0), arquivoDados);

    // Aqui armazena o proprio vetor de bytes
    fwrite (&vetorDeBytes[0], sizeof(std::vector<byte>::value_type), tamanhoVetorDeBytes, arquivoDados);


    rewind(arquivoDados);

    return endereco;
}

std::vector<byte> ClienteEntrada::clienteParaBytes(Cliente* cliente) {

    std::vector<byte> novoVetorDeBytes;
    byte separador = '|';

    // Formato: id|nome|descricao|preco

    // Adicionando ID
    novoVetorDeBytes.push_back((byte)cliente->get_id());

    novoVetorDeBytes.push_back(separador);

    // Adicionando Nome
	std::string nome = cliente->get_nome();

    std::for_each(
    	nome.begin(),
    	nome.end(),
    	[&](char c) { novoVetorDeBytes.push_back( (byte) c ); }
    );

	novoVetorDeBytes.push_back(separador);

    // Adicionando Email
	std::string email = cliente->get_email();

	std::for_each(
		email.begin(),
		email.end(),
		[&](char c) { novoVetorDeBytes.push_back( (byte) c ); }
	);

    return novoVetorDeBytes;
}

// ======= Metodos para ler do arquivo

Cliente* ClienteEntrada::recuperaCliente(FILE *arquivoDados, unsigned long int endereco) {

    Cliente *clienteRecuperado = new Cliente();

    // Recebe o valor -1 como erro padrao
    clienteRecuperado->set_id(-1);

    if (endereco == (unsigned long int) -1 )
        return clienteRecuperado;

    fseek(arquivoDados, endereco, SEEK_SET);
    
    // lapide = fgetc(arquivoDados);

    if ( fgetc(arquivoDados) == (byte)' ' )
    {
        // Recuperando o tamanho do vetor de bytes do arquivo
	    // utilizando Binary Shift Left (operador "<<") para
	    // transformar os dois bytes separados armazenados no
	    // arquivo de dados em um unsigned short (tamanhoEntrada)
	    // que possui 2 bytes.
        unsigned short tamanhoEntrada = short(fgetc(arquivoDados) << 8 | fgetc(arquivoDados));

        byte* buffer = (byte*)malloc(tamanhoEntrada);
        std::vector<byte> vetorDeBytes;

        fread(buffer, tamanhoEntrada, 1, arquivoDados);

        for (short i=0; i<tamanhoEntrada; ++i)
            vetorDeBytes.push_back(buffer[i]);

        clienteRecuperado = bytesParaCliente(vetorDeBytes);

        free(buffer);
    }

    rewind(arquivoDados);

    return clienteRecuperado;
}

Cliente* ClienteEntrada::bytesParaCliente(std::vector<byte> vetorDeBytes) {

    Cliente *cliente = new Cliente();

 	// Criando um vetor com as posicoes de cada separador no vetor de bytes
    std::vector<short> separadorPos;

    for(unsigned short i=0; i < vetorDeBytes.size(); ++i)
        if (vetorDeBytes[i] == (byte)'|')
                separadorPos.push_back(i);


    // Utilizando o vetor de posicoes dos separadores para separar o vetor de bytes em 4 vetores para os campos
    std::vector<byte> id(vetorDeBytes.begin(), vetorDeBytes.begin() + separadorPos[0]);
    std::vector<byte> nome(vetorDeBytes.begin() + (separadorPos[0] + 1), vetorDeBytes.begin() + separadorPos[1]);
    std::vector<byte> email(vetorDeBytes.begin() + (separadorPos[1] + 1), vetorDeBytes.end());



    // Armazenado cada vetor em um campo do Cliente
    cliente->set_id( (unsigned short) id[0] );

    std::for_each(
    	nome.begin(),
    	nome.end(),
    	[&](byte c) { cliente->set_append_nome( c ); }
    );

    std::for_each(
    	email.begin(),
    	email.end(),
    	[&](byte c) { cliente->set_append_email( c ); }
    );


    return cliente;
}