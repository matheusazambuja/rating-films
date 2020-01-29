#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#define LINHA 100
#define ALPHABET_SIZE 120
#define TAM  100
#define TAM_LINHA 100
#define TAM_ELEMENTO 30
#define TAM_NOME 100
#define TAM_GENERO 30
#define TAM_TABELA_HASH 29000


//Trie

struct INFO_FILME_TRIE{
    int PrefixoID;
    char Nome[TAM];
};
typedef struct INFO_FILME_TRIE FILMES_TRIE;

// Lista de ID dos filme
struct PONTEIRO_FILME_TRIE{
    FILMES_TRIE Dado;
    struct PONTEIRO_FILME_TRIE *Prox;
};
typedef struct PONTEIRO_FILME_TRIE PT_FILME_TRIE;

struct Movie
{
    FILME_HASH dados;
    char name[50];

};
typedef struct Movie Movie;

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
void insert(struct TrieNode *root, struct Movie movie);
bool search(struct TrieNode *Raiz, char String[]);
void RemoveAcentos (char s[]);
void leArquivoTrie(FILE *arq,TrieNode *T);

//

//HASH

struct INFO_FILME_TRIE{
    int PrefixoID;
    char Nome[TAM];
};
typedef struct INFO_FILME_TRIE FILMES_TRIE;

// Lista de ID dos filme
struct PONTEIRO_FILME_TRIE{
    FILMES_TRIE Dado;
    struct PONTEIRO_FILME_TRIE *Prox;
};
typedef struct PONTEIRO_FILME_TRIE PT_FILME_TRIE;

struct Movie
{
    FILME_HASH dados;
    char name[50];

};
typedef struct Movie Movie;

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
void insert(struct TrieNode *root, struct Movie movie);
bool search(struct TrieNode *Raiz, char String[]);
void RemoveAcentos (char s[]);
void leArquivoTrie(FILE *arq,TrieNode *T);


//ABP

typedef struct info
{
    Movie avaliados[TAM_TABELA_HASH];
    int nota;
}USER;

typedef struct ABP
{
    USER user;
    struct ABP *dir;
    struct ABP *esq;
} ABP;

ABP* cria_abp(void);
ABP* insere_abp(ABP *a,info i);



