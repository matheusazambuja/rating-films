#include "header.h"


PT_FILME_AVALIADO* InsereFilme(PT_FILME_AVALIADO *p, FILME_AVL DadoFilme)
{
    PT_FILME_AVALIADO* Aux = p;
    PT_FILME_AVALIADO* Novo;

    Novo = malloc(sizeof(PT_FILME_AVALIADO));
    Novo->Dados = DadoFilme;

    if(Aux == NULL)
    {
        p = Novo;
        Novo->prox = NULL;
    }
    else{
        while(Aux->prox != NULL)
        {
            Aux = Aux->prox;
        }
        Aux->prox = Novo;
        Novo->prox = NULL;
    }
    return p;
}

AVL* BuscaAVL(AVL *a, int userId)
{

    while (a != NULL)
    {
        if (a->user.id == userId)
        {
            return a;
        }
        else
        {
            if (userId < a->user.id)
                a = a->esq;
            else
                a = a->dir;
        }
    }
    return NULL; //nao achou, retorna 0
}

void printaFilmeAVL(PT_FILME_AVALIADO *filme)
{
    PT_FILME_AVALIADO *Aux = filme;
    while(Aux != NULL)
    {
        //printa nome
        printf("MovieID:%d ", Aux->Dados.FilmeID);
        printf("Rating:%.1lf ",Aux->Dados.Nota);
        Aux = Aux->prox;
    }
}

void printaListaFilmeAVL(PT_FILMEAVL* Lista)
{
    PT_FILMEAVL *Aux = Lista;

    if(Lista == NULL)
    {
        printf("Sem resultados\n");
    }
    else
    {
        while(Aux != NULL)
        {
            printf("UserRating: %lf\n", Aux->InfoFilme.Nota);
            printf("NomeFilme: %s\n", Aux->InfoFilme.NomeFilme);
            //printf("Filme ID: %d\n", Aux->InfoFilme.FilmeID);
            printf("GlobalRating: %lf\n", Aux->InfoFilme.GlobalRating);
            printf("Counting: %d\n\n", Aux->InfoFilme.CountRatings);
            Aux = Aux->Prox;
        }
        printf("\n");
    }
}

AVL * rotacao_esquerda(AVL *p)
{
    AVL *z;
    z = p->dir;
    p->dir = z->esq;
    z->esq = p;
    p->FB = 0;
    p = z;
    return p;
}



AVL* rotacao_direita(AVL* p)
{
    AVL *u;
    u = p->esq;
    p->esq = u->dir;
    u->dir = p;
    p->FB = 0;
    p = u;
    return p;
}


AVL* rotacao_dupla_direita (AVL* p)
{
    AVL *u, *v;
    u = p->esq;
    v = u->dir;
    u->dir = v->esq;
    v->esq = u;
    p->esq = v->dir;
    v->dir = p;
    if (v->FB == 1) p->FB = -1;
    else p->FB = 0;
    if (v->FB == -1) u->FB = 1;
    else u->FB = 0;
    p = v;
    return p;
}

AVL* rotacao_dupla_esquerda (AVL *p)
{
    AVL *z, *y;
    z = p->dir;
    y = z->esq;
    z->esq = y->dir;
    y->dir = z;
    p->dir = y->esq;
    y->esq = p;
    if (y->FB == -1) p->FB = 1;
    else p->FB = 0;
    if (y->FB == 1) z->FB = -1;
    else z->FB = 0;
    p = y;
    return p;
}

AVL* Caso1 (AVL*a, int *ok)
{
    AVL *z;
    z = a->esq;
    if (z->FB == 1)
        a = rotacao_direita(a);
    else
        a = rotacao_dupla_direita(a);
    a->FB = 0;
    *ok = 0;
    return a;
}

AVL* Caso2 (AVL *a, int *ok)
{
    AVL *z;
    z = a->dir;
    if (z->FB == -1)
        a = rotacao_esquerda(a);
    else
        a = rotacao_dupla_esquerda(a);
    a->FB = 0;
    *ok = 0;
    return a;
}

AVL* InsereAVL (AVL *a, USER x, int *ok)
{
    /* Insere nodo em uma árvore AVL, onde A representa a raiz da árvore,
    x, a chave a ser inserida e h a altura da árvore */
    if (a == NULL)
    {
        a = (AVL*) malloc(sizeof(AVL));
        a->user = x;
        a->esq = NULL;
        a->dir = NULL;
        a->FB = 0;
        *ok = 1;
    }
    else if (x.id<a->user.id)
    {
        a->esq = InsereAVL(a->esq,x,ok);
        if (*ok)
        {
            switch (a->FB)
            {
            case -1:
                a->FB = 0;
                *ok = 0;
                break;
            case 0:
                a->FB = 1;
                break;
            case 1:
                a=Caso1(a,ok);
                break;
            }
        }
    }
    else
    {
        a->dir = InsereAVL(a->dir,x,ok);
        if (*ok)
        {
            switch (a->FB)
            {
            case 1:
                a->FB = 0;
                *ok = 0;
                break;
            case 0:
                a->FB = -1;
                break;
            case -1:
                a = Caso2(a,ok);
                break;
            }
        }
    }
    return a;
}

// Imprime os Tweets em ordem crescente por FilmeID
void CentralEsqAVL(AVL *a){
    if(a != NULL)
    {
        CentralEsqAVL(a->esq);
        printf("UsuarioID: %d\n", a->user.id);
        CentralEsqAVL(a->dir);
    }
}


void leArquivoABP(FILME_HASH *tabela, AVL **a)
{
    FILE *rt;
    char separadorId[] = {","};
    char *palavra, linha[TAM_LINHA];
    int id,mid,i,ok=1;
    int chave,nota,contador;
    unsigned long int ContadorLinha = 0;
    Movie m;
    FILME_AVL DadosFilmes;
    DadosFilmes.FilmeID = 0;
    DadosFilmes.Nota = 0;
    USER u;
    u.id = 1348948;
    contador=0;
    u.FilmesAvaliados = NULL;

    rt = fopen("rating.csv","r");

    if(rt)
    {
        rewind(rt);
        fgets(linha, TAM_LINHA, rt);
        fgets(linha, TAM_LINHA, rt);

        palavra = strtok(linha, separadorId); // String UserID
        id = atoi(palavra); // Numero UserID
        u.id = id;
        while(!feof(rt))
        {
            if(id != u.id)
            {
                *a = InsereAVL(*a, u, &ok);
                u.id = id;
                u.FilmesAvaliados = NULL;
            }

            // Busca as informações do filme na TabelaHash
            palavra = strtok(NULL, separadorId);
            mid = atoi(palavra); // Numero FilmeID

            chave = BuscaFilmeHash(tabela, mid);
            if(chave != -1)
            {
                DadosFilmes.FilmeID = tabela[chave].FilmeID;
                ContadorLinha++;

                palavra = strtok(NULL, separadorId); // Pega o rating do filme
                DadosFilmes.Nota = atof(palavra);

                u.FilmesAvaliados = InsereFilme(u.FilmesAvaliados, DadosFilmes);
            }

            fgets(linha, TAM_LINHA, rt);
            palavra = strtok(linha, separadorId); // String UserID
            id = atoi(palavra); // Numero UserID
        }
        fclose(rt);
    }
    else
        printf("erro ao abrir o arquivo de Rating");
}

PT_FILMEAVL* InsereListaFilmeAVL(PT_FILMEAVL *Lista, FILMEAVL_RETORNO Dado)
{
    PT_FILMEAVL* Aux = Lista;
    PT_FILMEAVL* Novo;

    Novo = malloc(sizeof(PT_FILMEAVL));
    Novo->InfoFilme = Dado;

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

int ProcuraListaNome(LISTA_FILME_DIF *Lista, int FilmeID, char NomeFilme[])
{
    LISTA_FILME_DIF *Aux = Lista;
    LISTA_FILME_DIF *Anterior = NULL;

    if(Lista == NULL)
    {
        return 0;
    }
    else
    {
        while(Aux != NULL && Aux->InfoLista.FilmeID != FilmeID)
        {
            Anterior = Aux;
            Aux = Aux->Prox;
        }
        if(Aux == NULL)
        {
            return 0;
        }
        else
        {
            strcpy(NomeFilme, Aux->InfoLista.FilmeNome);
            return 1;
        }
    }
}

PT_FILMEAVL *BuscaFilmeUsuario(PT_FILMEAVL *Lista, PT_FILME_AVALIADO *FilmesAvaliados, FILME_HASH *TabelaHash, LISTA_FILME_DIF *ListaNomeFilme)
{
    int IndexHash;
    int Retorno;
    char NomeFilme[TAM_NOME];
    FILMEAVL_RETORNO DadoRetorno;
    PT_FILME_AVALIADO *AuxAvaliados = FilmesAvaliados;
    while(AuxAvaliados != NULL)
    {
        IndexHash = BuscaFilmeHash(TabelaHash, AuxAvaliados->Dados.FilmeID);

        if(IndexHash != -1)
        {
            Retorno = ProcuraListaNome(ListaNomeFilme, AuxAvaliados->Dados.FilmeID, &NomeFilme);

            DadoRetorno.GlobalRating = TabelaHash[IndexHash].Rating;
            DadoRetorno.CountRatings = TabelaHash[IndexHash].CountRating;
            DadoRetorno.FilmeID = TabelaHash[IndexHash].FilmeID;
            DadoRetorno.Nota = AuxAvaliados->Dados.Nota;
            strcpy(DadoRetorno.NomeFilme, NomeFilme);

            Lista = InsereListaFilmeAVL(Lista, DadoRetorno);
        }
        AuxAvaliados = AuxAvaliados->prox;
    }
    return Lista;
}

void CriaEstruturas(FILME_HASH *TabelaHash_Filme, FILMES_TAG *TabelaHash_Tag, struct TrieNode **Trie, AVL **Avl, LISTA_FILME_DIF **ListaNomeFilme)
{
    // Inicializa os elementos da Tabela Hash de filmes
    InicializaTabela_Filme(TabelaHash_Filme);
    // Inicializa os elementos da Tabela Hash de filmes
    InicializaTabela_Tag(TabelaHash_Tag);

    // Abre o arquivo 'rating.csv' e trata os dados para TabelaHash_Filme = Aberta
    printf("Atribuindo filmes na Tabela Hash de filmes...\n");
    AbreArquivoRating("rating.csv", TabelaHash_Filme);
    // Abre o arquivo 'movie.csv' e trata os dados para TabelaHash_Filme = Aberta
    // Tambem cria uma lista encadeada com os nomes do filmes
    AbreArquivoMovie("movie.csv", TabelaHash_Filme, *(&ListaNomeFilme));
    // Abre o arquivo 'rating.csv' e trata os dados para AVL
    printf("Atribuindo filmes na AVL...\n");
    leArquivoABP(TabelaHash_Filme, *(&Avl));
    // Abre o arquivo 'movie.csv' e trata os dados para Arvore Trie
    printf("Atribuindo filmes na Trie...\n");
    leArquivoTrie("movie.csv", *Trie);
    // Abre o arquivo 'tag.csv' e trata os dados para TabelaHash_Tag = Fechada
    printf("Atribuindo filmes na Tabela Hash de Tags...\n");
    AbreArquivoTag("tag.csv", TabelaHash_Tag);

    printf("Criacao de estruturas prontas\n\n");
    printf("Pressione qualquer tecla para iniciar o menu...");
    getchar();
}

