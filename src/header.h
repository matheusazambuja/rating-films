#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>

#define LINHA 300
#define ALPHABET_SIZE 120
#define TAM_GENERO_BUSCADO 100
#define TAM_TAGS_BUSCADA 200
#define TAM_LINHA 300
#define TAM_ELEMENTO 30
#define TAM_NOME 250
#define TAM_GENERO 30
#define TAM_TAG 100
#define TAM_TABELA_HASH_FILME 29000
#define TAM_TABELA_HASH_TAG 29000

/// ===========================================
///    Informacoes da Tabela Hash de filmes
/// ===========================================

// Informações da Lista Encadeada de Generos;
typedef struct{
    char Genero[TAM_GENERO];
}INFO_GENEROS;

// Lista Encadeada dos Generos dos Filmes
// Contem os seguintes elementos:
// - INFO_GENEROS: Struct com as informacoes da lista em questao
// - Ponteiro para o proximo genero;
struct LISTA_GENERO{
    INFO_GENEROS InfoLista;
    struct PONTEIRO_GENERO *Prox;
};
typedef struct LISTA_GENERO LISTA_GENERO;

// --------------------------------------------------------------------------------------------
// Elementos da Tabela Hash de Filmes: cada elemento da tabela é uma estrutura do tipo: FILME_HASH
// Cada elemento da tabela possui:
// - Numero inteiro: Filme ID
// - Numero inteiro: CountRating
// - Numero double: Rating
// - Lista encadeada: String dos generos do filme
typedef struct{
    int FilmeID;
    int CountRating;
    double Rating;
    LISTA_GENERO *Generos;
}INFO_HASH_FILME;

// Lista encadeada:
// Contem as sequintes informacoes:
// - INFO_HASH_FILME: Struct com as informacoes da lista em questao
// - Ponteiro: Proximo elemento
struct LISTA_FILME_HASH{
    INFO_HASH_FILME InfoLista;
    struct PONTEIRO_FILME_HASH *Prox;
};
typedef struct LISTA_FILME_HASH LISTA_FILME_HASH;

// Igual a estrutura da Tabela Hash de Filmes: + o string do nome do filme;
// Usada para retorno da pesquisa realizada
// Cada elemento da tabela possui:
// - Numero inteiro: Filme ID
// - Numero inteiro: CountRating
// - Numero double: Rating
// - String: Nome do filme
// - Lista encadeada: String dos generos do filme
typedef struct{
    int FilmeID;
    int CountRating;
    double Rating;
    char NomeFilme[TAM_NOME];
    LISTA_GENERO *Generos;
}INFO_HASH_FILME_RETORNO;

// Lista encadeada:
// Contem os seguintes elementos:
// - DADO_HASH_FILME_RETORNO: Struct com as informacoes da lista em questao
// - Ponteiro: Proximo elemento
struct LISTA_HASH_FILME_RETORNO{
    INFO_HASH_FILME_RETORNO InfoLista;
    struct LISTA_HASH_FILME_RETORNO *Prox;
};
typedef struct LISTA_HASH_FILME_RETORNO LISTA_HASH_FILME_RETORNO;

/// Struct auxiliar somente. Usado nas funcoes de pesquisa para retorna o nome;
// Informacoes da Lista encadeada;
// Contem o seguintes elementos:
// Nome da struct = INFO_FILME_NOME:
// - Numero inteiro: ID do filme
// - String: Nome do filme
typedef struct{
    int FilmeID;
    char FilmeNome[TAM_NOME];
}INFO_FILME_NOME;

// Lista encadeada:
// Contem os seguintes elementos:
// - INFO_HASH_FILME_RETORNO: Struct com as informacoes da lista em questao
// - Ponteiro: Proximo elemento
struct LISTA_FILME_NOME{
    DADO_FILME_NOME InfoLista;
    struct LISTA_FILME_NOME *Prox;
};
typedef struct LISTA_FILME_NOME LISTA_FILME_NOME;

/// ===========================================
///                  Funcoes
/// ===========================================
// Inicializa a Tabela Hash Aberta
void InicializaTabela(FILME_HASH *TabelaHash);
void AbreArquivoRating(char NomeArquivo[], FILME_HASH *TabelaHash);
void AbreArquivoMovie(char NomeArquivo[], FILME_HASH *TabelaHash, LISTA_FILME_DIF **ListaNomeFilme);
void InsereTabelaHash(FILME_HASH *TabelaHash, FILME_HASH Novo);
void PrintaFilme(DADO_HASH_RETORNO Filme);
int Hashing(int FilmeID);
FILME_HASH InicializaFilme(FILME_HASH Novo);
PT_GENERO *CriaListaGeneros(PT_GENERO *Lista, char Elemento[]);

/// ===========================================
///         Informacoes da Arvore AVL
/// ===========================================

typedef struct{
    FILME_HASH dados;
    char name[TAM_NOME];
    double Nota;
}Movie;

// Igual a estrutura da Tabela Hash de Filmes: + o string do nome do filme;
// Contem os seguintes elementos:
// Nome da struct = INFO_FILME_AVL_RETORNO:
// - Numero inteiro: FilmeID
// - Numero inteiro: CountRating
// - Numero doible: Nota do filme
// - Numero double: GlobalRating
// - String: Nome do filme
typedef struct{
    int FilmeID;
    int CountRatings;
    double Nota;
    double GlobalRating;
    char NomeFilme[TAM_NOME];
}INFO_AVL_FILME_RETORNO;

// Lista encadeada:
// Contem os seguintes elementos:
// - INFO_AVL_FILME_RETORNO: Struct com as informacoes da lista em questao
// - Ponteiro: Proximo elemento
struct LISTA_AVL_FILME{
    INFO_AVL_FILME_RETORNO InfoLista;
    struct LISTA_AVL_FILME *Prox;
};
typedef struct LISTA_AVL_FILME LISTA_AVL_FILME;

// Informacoes da estruturas dos elementos da Arvore AVL:
// Contem os seguintes elementos:
// Nome da struct = INFO_AVL_FILME:
// - Numero inteiro: FilmeID
// - Numero double: Nota do filme
typedef struct{
    int FilmeID;
    double Nota;
}INFO_AVL_FILME;


typedef struct{
    INFO_AVL_FILME InfoLista;
    struct PT_FILME_AVALIADO *Prox;
}PT_FILME_AVALIADO;

typedef struct{
    int id;
    struct PT_FILME_AVALIADO *FilmesAvaliados;
}USER;
/*
typedef struct ABP
{
    USER user;
    struct ABP *dir;
    struct ABP *esq;
} ABP;
*/
//
typedef struct AVL
{
    USER user;
    int FB;
    struct AVL *dir;
    struct AVL *esq;
} AVL;

AVL* rotacao_esquerda(AVL *p);
AVL* rotacao_direita(AVL* p);
AVL* rotacao_dupla_direita (AVL* p);
AVL* rotacao_dupla_esquerda (AVL *p);
AVL* Caso1 (AVL*a, int *ok);
AVL* Caso2 (AVL *a, int *ok);
AVL* InsereAVL (AVL *a, USER x, int *ok);
void CentralDirAVL(AVL *a);




//ABP* cria_abp(void);
//ABP* InsereAbp(ABP *a,USER u);
AVL* BuscaAVL(AVL*a,int userId);
PT_FILME_AVALIADO* InsereFilme(PT_FILME_AVALIADO *p, FILME_AVL DadoFilme);
//void PrintaUser(ABP *u);
void printaFilmeAVL(PT_FILME_AVALIADO *filme);
void leArquivoABP(FILME_HASH *tabela, AVL **a);


// TAG
typedef struct{
    int FilmeID;
    struct FILMES_TAG *Prox;
}FILMES_TAG;

typedef struct{
    int FilmeID;
    int Count;
    struct FILMES_TAG *Prox;
}FILMES_TAG_AUX;

typedef struct{
    char Tag[TAM_TAG];
    struct FILMES_TAG *FilmesTag;
}TAG;

typedef struct{
    int CountRatings;
    double GlobalRating;
    char NomeFilme[TAM_NOME];
    GENEROS *Generos;
}FILMETAG_RETORNO;

struct PT_FILMETAG{
    FILMETAG_RETORNO InfoFilme;
    struct PT_FILMETAG *Prox;
};
typedef struct PT_FILMETAG PT_FILMETAG;

struct PT_TAG_PROCURADA{
    char TagProcurada[TAM_TAG];
    struct PT_TAG_PROCURADA *Prox;
};
typedef struct PT_TAG_PROCURADA PT_TAG_PROCURADA;


//Trie
typedef struct{
    int PrefixoID;
    char Nome[TAM_NOME];
}FILMES_TRIE;

// Lista de ID dos filme
typedef struct{
    FILMES_TRIE Dado;
    struct PONTEIRO_FILME_TRIE *Prox;
}PT_FILME_TRIE;


// trie node
struct TrieNode
{
    struct TrieNode *movieName[ALPHABET_SIZE];

    // isEndOfWord is true if the node represents
    // end of a word
    int  isEndOfWord;
};
typedef struct TrieNode TrieNode;

// Retorna um novo nodo incializado
// Inicializado com -1
struct TrieNode *getNode(void);
void insert(struct TrieNode *root, Movie movie);
bool search(struct TrieNode *Raiz, char String[]);
void RemoveAcentos (char s[]);
void leArquivoTrie(char NomeArquivo[], struct TrieNode *T);

