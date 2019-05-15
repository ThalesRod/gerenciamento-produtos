#include "../include/produto.h"

// =========== Metodos Produto ============================

// ======= Getters

unsigned short Produto::get_id() {
	return id;
}

std::string Produto::get_nome() {
	return nome;
}

std::string Produto::get_descricao() {
	return descricao;
}

float Produto::get_preco() {
	return preco;
}

unsigned short Produto::get_idCategoria() {
    return idCategoria;
}

// ======= Setters

void Produto::set_id(unsigned short novoId) {
	id = novoId;
}

void Produto::set_preco(float novoPreco) {
	preco = novoPreco;
}

void Produto::set_append_nome(char c) {
	nome += c;
}

void Produto::set_append_descricao(char c) {
	descricao += c;
}

void Produto::set_idCategoria(unsigned short novoId) {
    idCategoria = novoId;
}
// ======= Metodos de manipulacao de Produto

void Produto::lerDadosProduto(FILE *arquivoID) {


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


	std::cout << "\n=== Dados do Produto ===\n" << std::endl;

    std::cout << "Digite o nome do produto: ";
    std::getline(std::cin, nome);

    std::cout << "Digite uma descricao para o produto: ";
    std::getline(std::cin, descricao);

    std::cout << "Digite o preco do produto: ";
    std::cin >> preco;

    std::cout << "Digite o ID da categoria do produto: ";
    std::cin >> idCategoria;
}

void Produto::exibeDadosProduto(FILE *arquivoIndiceCategorias = NULL, FILE *arquivoDadosCategorias = NULL) {

	if( id == 65535 ) {
		std::cout << "\n=== Produto nao encontrado! ===\n" << std::endl;
		return;
	}
	
	std::cout << "\n=== Produto ===\n" << std::endl;

	std::cout << "Nome: " 		<< nome << std::endl;
	std::cout << "Descricao: "	<< descricao << std::endl;
	std::cout << "Preco: "		<< preco << std::endl;

    if ( arquivoIndiceCategorias != NULL && arquivoDadosCategorias != NULL )
        CrudCategorias::busca(arquivoIndiceCategorias, arquivoDadosCategorias, idCategoria);


    std::cout << std::endl;
}

// =========== Metodos ProdutoEntrada ============================

// ======= Metodos para gravar no arquivo

unsigned long int ProdutoEntrada::armazenaProduto(FILE *arquivoDados, Produto *produto) {

    unsigned long int endereco;

    // Transformando um Produto em uma Entrada de Produto para o arquivo

    // Criando um vetor de bytes com os dados do produto
    vetorDeBytes = produtoParaBytes(produto);

    lapide = ' ';
    tamanhoVetorDeBytes = vetorDeBytes.size();


    // Movendo o ponteiro para o final do arquivo e armazenando esse endereco
    fseek(arquivoDados, 0, SEEK_END);
    endereco = ftell(arquivoDados);


    // Armazenado os bytes da entrada de Produto no arquivo de dados
    
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

std::vector<byte> ProdutoEntrada::produtoParaBytes(Produto* produto) {

    std::vector<byte> novoVetorDeBytes;
    byte separador = '|';

    // Formato: id|nome|descricao|preco

    // Adicionando ID
    novoVetorDeBytes.push_back((byte)produto->get_id());

    novoVetorDeBytes.push_back(separador);


    // Adicionando Nome
	std::string nome = produto->get_nome();

    std::for_each(
    	nome.begin(),
    	nome.end(),
    	[&](char c) { novoVetorDeBytes.push_back( (byte) c ); }
    );

	novoVetorDeBytes.push_back(separador);

    // Adicionando Descricao
	std::string descricao = produto->get_descricao();

	std::for_each(
		descricao.begin(),
		descricao.end(),
		[&](char c) { novoVetorDeBytes.push_back( (byte) c ); }
	);

    novoVetorDeBytes.push_back(separador);

    // Adicionando o preco
    ProdutoEntrada::floatBytesCopy(produto->get_preco(), novoVetorDeBytes);

    novoVetorDeBytes.push_back(separador);

    // Adicionando ID Categoria
    novoVetorDeBytes.push_back((byte)produto->get_idCategoria());

    return novoVetorDeBytes;
}

void ProdutoEntrada::floatBytesCopy(float paramFloat, std::vector<byte> &vetorDeBytes) {

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

Produto* ProdutoEntrada::recuperaProduto(FILE *arquivoDados, unsigned long int endereco) {

    Produto *produtoRecuperado = new Produto();

    // Recebe o valor -1 como erro padrao
    produtoRecuperado->set_id(-1);

    if (endereco == (unsigned long int) -1 )
        return produtoRecuperado;
    
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

        produtoRecuperado = bytesParaProduto(vetorDeBytes);

        free(buffer);
    }

    rewind(arquivoDados);

    return produtoRecuperado;
}

Produto* ProdutoEntrada::bytesParaProduto(std::vector<byte> vetorDeBytes) {

    Produto *produto = new Produto();

 	// Criando um vetor com as posicoes de cada separador no vetor de bytes
    std::vector<short> separadorPos;

    for(unsigned short i=0; i < vetorDeBytes.size(); ++i)
        if (vetorDeBytes[i] == (byte)'|')
                separadorPos.push_back(i);


    // Utilizando o vetor de posicoes dos separadores para separar o vetor de bytes em 4 vetores para os campos
    std::vector<byte> id(vetorDeBytes.begin(), vetorDeBytes.begin() + separadorPos[0]);
    std::vector<byte> nome(vetorDeBytes.begin() + (separadorPos[0] + 1), vetorDeBytes.begin() + separadorPos[1]);
    std::vector<byte> descricao(vetorDeBytes.begin() + (separadorPos[1] + 1), vetorDeBytes.begin() + separadorPos[2]);
    std::vector<byte> preco(vetorDeBytes.begin() + (separadorPos[2] + 1), vetorDeBytes.begin() + separadorPos[3]);
    std::vector<byte> idCategoria(vetorDeBytes.begin() + (separadorPos[3] + 1), vetorDeBytes.end());



    // Armazenado cada vetor em um campo do Produto
    produto->set_id( (unsigned short) id[0] );

    std::for_each(
    	nome.begin(),
    	nome.end(),
    	[&](byte c) { produto->set_append_nome( c ); }
    );

    std::for_each(
    	descricao.begin(),
    	descricao.end(),
    	[&](byte c) { produto->set_append_descricao( c ); }
    );

	// Logica inversa da funcao ProdutoEntrada::floatBytesCopy
	// Usada para recuperar o float a partir dos 4 bytes armazenados no arquivo
    produto->set_preco( (float) int(preco[0] << 24 | preco[1] << 16 | preco[2] << 8 | preco[3]) / 100 );

    produto->set_idCategoria( (unsigned short) idCategoria[0] );

    return produto;
}