#include "header.h"

// Aplica a funcao de hashing por divisao por um numero primo
// Entrada: ID do filme
// Saida: Endereço da TabelaHash
// range da funcao = [0, n-1]; n = Numero Primo
int Hashing(int FilmeID){
    int Chave = FilmeID;
    int NumPrimo = 27997;

    if(Chave > NumPrimo)
        Chave = FilmeID % NumPrimo;

    return Chave;
}

// Realiza a inserção de um genero em uma Lista encadeada de generos
// Entrada: Lista encadeada e uma string
// Saida  : Lista encadeada
PT_GENERO *InsereListaGeneros(PT_GENERO *Lista, char StringGenero[])
{
    PT_GENERO* Aux = Lista;
    PT_GENERO* Novo;

    Novo = malloc(sizeof(PT_GENERO));
    strcpy(Novo->Generos.Genero, StringGenero);
    Novo->Prox = NULL;

    if(Aux == NULL){
        Lista = Novo;
    }
    else{
        while(Aux->Prox != NULL){
            Aux = Aux->Prox;
        }
        Aux->Prox = Novo;
    }
    return Lista;
}

// Criação da lista encadeada e tratamento dos dados de generos
// Entrada: Lista encadeada e o string dos generos nao tratato
// Saida  : Lista encadeada
PT_GENERO *CriaListaGeneros(PT_GENERO *Lista, char StringGeneros[])
{
    char Separador[] = {"|"};
    char *Elemento;

    if(strcmp("(no genres listed)", StringGeneros) != 0)
    {
        Elemento = strtok(StringGeneros, Separador); // Primeiro elemento do string de generos
        // Enquanto tiver generos no string, ou seja, enquanto Elemento não for nulo
        while(Elemento != NULL){
            Lista = InsereListaGeneros(Lista, Elemento); // Insere genero na lista
            Elemento = strtok(NULL, Separador); // Pega o proximo genero do string
        }
    }
    else
        Lista = NULL;
    return Lista;
}

LISTA_FILME_DIF* InsereListaNomeFilme(LISTA_FILME_DIF *Lista, DADO_NOMEFILME NovoFilme)
{
    LISTA_FILME_DIF* Aux = Lista;
    LISTA_FILME_DIF* Anterior = NULL;
    LISTA_FILME_DIF* Novo;

    Novo = malloc(sizeof(LISTA_FILME_DIF));
    Novo->InfoLista = NovoFilme;

    if(Aux == NULL)
    {
        Lista = Novo;
        Novo->Prox = NULL;
    }
    else{
        while(Aux != NULL && Aux->InfoLista.FilmeID != NovoFilme.FilmeID)
        {
            Anterior = Aux;
            Aux = Aux->Prox;
        }
        if(Aux == NULL)
        {
            Anterior->Prox = Novo;
            Novo->Prox = NULL;
        }
    }
    return Lista;
}


// Tratamento do arquivo de entrada 'minirating.csv'
// Trata os dados linha a linha e adiciona na Tabela Hash
void AbreArquivoRating(char NomeArquivo[], FILME_HASH *TabelaHash)
{
    FILE *Arq;
    FILME_HASH Filme;
    int i, Flag = 0;
    unsigned long int ContadorR = 0, ContadorL = 0;
    char Linha[TAM_LINHA];
    char Separador[] = {","};
    char *Elemento;

    Arq = fopen(NomeArquivo, "r");

    if(!Arq)
        printf("Erro na abertura do arquivo '%s'.\n", NomeArquivo);
    else
    {
        fgets(Linha, TAM_LINHA, Arq); // Passa a primeira linha do arquivo
        while(!feof(Arq))
        {
            fgets(Linha, TAM_LINHA, Arq);
            ContadorL++;

            // Inicializa variaveis da estrutura
            Filme = InicializaFilme(Filme);

            Elemento = strtok(Linha, Separador); // ID_Usuario
            Elemento = strtok(NULL, Separador); // FilmeID
            Filme.FilmeID = atoi(Elemento);

            Elemento = strtok(NULL, Separador); // Rating
            Filme.Rating = atof(Elemento);

            // Para nao inserir filme com ID = 0 (????)
            if(Filme.FilmeID != 0)
                InsereTabelaHash(TabelaHash, Filme);
        }
        fclose(Arq);
    }
    // Calcula a media das avaliacoes
    for(i=0; i<TAM_TABELA_HASH_FILME; i++)
    {
        if(TabelaHash[i].FilmeID != -1)
        {
            TabelaHash[i].Rating /= TabelaHash[i].CountRating;
            ContadorR += TabelaHash[i].CountRating; // Calcula a quantidade de avaliacoes na tabela hash
        }
    }
}

// Tratamento do arquivo de entrada 'movie.csv'
// Trata os dados linha a linha, criando a Lista de Generos de cada filme da Tabela Hash
void AbreArquivoMovie(char NomeArquivo[], FILME_HASH *TabelaHash, LISTA_FILME_DIF **ListaNomeFilme)
{
    FILE *Arq;
    int i, IndexTabela, ID, TamString;
    int Contador = 0;
    char Linha[TAM_LINHA];
    char Separadores[] = {";"};
    char *ElementoID, *ElementoGeneros;

    DADO_NOMEFILME DadoNomeFilme;

    Arq = fopen(NomeArquivo, "r");

    if(!Arq)
        printf("Erro na abertura do arquivo '%s'.\n", NomeArquivo);
    else
    {
        fgets(Linha, TAM_LINHA, Arq); // Passa a primeira linha do arquivo.
        while(!feof(Arq) && Contador < 27278)
        {
            fgets(Linha, TAM_LINHA, Arq);
            Contador++;

            // Formata a linha do arquivo 'movie.csv' para retirar as informações importantes
            TrataLinhaMovie(Linha);

            ElementoID = strtok(Linha, Separadores); // FilmeID
            ElementoGeneros = strtok(NULL, Separadores); // Nome do filme (nao utlizado)
            strcpy(DadoNomeFilme.FilmeNome, ElementoGeneros);
            ElementoGeneros = strtok(NULL, Separadores); // String dos generos

            // Calcula o endereco na Tabela Hash do filme
            ID = atoi(ElementoID);
            DadoNomeFilme.FilmeID = ID;

            *ListaNomeFilme = InsereListaNomeFilme(*ListaNomeFilme, DadoNomeFilme);

            IndexTabela = BuscaFilmeHash(TabelaHash, ID);
            if(IndexTabela != -1)
            {
                // Cria uma lista de generos apartir do string ElementoGeneros
                ElementoGeneros = strlwr(ElementoGeneros);
                TabelaHash[IndexTabela].Generos = CriaListaGeneros(TabelaHash[IndexTabela].Generos, ElementoGeneros);
            }
        }
        fclose(Arq);
    }
}

int BuscaFilmeHash(FILME_HASH *TabelaHash, int FilmeID)
{
    unsigned long int IndexHash;

    IndexHash = Hashing(FilmeID);

    // Se PosTabela == ID do filme
    if(TabelaHash[IndexHash].FilmeID == FilmeID){
        return IndexHash;
    }
    else{
        if(TabelaHash[IndexHash].FilmeID != -1){ // Se Filme != Vazio
            while(1)
            {
                // Enquanto (PosTabela != Vazio) E (PosTabela < TamanhoTabela) E (EndHash < TAM_TABELA)
                while((TabelaHash[IndexHash].FilmeID != -1) && (TabelaHash[IndexHash].FilmeID != FilmeID) && IndexHash < TAM_TABELA_HASH_FILME){
                    IndexHash++;
                }
                if(IndexHash == TAM_TABELA_HASH_FILME) // Então IndexHash excedeu o tamanho da tabela
                {
                    IndexHash = 0;
                }
                else
                    break;
            }
        }
        if(TabelaHash[IndexHash].FilmeID == FilmeID) // Se ID do filme da tabela == ID filme novo
        {
            return IndexHash;
        }
        else
            return -1;
    }
}

// Inicializa a Tabela Hash Aberta
// Ou seja: Inicializa as variaveis da estrutura de cada elemento da TabelaHash
void InicializaTabela_Filme(FILME_HASH *TabelaHash){
    int i;
    for(i=0; i<TAM_TABELA_HASH_FILME; i++)
    {
        TabelaHash[i].FilmeID = -1;
        TabelaHash[i].CountRating = 0;
        TabelaHash[i].Generos = NULL;
        TabelaHash[i].Rating = 0;
    }
}

// Inicializa a estrutura FILME_HASH;
FILME_HASH InicializaFilme(FILME_HASH Novo)
{
    Novo.CountRating = 1;
    Novo.Generos = NULL;
    Novo.FilmeID = 0;
    Novo.Rating = 0;

    return Novo;
}

// Insere o filme na Tabela Hash com base no seu ID
// Entrada: Tabela Hash e um filme
// Saida  : Tabela Hash
void InsereTabelaHash(FILME_HASH *TabelaHash, FILME_HASH Novo)
{
    int IndexHash, i, Contador;

    IndexHash = Hashing(Novo.FilmeID); // calcula o endereco do filme na Tabela Hash

    // Se PosTabela == ID do filme
    if(TabelaHash[IndexHash].FilmeID == Novo.FilmeID){
        TabelaHash[IndexHash].Rating += Novo.Rating;
        TabelaHash[IndexHash].CountRating++;
    }
    else{
        if(TabelaHash[IndexHash].FilmeID != -1){ // Se Filme != Vazio
            while(1)
            {
                // Enquanto (PosTabela != Vazio) E (PosTabela < TamanhoTabela) E (EndHash < TAM_TABELA)
                while((TabelaHash[IndexHash].FilmeID != -1) && (TabelaHash[IndexHash].FilmeID != Novo.FilmeID) && IndexHash < TAM_TABELA_HASH_FILME){
                    IndexHash++;
                }
                if(IndexHash == TAM_TABELA_HASH_FILME) // Então IndexHash excedeu o tamanho da tabela
                {
                    IndexHash = 0;
                }
                else
                    break;
            }
        }
        if(TabelaHash[IndexHash].FilmeID == Novo.FilmeID) // Se ID do filme da tabela == ID filme novo
        { // Atualiza variaveis do filme
            TabelaHash[IndexHash].Rating += Novo.Rating;
            TabelaHash[IndexHash].CountRating++;
        }
        else // Senao adiciona um novo filme na tabela
            TabelaHash[IndexHash] = Novo;
    }
}

// Funcao TrataLinhaMovie;
// Entrada: string que corresponde a linha do arquivo de Rating
// Saida  : string trata para retirada das informacoes
void TrataLinhaMovie(char Linha[])
{
    int i, TamLinha;
    TamLinha = strlen(Linha); // Tamanho do string Linha
    for(i=0; i<TamLinha; i++)
        if(Linha[i] == '"')
            Linha[i] = ';';
        else if(Linha[i] == ',' && Linha[i-1] == ';') // Quando o caracter ',' não está no nome, logo era separador
            Linha[i] = ';';
}

// Printa os elementos da Lista de generos para o usuario
void PrintaListaGeneros(PT_GENERO *Lista)
{
    PT_GENERO *Aux = Lista;

    printf("Lista de Generos:[");
    while(Aux != NULL)
    {
        printf("%s, ", Aux->Generos.Genero);
        Aux = Aux->Prox;
    }
    printf("]\n");
}

// Printa as variaveis da estrutura LISTA_FILMEHASH_RETORNO
void PrintaFilme(DADO_HASH_RETORNO Filme)
{
    printf("NomeFilme: %s\n", Filme.NomeFilme);
    PrintaListaGeneros(Filme.Generos);
    printf("Rating: %lf\n", Filme.Rating);
    printf("CountRating: %d\n\n", Filme.CountRating);
}

int VerificaGeneroBuscado(PT_GENERO *ListaGeneros, char GeneroBuscado[])
{
    PT_GENERO* Aux = ListaGeneros;
    PT_GENERO* Anterior = NULL;

    if(Aux == NULL)
    {
        return 0;
    }
    else
    {
        while(Aux != NULL && strcmp(GeneroBuscado, Aux->Generos.Genero) != 0)
        {
            Anterior = Aux;
            Aux = Aux->Prox;
        }
        if(Aux == NULL)
            return 0;
        else
            return 1;
    }
}

LISTA_FILMEHASH_RETORNO *InsereFilmeHash(LISTA_FILMEHASH_RETORNO *Lista, DADO_HASH_RETORNO NovoFilme)
{
    LISTA_FILMEHASH_RETORNO* Aux = Lista;
    LISTA_FILMEHASH_RETORNO* Novo;

    Novo = malloc(sizeof(LISTA_FILMEHASH_RETORNO));
    Novo->InfoLista = NovoFilme;

    if(Aux == NULL)
    {
        Lista = Novo;
        Novo->Prox = NULL;
    }
    else{
        while(Aux->Prox != NULL)
        {
            Aux = Aux->Prox;
        }
        Aux->Prox = Novo;
        Novo->Prox = NULL;
    }
    return Lista;
}

DADO_HASH_RETORNO* AlocaVetor(int TamVetor){
    DADO_HASH_RETORNO *Vetor = NULL;

    Vetor = (DADO_HASH_RETORNO*)malloc(TamVetor * sizeof(DADO_HASH_RETORNO));

    return Vetor;
}


int Partition(DADO_HASH_RETORNO *vetor, int Inicio, int Final){
    int esquerda = 1;
    DADO_HASH_RETORNO pivo;

    pivo = vetor[Inicio];

    while(Inicio < Final){
        if(esquerda == 1){
            if(pivo.Rating >= vetor[Final].Rating){
                vetor[Inicio] = vetor[Final];
                Inicio++;
                esquerda = 0;
            }
            else{
                Final--;
            }
        }
        else{
            if(pivo.Rating < vetor[Inicio].Rating){
                vetor[Final] = vetor[Inicio];
                Final--;
                esquerda = 1;
            }
            else{
                Inicio++;
            }
        }
    }
    vetor[Inicio] = pivo;

    return Inicio;
}

void QuickSort(FILME_HASH *Vetor, int Inicio, int Final){
    int PosPivo;

    if(Final > Inicio){
        PosPivo = Partition(Vetor, Inicio, Final);

        QuickSort(Vetor, Inicio, PosPivo - 1);
        QuickSort(Vetor, PosPivo + 1, Final);
    }
}

// Funcao BuscaPorGenero
// Entrada: Lista de filmes da Tabela Hash, Quantidade de filmes solicitados, Genero buscado, TabelaHash
// Saida: Lista de filmes decrescente por Rating;
LISTA_FILMEHASH_RETORNO *BuscaPorGenero(LISTA_FILMEHASH_RETORNO *Lista, int Quant, char GeneroBuscado[], FILME_HASH *TabelaHash, LISTA_FILME_DIF *ListaNomeFilme)
{
    int Index, i;
    int QuantidadeFilmes = Quant;
    int TamVetor = 0;
    int Retorno;
    char NomeFilme[TAM_NOME];
    DADO_HASH_RETORNO DadoRetorno;

    DADO_HASH_RETORNO *Vetor = NULL;
    LISTA_FILMEHASH_RETORNO *ListaAux = NULL;

    GeneroBuscado = strlwr(GeneroBuscado);

    for(Index=0; Index<TAM_TABELA_HASH_FILME; Index++)
    {
        if(TabelaHash[Index].FilmeID != -1 && TabelaHash[Index].CountRating > 999)
        {
            if(VerificaGeneroBuscado(TabelaHash[Index].Generos, GeneroBuscado) == 1)
            {
                Retorno = ProcuraListaNome(ListaNomeFilme, TabelaHash[Index].FilmeID, &NomeFilme);

                DadoRetorno.CountRating = TabelaHash[Index].CountRating;
                DadoRetorno.FilmeID = TabelaHash[Index].FilmeID;
                DadoRetorno.Generos = TabelaHash[Index].Generos;
                DadoRetorno.Rating = TabelaHash[Index].Rating;
                strcpy(DadoRetorno.NomeFilme, NomeFilme);

                ListaAux = InsereFilmeHash(ListaAux, DadoRetorno);
                TamVetor++; // Calcula o tamanho do vetor auxiliar utilizado para ordenação
            }
        }
    }
    if(ListaAux != NULL) // Se existir filmes com o genero buscado
    {
        Vetor = AlocaVetor(TamVetor); // Aloca o vetor auxiliar na memoria

        i = 0;
        while(ListaAux != NULL)
        {
            Vetor[i] = ListaAux->InfoLista;
            ListaAux = ListaAux->Prox;
            i++;
        }

        QuickSort(Vetor, 0, TamVetor-1); // Organiza o vetor de filmes pelo Rating

        // Trecho da função que trata a Lista de retorno
        // Insere na Lista de retorno a partir do ultimo elemento
        // Assim a Lista estará em ordem decrescente
        i = TamVetor;
        while(QuantidadeFilmes > 0)
        {
            i--;
            Lista = InsereFilmeHash(Lista, Vetor[i]);
            QuantidadeFilmes--;
        }
    }
    return Lista;
}

// Printa uma lista de filmes do tipo FILME_HASH
// Utilizada apos a função de Busca por Genero
void PrintaListaFilmeHash(LISTA_FILMEHASH_RETORNO *Lista)
{
    LISTA_FILMEHASH_RETORNO *Aux = Lista;

    if(Lista == NULL){
        printf("Sem resultados\n");
    }
    else{
        while(Aux != NULL){
            PrintaFilme(Aux->InfoLista);
            Aux = Aux->Prox;
        }
    }
}

void PrintaListaFilmeNome(LISTA_FILME_DIF *Lista)
{
    LISTA_FILME_DIF *Aux = Lista;

    if(Lista == NULL){
        printf("Sem resultados\n");
    }
    else{
        while(Aux != NULL){
            printf("FilmeID: %d\n", Aux->InfoLista.FilmeID);
            printf("NomeFilme: %s\n\n", Aux->InfoLista.FilmeNome);
            getchar();
            Aux = Aux->Prox;
        }
    }
}



