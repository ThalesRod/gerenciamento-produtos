#include "../include/categoria.h"

// =========== Metodos Categoria ============================

// ======= Getters

unsigned short Categoria::get_id() {
	return id;
}

std::string Categoria::get_nome() {
	return nome;
}

// ======= Setters

void Categoria::set_id(unsigned short novoId) {
	id = novoId;
}

void Categoria::set_append_nome(char c) {
	nome += c;
}

// ======= Metodos de manipulacao de Categoria

void Categoria::lerDadosCategoria(FILE *arquivoID) {


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


	std::cout << "\n=== Dados da Categoria ===\n" << std::endl;

    std::cout << "Digite o nome da categoria: ";
    std::getline(std::cin, nome);
}

void Categoria::exibeDadosCategoria() {

	if( id == 65535 ) {
		std::cout << "\n=== Categoria nao existe! ===\n" << std::endl;
		return;
	}
	
	std::cout << "\n=== Categoria ===\n" << std::endl;

	std::cout << "Nome: " 		<< nome << std::endl;

    std::cout << std::endl;
}

// =========== Metodos CategoriaEntrada ============================

// ======= Metodos para gravar no arquivo

unsigned long int CategoriaEntrada::armazenaCategoria(FILE *arquivoDados, Categoria *categoria) {

    unsigned long int endereco;

    // Transformando uma Categoria em uma Entrada de Categoria para o arquivo

    // Criando um vetor de bytes com os dados da Categoria
    vetorDeBytes = categoriaParaBytes(categoria);

    lapide = ' ';
    tamanhoVetorDeBytes = vetorDeBytes.size();


    // Movendo o ponteiro para o final do arquivo e armazenando esse endereco
    fseek(arquivoDados, 0, SEEK_END);
    endereco = ftell(arquivoDados);


    // Armazenado os bytes da entrada de Categoria no arquivo de dados
    
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

std::vector<byte> CategoriaEntrada::categoriaParaBytes(Categoria *categoria) {

    std::vector<byte> novoVetorDeBytes;
    byte separador = '|';

    // Formato: id|nome|descricao|preco

    // Adicionando ID
    novoVetorDeBytes.push_back((byte)categoria->get_id());

    novoVetorDeBytes.push_back(separador);


    // Adicionando Nome
	std::string nome = categoria->get_nome();

    std::for_each(
    	nome.begin(),
    	nome.end(),
    	[&](char c) { novoVetorDeBytes.push_back( (byte) c ); }
    );

    return novoVetorDeBytes;
}

// ======= Metodos para ler do arquivo

Categoria* CategoriaEntrada::recuperaCategoria(FILE *arquivoDados, unsigned long int endereco) {

    Categoria *categoriaRecuperado = new Categoria();

    // Recebe o valor -1 como erro padrao
    categoriaRecuperado->set_id(-1);

    if (endereco == (unsigned long int) -1 )
        return categoriaRecuperado;

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

        categoriaRecuperado = bytesParaCategoria(vetorDeBytes);

        free(buffer);
    }

    rewind(arquivoDados);

    return categoriaRecuperado;
}

Categoria* CategoriaEntrada::bytesParaCategoria(std::vector<byte> vetorDeBytes) {

    Categoria *categoria = new Categoria();

 	// Criando um vetor com as posicoes de cada separador no vetor de bytes
    std::vector<short> separadorPos;

    for(unsigned short i=0; i < vetorDeBytes.size(); ++i)
        if (vetorDeBytes[i] == (byte)'|')
                separadorPos.push_back(i);


    // Utilizando o vetor de posicoes dos separadores para separar o vetor de bytes em 4 vetores para os campos
    std::vector<byte> id(vetorDeBytes.begin(), vetorDeBytes.begin() + separadorPos[0]);
    std::vector<byte> nome(vetorDeBytes.begin() + (separadorPos[0] + 1), vetorDeBytes.end());

    // Armazenado cada vetor em um campo do Categoria
    categoria->set_id( (unsigned short) id[0] );

    std::for_each(
    	nome.begin(),
    	nome.end(),
    	[&](byte c) { categoria->set_append_nome( c ); }
    );

    return categoria;
}