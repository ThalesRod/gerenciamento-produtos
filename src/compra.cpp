#include "../include/compra.h"

// =========== Metodos Compra ============================

// ======= Getters

unsigned short Compra::get_id() {
	return id;
}

std::string Compra::get_dataCompra() {
	return dataCompra;
}

float Compra::get_preco() {
	return preco;
}

unsigned short Compra::get_idCliente() {
    return idCliente;
}

unsigned short Compra::get_idProduto() {
    return idProduto;
}

unsigned short Compra::get_quantidadeProduto() {
    return quantidadeProduto;
}

// ======= Setters

void Compra::set_id(unsigned short novoId) {
	id = novoId;
}

void Compra::set_preco(float novoPreco) {
	preco = novoPreco;
}

void Compra::set_append_dataCompra(char c) {
	dataCompra += c;
}

void Compra::set_idCliente(unsigned short novoId) {
    idCliente = novoId;
}

void Compra::set_idProduto(unsigned short novoId) {
    idProduto = novoId;
}

void Compra::set_quantidadeProduto(unsigned short novaQuantidade) {
    quantidadeProduto = novaQuantidade;
}

// ======= Metodos de manipulacao de Compra

void Compra::lerDadosCompra(FILE *arquivoID) {


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


	std::cout << "\n=== Dados da Compra ===\n" << std::endl;

    std::cout << "Digite a data da compra: ";
    std::getline(std::cin, dataCompra);

    std::cout << "Digite o preco do compra: ";
    std::cin >> preco;

    std::cout << "Digite o ID do cliente da compra: ";
    std::cin >> idCliente;
}

void Compra::exibeDadosCompra(FILE *arquivoIndiceClientes = NULL, FILE *arquivoDadosClientes = NULL, FILE *arquivoIndice = NULL, FILE *arquivoDados = NULL, FILE *arquivoIndiceCategorias = NULL, FILE *arquivoDadosCategorias = NULL) {

	if( id == 65535 ) {
		std::cout << "\n=== Compra nao encontrada! ===\n" << std::endl;
		return;
	}
	
	std::cout << "\n=== Compra ===\n" << std::endl;

	std::cout << "Nome: " 		<< dataCompra << std::endl;
	std::cout << "Preco: "		<< preco << std::endl;

    if ( arquivoIndiceClientes != NULL && arquivoDadosClientes != NULL )
        CrudClientes::busca(arquivoIndiceClientes, arquivoDadosClientes, idCliente);

    if ( arquivoIndice != NULL && arquivoDados != NULL && arquivoIndiceCategorias != NULL && arquivoDadosCategorias != NULL ) {
        CrudProdutos::busca(arquivoIndice, arquivoDados, arquivoIndiceCategorias, arquivoDadosCategorias, idProduto);
    }

    std::cout << std::endl;
}

// =========== Metodos CompraEntrada ============================

// ======= Metodos para gravar no arquivo

unsigned long int CompraEntrada::armazenaCompra(FILE *arquivoDados, Compra *compra) {

    unsigned long int endereco;

    // Transformando um Compra em uma Entrada de Compra para o arquivo

    // Criando um vetor de bytes com os dados do compra
    vetorDeBytes = compraParaBytes(compra);

    lapide = ' ';
    tamanhoVetorDeBytes = vetorDeBytes.size();


    // Movendo o ponteiro para o final do arquivo e armazenando esse endereco
    fseek(arquivoDados, 0, SEEK_END);
    endereco = ftell(arquivoDados);


    // Armazenado os bytes da entrada de Compra no arquivo de dados
    
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

std::vector<byte> CompraEntrada::compraParaBytes(Compra* compra) {

    std::vector<byte> novoVetorDeBytes;
    byte separador = '|';

    // Formato: id|dataCompra|descricao|preco

    // Adicionando ID
    novoVetorDeBytes.push_back((byte)compra->get_id());

    novoVetorDeBytes.push_back(separador);


    // Adicionando Nome
	std::string dataCompra = compra->get_dataCompra();

    std::for_each(
    	dataCompra.begin(),
    	dataCompra.end(),
    	[&](char c) { novoVetorDeBytes.push_back( (byte) c ); }
    );

	novoVetorDeBytes.push_back(separador);

    // Adicionando o preco
    CompraEntrada::floatBytesCopy(compra->get_preco(), novoVetorDeBytes);

    novoVetorDeBytes.push_back(separador);

    // Adicionando ID Cliente
    novoVetorDeBytes.push_back((byte)compra->get_idCliente());

    novoVetorDeBytes.push_back(separador);

    // Adicionando ID Produto
    novoVetorDeBytes.push_back((byte)compra->get_idProduto());

    novoVetorDeBytes.push_back(separador);

    // Adicionando quantidade Produto
    novoVetorDeBytes.push_back((byte)compra->get_quantidadeProduto());

    return novoVetorDeBytes;
}

void CompraEntrada::floatBytesCopy(float paramFloat, std::vector<byte> &vetorDeBytes) {

	// Transforma o float em 4 bytes separados e os armazena no vetor de bytes
	// Na logica da funcao o float eh multiplicado por 100 para transforma-lo em um inteiro.
	// Pelo float no sistema sempre se tratar de um preco com duas casa decimais essa logica
	// eh valida.

    int paramInt = paramFloat * 100;

    std::vector<byte> arrayOfByte(4);

    for (int i = 0; i < 4; i++)
        arrayOfByte[3 - i] = (paramInt >> (i * 8));


    for(short i=0;i<4;++i)
        vetorDeBytes.push_back(arrayOfByte[i]);
}

// ======= Metodos para ler do arquivo

Compra* CompraEntrada::recuperaCompra(FILE *arquivoDados, unsigned long int endereco) {

    Compra *compraRecuperado = new Compra();

    // Recebe o valor -1 como erro padrao
    compraRecuperado->set_id(-1);

    if (endereco == (unsigned long int) -1 )
        return compraRecuperado;
    
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

        compraRecuperado = bytesParaCompra(vetorDeBytes);

        free(buffer);
    }

    rewind(arquivoDados);

    return compraRecuperado;
}

Compra* CompraEntrada::bytesParaCompra(std::vector<byte> vetorDeBytes) {

    Compra *compra = new Compra();

 	// Criando um vetor com as posicoes de cada separador no vetor de bytes
    std::vector<short> separadorPos;

    for(unsigned short i=0; i < vetorDeBytes.size(); ++i)
        if (vetorDeBytes[i] == (byte)'|')
                separadorPos.push_back(i);


    // Utilizando o vetor de posicoes dos separadores para separar o vetor de bytes em 4 vetores para os campos
    std::vector<byte> id(vetorDeBytes.begin(), vetorDeBytes.begin() + separadorPos[0]);
    std::vector<byte> dataCompra(vetorDeBytes.begin() + (separadorPos[0] + 1), vetorDeBytes.begin() + separadorPos[1]);
    std::vector<byte> preco(vetorDeBytes.begin() + (separadorPos[1] + 1), vetorDeBytes.begin() + separadorPos[2]);
    std::vector<byte> idCliente(vetorDeBytes.begin() + (separadorPos[2] + 1), vetorDeBytes.begin() + separadorPos[3]);
    std::vector<byte> idProduto(vetorDeBytes.begin() + (separadorPos[3] + 1), vetorDeBytes.begin() + separadorPos[4]);
    std::vector<byte> quantidadeProduto(vetorDeBytes.begin() + (separadorPos[4] + 1), vetorDeBytes.end());



    // Armazenado cada vetor em um campo do Compra
    compra->set_id( (unsigned short) id[0] );

    std::for_each(
    	dataCompra.begin(),
    	dataCompra.end(),
    	[&](byte c) { compra->set_append_dataCompra( c ); }
    );

	// Logica inversa da funcao CompraEntrada::floatBytesCopy
	// Usada para recuperar o float a partir dos 4 bytes armazenados no arquivo
    compra->set_preco( (float) int(preco[0] << 24 | preco[1] << 16 | preco[2] << 8 | preco[3]) / 100 );

    compra->set_idCliente( (unsigned short) idCliente[0] );

    compra->set_idProduto( (unsigned short) idProduto[0] );

    compra->set_quantidadeProduto( (unsigned short) quantidadeProduto[0] );

    return compra;
}