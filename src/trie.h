
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
//#include "hash.h"
#define LINHA 100
#define ALPHABET_SIZE 120
#define TAM  100

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
