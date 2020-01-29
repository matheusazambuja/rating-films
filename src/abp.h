#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "hash.h"
#include "trie.h"


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
