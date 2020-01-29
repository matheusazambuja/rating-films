#include"header.h"

struct TrieNode *getNode(void)
{
    int i;
    struct TrieNode *pNode;

    pNode = (struct TrieNode*) malloc(sizeof(struct TrieNode));

    if(pNode)
    {
        pNode->isEndOfWord = NULL;
        for (i = 0; i < ALPHABET_SIZE; i++)
            pNode->movieName[i] = NULL;
    }

    return pNode;
}

// If not present, inserts key into trie
// If the key is prefix of trie node, just
// marks leaf node
void insert(struct TrieNode *root, Movie movie)
{
    int i, index;
    int TamKey;
    char key[TAM_NOME];
    struct TrieNode *pCrawl = root;

    // Copia o nome do filme e usa como chave da arvore
    strcpy(key, movie.name);
    TamKey = strlen(key);

    for (i = 0; i < TamKey; i++)
    {
        index = key[i];
        if(index >= 32){
            index = index - 32;
            if (!pCrawl->movieName[index])
                pCrawl->movieName[index] = getNode();

            pCrawl = pCrawl->movieName[index];
        }
    }
    // Marca de fim de palavra
    // Recebe ID do filme
    pCrawl->isEndOfWord = movie.dados.FilmeID;
}

bool search(struct TrieNode *Raiz, char String[])
{
    int i, j, Index;
    int TamString = strlen(String);

    String = strupr(String);

    struct TrieNode *Aux = Raiz;

    for(i=0; i<TamString; i++)
    {
        Index = String[i] - 32;
        if(Aux->movieName[Index] == NULL)
            return NULL;

        Aux = Aux->movieName[Index];
    }

    return (Aux->isEndOfWord && Aux->movieName[Index] != NULL);
}


// Remove os acentos de um string
void RemoveAcentos (char s[]){
    int i, j;
    i = strlen(s)-1;

    while (i >= 0)
    {
        switch (s[i])
        {
        /*
        case '�':
            s[i]='a';
            break;
        case '�':
            s[i]='a';
            break;
        case '�':
            s[i]='a';
            break;
        case '�':
            s[i]='a';
            break;
        case '�':
            s[i]='o';
            break;
        case '�':
            s[i]='o';
            break;
        case '�':
            s[i]='o';
            break;
        case '�':
            s[i]='e';
            break;
        case '�':
            s[i]='e';
            break;
        case '�':
            s[i]='e';
            break;
        case '�':
            s[i]='u';
            break;
        case '�':
            s[i]='u';
            break;
        case '�':
            s[i]='i';
            break;
        case '�':
            s[i]='c';
            break;
        case '�':
            s[i]='n';
            break;
        */
        case '�':
            s[i-1] = 'E';
            for(j = i; j < strlen(s); j++)
                s[j] = s[j+1];
            break;
        case '�':
            s[i-1] = 'E';
            for(j = i; j < strlen(s); j++)
                s[j] = s[j+1];
            break;
        case '�':
            s[i-1] = 'U';
            for(j = i; j < strlen(s); j++)
                s[j] = s[j+1];
            break;
        case '�':
            s[i-1] = 'O';
            for(j = i; j < strlen(s); j++)
                s[j] = s[j+1];
            break;
        case '�':
            s[i-1] = 'A';
            for(j = i; j < strlen(s); j++)
                s[j] = s[j+1];
            break;
        case '�':
            s[i-1] = 'E';
            for(j = i; j < strlen(s); j++)
                s[j] = s[j+1];
            break;
        case '�':
            s[i-1] = 'A';
            for(j = i; j < strlen(s); j++)
                s[j] = s[j+1];
            break;
        case '�':
            s[i]='A';
            break;
        case  '�':
            s[i]='A';
            break;
        case  '�':
            s[i]='A';
            break;
        case  '�':
            s[i]='A';
            break;
        case  '�':
            s[i]='E';
            break;
        case  '�':
            s[i]='E';
            break;
        case  '�':
            s[i]='I';
            break;
        case  '�':
            s[i]='O';
            break;
        case  '�':
            s[i]='O';
            break;
        case  '�':
            s[i]='O';
            break;
        case  '�':
            s[i]='U';
            break;
        case  '�':
            s[i]='U';
            break;
        case  '�':
            s[i]='N';
            break;
        }
        i--;
    }
}


void leArquivoTrie(char NomeArquivo[], struct TrieNode *T)
{
    FILE *arq;
    int id, i;
    int ContadorLinha = 0, Contador = 0;
    char *palavra, linha[TAM_LINHA];
    char separador[] = {";"};
    Movie M;

    arq = fopen(NomeArquivo, "r");

    if(!arq)
    {
        printf("Erro ao abrir o arquivo '%s'.\n", NomeArquivo);
    }
    else
    {
        fgets(linha, TAM_LINHA, arq); // Passa a primeira linha do csv
        while (!feof(arq)) // percorre todo o arquivo do lexico de palavras, lendo linha por linha
        {
            fgets(linha, TAM_LINHA, arq);

            // Formata a linha do arquivo 'movie.csv' para retirar as informa��es importantes
            TrataLinhaMovie(linha);

            palavra = strtok(linha, separador); // ID do filme

            if(palavra != NULL)
            {
                id = atoi(palavra);
                M.dados.FilmeID = id;
            }
            // Copia o nome do filme em maiusculo para o arquivo
            // E salva na arvore Trie
            palavra = strtok(NULL, separador);
            if(palavra != NULL)
            {
                RemoveAcentos(palavra); // Remove os acentos do nome do filme
                palavra = strupr(palavra); // Coloca todos os nomes de filmes em maiusculos
                strcpy(M.name, palavra);
                insert(T, M);
            }
        }
        fclose(arq);
    }
}

