#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM_LINHA 70
#define TAM_ELEMENTO 30
#define TAM_NOME 100
#define TAM_TABELA_HASH 28000

/// Informações da Tabela Hash;
// Informações da Lista Encadeada de Generos
struct INFO_GENERO{
    char Genero[TAM_NOME]
};
typedef struct INFO_GENERO GENEROS;

// Lista Encadeada dos Generos dos Filmes
struct PONTEIRO_GENERO{
    GENEROS Generos;
    struct PONTEIRO_GENERO *Prox;
};
typedef struct PONTEIRO_GENERO PT_GENERO;

// Informações dos elementos da Tabela Hash
struct INFO_HASH{
    double Rating;
    int CountRating; // Quantidade de avaliações do filme
    int IDFilme; // Usado como chave da Tabela Hash
    GENEROS *Generos; // Lista encadeada dos generos do filme
};
typedef struct INFO_HASH FILME_HASH;



// Inicializa a Tabela Hash Aberta
void InicializaTabela(FILME_HASH *TabelaHash){
    int i;
    for(i=0; i<TAM_TABELA_HASH; i++)
    {
        TabelaHash[i].IDFilme = -1;
        TabelaHash[i].CountRating = 0;
        TabelaHash[i].Generos = NULL;
        TabelaHash[i].Rating = 0;
    }
}

int Hashing(int FilmeID){
    int i;
    int Chave;
    int NumPrimo = 27997;

    Chave = FilmeID % NumPrimo;

    return Chave;
}

FILME_HASH InicializaFilme(FILME_HASH Novo)
{
    Novo.CountRating = 1;
    Novo.Generos = NULL;
    Novo.IDFilme = 0;
    Novo.Rating = 0;

    return Novo;
}

void InsereTabelaHash(FILME_HASH *TabelaHash, FILME_HASH Novo)
{
    int IndexHash;

    IndexHash = Hashing(Novo.IDFilme);

    if(TabelaHash[IndexHash].IDFilme == Novo.IDFilme)
    {
        TabelaHash[IndexHash].Rating += Novo.Rating;
        TabelaHash[IndexHash].CountRating++;
    }
    else
    {
        if(TabelaHash[IndexHash].IDFilme != -1)
            while(1)
            {
                while(TabelaHash[IndexHash].IDFilme != -1 && IndexHash < TAM_TABELA_HASH)
                    IndexHash++;

                if(IndexHash == TAM_TABELA_HASH)
                    IndexHash = 0;
                else
                    break;
            }
        TabelaHash[IndexHash] = Novo;
    }
}

void PrintaFilme(FILME_HASH Filme)
{
    printf("Filme ID: %d\n", Filme.IDFilme);
    printf("Rating: %lf\n", Filme.Rating);
    printf("CountRating: %d\n\n", Filme.CountRating);
}


int main()
{
    FILE* Arq;
    FILME_HASH TabelaHash[TAM_TABELA_HASH];
    int i, Contador = 0;
    char Linha[TAM_LINHA];
    char SeparadorRating[] = {","};
    char *Elemento;

    FILME_HASH Filme;

    InicializaTabela(TabelaHash);

    Arq = fopen("minirating.csv", "r");

    if(!Arq)
        printf("Erro na abertura do arquivo 'minirating.csv'\n");
    else
    {
        // rewind(Arq);
        fgets(Linha, TAM_LINHA, Arq); // Passa a primeira linha do arquivo
        while(!feof(Arq))
        {
            fgets(Linha, TAM_LINHA, Arq);

            // Inicializa variaveis da estrutura
            Filme = InicializaFilme(Filme);

            Elemento = strtok(Linha, SeparadorRating); // ID_Usuario
            Elemento = strtok(NULL, SeparadorRating); // IDFilme
            Filme.IDFilme = atoi(Elemento);

            Elemento = strtok(NULL, SeparadorRating); // Rating
            Filme.Rating = atof(Elemento);

            if(Filme.IDFilme != 0)
                InsereTabelaHash(TabelaHash, Filme);
        }
        fclose(Arq);
    }

    // TESTES
    for(i=0; i<TAM_TABELA_HASH; i++)
    {
        if(TabelaHash[i].IDFilme != -1)
        {
            TabelaHash[i].Rating /= TabelaHash[i].CountRating;
            //PrintaFilme(TabelaHash[i]);
            Contador += TabelaHash[i].CountRating;
        }
    }
    printf("%d", Contador);

    return 0;
}
