#include "header.h"

int main()
{
    int TabelaHash_Tag[TAM_TABELA_HASH_TAG]; // TabelaHash Fechada
    FILME_HASH TabelaHash_Filme[TAM_TABELA_HASH_FILME]; // TabelaHash Aberta

    LISTA_FILME_DIF *ListaNomeFilme = NULL;

    TrieNode *Trie = getNode();
    AVL *Avl = NULL;
    AVL *AvlBusca = NULL;

    // Recebe as estruturas como referencia e as inicializa e trata os arquivos de entrada
    // Adicionando o conteudo dos arquivos nas seus respectivas estruturas
    CriaEstruturas(TabelaHash_Filme, TabelaHash_Tag, &Trie, &Avl, &ListaNomeFilme);

    //escondecursor();

    // Entra no Menu do programa
    LacoMenu(TabelaHash_Filme, TabelaHash_Tag, Trie, Avl, ListaNomeFilme);
    system("cls");

    return 0;
}

