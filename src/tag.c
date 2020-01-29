#include "header.h"

int HashingTag(char String[TAM_TAG], int TamTabela){
    int i, TamString;
    unsigned long int Chave;
    TamString = strlen(String);

    Chave = 7;
    for(i=0; i<TamString; i++)
        Chave = Chave * 3 + (int)String[i];
    Chave %= TamTabela;

    return Chave;
}

FILMES_TAG *InsereListaHashFechado(FILMES_TAG *Lista, int FilmeID)
{
    FILMES_TAG* Aux = Lista;
    FILMES_TAG* Novo;

    Novo = malloc(sizeof(FILMES_TAG));
    Novo->FilmeID = FilmeID;

    if(Aux == NULL)
    {
        Lista = Novo;
        Novo->Prox = NULL;
    }
    else{
        while(Aux->Prox != NULL && Aux->FilmeID != FilmeID)
        {
            Aux = Aux->Prox;
        }
        if(Aux->Prox == NULL)
        {
            Aux->Prox = Novo;
            Novo->Prox = NULL;
        }
    }
    return Lista;
}

void InicializaTabela_Tag(int *TabelaHash_Tag)
{
    int i;
    for(i=0; i<TAM_TABELA_HASH_TAG; i++)
        TabelaHash_Tag[i] = -1;
}


void HashFechado(int *TabelaHash, int FilmeID, char StringTag[]){
    int i;
    unsigned long int IndexHash;
    //TAG Dado;

    IndexHash = HashingTag(StringTag, TAM_TABELA_HASH_TAG);

    if(TabelaHash[IndexHash] == -1){
        TabelaHash[IndexHash] = 0; // tabela_hash[index_hash] = NULL;
        TabelaHash[IndexHash] = InsereListaHashFechado(TabelaHash[IndexHash], FilmeID);
    }
    else{
        TabelaHash[IndexHash] = InsereListaHashFechado(TabelaHash[IndexHash], FilmeID);
    }
    //PrintaListaHashFechado(TabelaHash[IndexHash]);
    //getchar();
}

// Funcao TrataLinhaTag;
// Entrada: string que corresponde a linha do arquivo de tags
// Saida  : string trata para retirada das informacoes
void TrataLinhaTag(char Linha[])
{
    int i, TamLinha;
    TamLinha = strlen(Linha); // Tamanho do string Linha
    for(i=0; i<TamLinha; i++)
        if(Linha[i] == '"' || Linha[i] == ',')
            Linha[i] = ';';
}

void PrintaListaHashFechado(FILMES_TAG *Lista)
{
    FILMES_TAG *Aux = Lista;
    if(Aux == NULL)
    {
        printf("Lista de filme da Hash de Tags esta vazia.\n");
    }
    else
    {
        printf("[");
        while(Aux != NULL)
        {
            printf("%d, ", Aux->FilmeID);
            Aux = Aux->Prox;
        }
        printf("]");
    }
}

void AbreArquivoTag(char NomeArquivo[], int *TabelaHash_Tag)
{
    FILE *Arq;
    int FilmeID_Aux;
    unsigned long int ContadorLinha = 0;
    char Linha[TAM_LINHA];
    char Separadores[] = {";"};
    char *ElementoID, *ElementoTag;

    Arq = fopen(NomeArquivo, "r");

    if(!Arq)
    {
        printf("Erro ao abrir o arquivo '%s' na funcao AbreArquivoTag.\n", NomeArquivo);
    }
    else
    {
        fgets(Linha, TAM_LINHA, Arq);
        while(!feof(Arq) && ContadorLinha < 465564)
        {
            fgets(Linha, TAM_LINHA, Arq);
            ContadorLinha++;

            // Formata a linha do arquivo 'movie.csv' para retirar as informações importantes
            TrataLinhaTag(Linha);

            ElementoID = strtok(Linha, Separadores); // UserID
            ElementoID = strtok(NULL, Separadores); // FilmeID
            FilmeID_Aux = atoi(ElementoID);

            ElementoTag = strtok(NULL, Separadores); // String tag
            ElementoTag = strlwr(ElementoTag);

            HashFechado(TabelaHash_Tag, FilmeID_Aux, ElementoTag); // Adiciona o ID do filme na TabelaHash

        }
        fclose(Arq);
    }
}

FILMES_TAG_AUX *InsereFilmeTagAux(FILMES_TAG_AUX *Lista, int NovoFilmeID)
{
    FILMES_TAG_AUX* Aux = Lista;
    FILMES_TAG_AUX* Anterior = NULL;
    FILMES_TAG_AUX* Novo;

    Novo = malloc(sizeof(FILMES_TAG_AUX));
    Novo->FilmeID = NovoFilmeID;

    if(Aux == NULL)
    {
        Lista = Novo;
        Novo->Prox = NULL;
        Novo->Count = 0;
    }
    else{
        while(Aux != NULL && Aux->FilmeID != NovoFilmeID)
        {
            Anterior = Aux;
            Aux = Aux->Prox;
        }
        if(Aux == NULL)
        {
            Anterior->Prox = Novo;
            Novo->Prox = NULL;
        }
        else
        {
            Aux->Count++;
        }
    }
    return Lista;
}

FILMES_TAG *InsereFilmeTag(FILMES_TAG *Lista, int NovoFilmeID)
{
    FILMES_TAG* Aux = Lista;
    FILMES_TAG* Anterior = NULL;
    FILMES_TAG* Novo;

    Novo = malloc(sizeof(FILMES_TAG));
    Novo->FilmeID = NovoFilmeID;

    if(Aux == NULL)
    {
        Lista = Novo;
        Novo->Prox = NULL;
    }
    else{
        while(Aux != NULL)
        {
            Anterior = Aux;
            Aux = Aux->Prox;
        }
        Anterior->Prox = Novo;
        Novo->Prox = NULL;
    }
    return Lista;
}

FILMES_TAG *CriaListaFilmeTag(FILMES_TAG *Lista, int PonteriosListaFilmes[], int TamVetor)
{
    int i;
    FILMES_TAG *AuxFilmeTag = NULL;
    FILMES_TAG_AUX *Aux = NULL;

    for(i=0; i<TamVetor; i++)
    {
        AuxFilmeTag = PonteriosListaFilmes[i];
        while(AuxFilmeTag != NULL)
        {
            Aux = InsereFilmeTagAux(Aux, AuxFilmeTag->FilmeID);
            AuxFilmeTag = AuxFilmeTag->Prox;
        }
    }
    AuxFilmeTag = NULL;

    while(Aux != NULL)
    {
        if(Aux->Count == TamVetor-1)
        {
            AuxFilmeTag = InsereFilmeTag(AuxFilmeTag, Aux->FilmeID);
        }
        Aux = Aux->Prox;
    }
    return AuxFilmeTag;
}

FILMES_TAG *BuscaPorTag(FILMES_TAG *Lista, int *TabelaHash, PT_TAG_PROCURADA *ListaTagProcurada)
{
    unsigned long int IndexHash;
    int QuantTags = 0, QuantTagsNaTabela = 0, i = 0;

    PT_TAG_PROCURADA *Aux = ListaTagProcurada;
    while(Aux != NULL)
    {
        QuantTags++;
        Aux = Aux->Prox;
    }

    if(QuantTags > 0)
    {
        int VetorListaFilmes[QuantTags];

        Aux = ListaTagProcurada;
        while(Aux != NULL)
        {
            IndexHash = HashingTag(Aux->TagProcurada, TAM_TABELA_HASH_TAG);

            if(TabelaHash[IndexHash] != -1)
            {
                VetorListaFilmes[QuantTagsNaTabela] = TabelaHash[IndexHash];
                QuantTagsNaTabela++;
            }
            Aux = Aux->Prox;
        }

        Lista = CriaListaFilmeTag(Lista, VetorListaFilmes, QuantTagsNaTabela);
    }
    return Lista;
}

PT_TAG_PROCURADA *InsereListaTagProcurada(PT_TAG_PROCURADA *Lista, char Tag[])
{
    PT_TAG_PROCURADA* Aux = Lista;
    PT_TAG_PROCURADA* Anterior = NULL;
    PT_TAG_PROCURADA* Novo;

    Novo = malloc(sizeof(PT_TAG_PROCURADA));
    strcpy(Novo->TagProcurada, Tag);

    if(Aux == NULL)
    {
        Lista = Novo;
        Novo->Prox = NULL;
    }
    else{
        while(Aux != NULL)
        {
            Anterior = Aux;
            Aux = Aux->Prox;
        }
        Anterior->Prox = Novo;
        Novo->Prox = NULL;
    }
    return Lista;
}

PT_TAG_PROCURADA *CriaListaTagProcurada(PT_TAG_PROCURADA *Lista, char StringTags[])
{
    char Separador[] = {"'"};
    char *Elemento;

    Elemento = strtok(StringTags, Separador);

    while(Elemento != NULL)
    {
        Elemento = strlwr(Elemento);
        Lista = InsereListaTagProcurada(Lista, Elemento);
        Elemento = strtok(NULL, Separador);
    }
    return Lista;
}

void PrintaListaFilmeTag(FILMES_TAG *Lista)
{
    FILMES_TAG *Aux = Lista;
    if(Lista == NULL)
        printf("Lista FilmeTag vazia.\n");
    else
    {
        printf("[");
        while(Aux != NULL)
        {
            printf("%d, ", Aux->FilmeID);
            Aux = Aux->Prox;
        }

    printf("]\n");
    }
}

void PrintaListaFilmeTagAux(FILMES_TAG_AUX *Lista)
{
    FILMES_TAG_AUX *Aux = Lista;
    if(Lista == NULL)
        printf("Lista FilmeTag vazia.\n");
    else
    {
        printf("[");
        while(Aux != NULL)
        {
            printf("%d-%d, ", Aux->FilmeID, Aux->Count);
            Aux = Aux->Prox;
        }

    printf("]\n");
    }
}

PT_FILMETAG *InsereFilmeTagRetorno(PT_FILMETAG* Lista, FILMETAG_RETORNO Dado)
{
    PT_FILMETAG* Aux = Lista;
    PT_FILMETAG* Anterior = NULL;
    PT_FILMETAG* Novo;

    Novo = malloc(sizeof(PT_FILMETAG));
    Novo->InfoFilme = Dado;

    if(Aux == NULL)
    {
        Lista = Novo;
        Novo->Prox = NULL;
    }
    else{
        while(Aux != NULL)
        {
            Anterior = Aux;
            Aux = Aux->Prox;
        }
        Anterior->Prox = Novo;
        Novo->Prox = NULL;
    }
    return Lista;
}

PT_FILMETAG *BuscaFilmeHashTag(PT_FILMETAG *Lista, FILMES_TAG *ListaID, FILME_HASH *TabelaHash, LISTA_FILME_DIF *ListaNomeFilme)
{
    int IndexHash;
    int Retorno;
    char NomeFilme[TAM_NOME];
    FILMETAG_RETORNO DadoRetorno;

    FILMES_TAG *Aux = ListaID;

    while(Aux != NULL)
    {
        IndexHash = Hashing(Aux->FilmeID);

        if(TabelaHash[IndexHash].FilmeID == Aux->FilmeID){
            Retorno = ProcuraListaNome(ListaNomeFilme, Aux->FilmeID, &NomeFilme);

            strcpy(DadoRetorno.NomeFilme, NomeFilme);
            DadoRetorno.Generos = TabelaHash[IndexHash].Generos;
            DadoRetorno.GlobalRating = TabelaHash[IndexHash].Rating;
            DadoRetorno.CountRatings = TabelaHash[IndexHash].CountRating;

            Lista = InsereFilmeTagRetorno(Lista, DadoRetorno);
        }
        else{
            if(TabelaHash[IndexHash].FilmeID != -1){ // Se Filme != Vazio
                while(1)
                {
                    // Enquanto (PosTabela != Vazio) E (PosTabela < TamanhoTabela) E (EndHash < TAM_TABELA)
                    while((TabelaHash[IndexHash].FilmeID != -1) && (TabelaHash[IndexHash].FilmeID != Aux->FilmeID) && IndexHash < TAM_TABELA_HASH_FILME){
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
            if(TabelaHash[IndexHash].FilmeID == Aux->FilmeID) // Se ID do filme da tabela == ID filme novo
            {
                Retorno = ProcuraListaNome(ListaNomeFilme, Aux->FilmeID, &NomeFilme);

                strcpy(DadoRetorno.NomeFilme, NomeFilme);
                DadoRetorno.Generos = TabelaHash[IndexHash].Generos;
                DadoRetorno.GlobalRating = TabelaHash[IndexHash].Rating;
                DadoRetorno.CountRatings = TabelaHash[IndexHash].CountRating;

                Lista = InsereFilmeTagRetorno(Lista, DadoRetorno);
            }
        }
        Aux = Aux->Prox;
    }
    return Lista;
}


void PrintaFilmeBuscadaTag(PT_FILMETAG *Lista)
{
    PT_FILMETAG *Aux = Lista;

    if(Lista == NULL)
        printf("Lista vazia.\n");
    else
    {
        while(Aux != NULL)
        {
            printf("NomeFilme: %s\n", Aux->InfoFilme.NomeFilme);
            PrintaListaGeneros(Aux->InfoFilme.Generos);
            printf("GlobalRating: %lf\n", Aux->InfoFilme.GlobalRating);
            printf("Couting     : %d\n\n", Aux->InfoFilme.CountRatings);
            Aux = Aux->Prox;
        }
    }
}


