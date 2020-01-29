#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM_LINHA 100
#define TAM_ELEMENTO 30
#define TAM_NOME 100
#define TAM_GENERO 30
#define TAM_TABELA_HASH 29000

/// ********************************************************************
///                         Informações da Tabela Hash;
/// ********************************************************************

// Informações da Lista Encadeada de Generos
struct INFO_GENERO{
    char Genero[TAM_GENERO];
};
typedef struct INFO_GENERO GENEROS;

// Lista Encadeada dos Generos dos Filmes
// Contem:
// - Lista encadeada de Generos;
// - Ponteiro para o proximo genero;
struct PONTEIRO_GENERO{
    GENEROS Generos;
    struct PONTEIRO_GENERO *Prox;
};
typedef struct PONTEIRO_GENERO PT_GENERO;

// --------------------------------------------------------------------------------------------
// Elementos da Tabela Hash: cada elemento da tabela é uma estrutura do tipo: FILME_HASH
// Cada elemento possui:
// - O ID do filme: FilmeID;
// - A quantidade de avaliações do filme: CountRating;
// - A avaliação media do filme: Rating;
// - Uma lista encadeada com os generos do filme: Generos;

struct INFO_HASH{
    int FilmeID; // Usado como chave da Tabela Hash
    int CountRating; // Quantidade de avaliações do filme
    double Rating;
    GENEROS *Generos; // Lista encadeada dos generos do filme
};
typedef struct INFO_HASH FILME_HASH;


// Inicializa a Tabela Hash Aberta
void InicializaTabela(FILME_HASH *TabelaHash);
void AbreArquivoRating(char NomeArquivo[], FILME_HASH *TabelaHash);
void AbreArquivoMovie(char NomeArquivo[], FILME_HASH *TabelaHash);
void InsereTabelaHash(FILME_HASH *TabelaHash, FILME_HASH Novo);
void PrintaFilme(FILME_HASH Filme);
int Hashing(int FilmeID);
FILME_HASH InicializaFilme(FILME_HASH Novo);
PT_GENERO *CriaListaGeneros(PT_GENERO *Lista, char Elemento[]);


