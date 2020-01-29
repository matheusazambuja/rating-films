#include "header.h"

///  ####################################################################
///                    DESENHO E CONTORLE DO MENU
///  ####################################################################
void desenha_menu_inicial()
{
    printf("   Aline Machado e Matheus Azambuja\n");
    printf("          CPD - INF01124\n");
    printf("             2019/2\n\n\n");

    printf("1 - Pesquisa por Prefixo\n\n");
    printf("2 - Pesquisa por Usuario\n\n");
    printf("3 - Pesquisa por Genero\n\n");
    printf("4 - Pesquisa por Tags\n\n");
    printf("5 - Sair\n\n");
    printf("\nDigite o numero da operacao para Selecionar: ");
}

int executa_menu()
{ // Executa a opcao que o usuario selecionou
    char ch = 0;
    int opcao = 1;
    desenha_menu_inicial();
    opcao = getchar();

    switch(opcao)
    {
        case 49:// Pesquisa por Prefixo
            system("cls");
            return 1;
            break;
        case 50: // Pesquisa por Usuario
            system("cls");
            return 2;
            break;
        case 51: // Pesquisa por Genero
            return 3;
            break;
        case 52: // Pesquisa por Tags
            return 4;
            break;
        case 53:// Sair
            return -1;
            break;
    }
    return 0; // Para consistencia
}

void escondecursor()
{
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}

// Controla o menu do programa
void LacoMenu(FILME_HASH *TabelaHash_Filme, int *TabelaHash_Tag, struct TrieNode *Trie, AVL *Avl, LISTA_FILME_DIF* ListaNomeFilme)
{
    int escolha_menu;
    int UsuarioID;
    int QuantFilmesGenero;
    char GeneroBuscado[TAM_GENERO];
    char TagsBuscadas[TAM_TAGS_BUSCADA];
    char NomeFilmeTrie[TAM_NOME];

    PT_TAG_PROCURADA *ListaTagProcurada = NULL;
    PT_FILMETAG *ListaFilmeBuscadaTag = NULL;
    FILMES_TAG *ListaFilmeTag = NULL;
    LISTA_FILMEHASH_RETORNO *ListaFilmeGenero = NULL;
    PT_FILMEAVL *ListaFilmeAVL = NULL;
    AVL *AvlBusca = NULL;

    do
    {
        system("cls");

        ListaFilmeAVL = NULL;
        ListaFilmeGenero = NULL;
        ListaFilmeBuscadaTag = NULL;

        escolha_menu = executa_menu(); // Armazena a opcao escolhida pelo usuario no menu
        fflush(stdin);

        switch(escolha_menu)
        {
            case 1: // Pesquisa por Prefixo
                strcpy(NomeFilmeTrie, "Carandiru (2003)");
                printf("\nO filme '%s' esta na Trie: %d\n"), NomeFilmeTrie, (int)search(Trie, NomeFilmeTrie);
                strcpy(NomeFilmeTrie, "Knocked Up (2007)");
                printf("\nO filme '%s' esta na Trie: %d\n"), NomeFilmeTrie, (int)search(Trie, NomeFilmeTrie);
                strcpy(NomeFilmeTrie, "Rock, The (1996)");
                printf("\nO filme '%s' esta na Trie: %d\n"), NomeFilmeTrie, (int)search(Trie, NomeFilmeTrie);

                getchar();
                break;
            case 2: // Pesquisa por Usuario
                system("cls");
                UsuarioID = PedeUsuario();
                fflush(stdin);

                AvlBusca = BuscaAVL(Avl, UsuarioID); // Utuliza o id do usuario para pesquisar na AVL
                ListaFilmeAVL = BuscaFilmeUsuario(ListaFilmeAVL, AvlBusca->user.FilmesAvaliados, TabelaHash_Filme, ListaNomeFilme); // Busca as informação solicitadas nessa pesquisa

                printaListaFilmeAVL(ListaFilmeAVL);
                getchar();
                break;
            case 3: // Pesquisa por Genero
                system("cls");
                QuantFilmesGenero = PedeGenero(&GeneroBuscado);

                ListaFilmeGenero = BuscaPorGenero(ListaFilmeGenero, QuantFilmesGenero, GeneroBuscado, TabelaHash_Filme, ListaNomeFilme); // Busca as informação solicitadas nessa pesquisa

                PrintaListaFilmeHash(ListaFilmeGenero);
                getchar();
                break;
            case 4: // Pesquisa por Tags
                system("cls");
                PedeTags(&TagsBuscadas);

                ListaTagProcurada = CriaListaTagProcurada(ListaTagProcurada, TagsBuscadas); // Cria uma lista encadeada com o string inserirdo pelo usuario
                ListaFilmeTag = BuscaPorTag(ListaFilmeTag, TabelaHash_Tag, ListaTagProcurada); // Cria uma lista de id de filmes que possuem as Tags buscadas
                ListaFilmeBuscadaTag = BuscaFilmeHashTag(ListaFilmeBuscadaTag, ListaFilmeTag, TabelaHash_Filme, ListaNomeFilme); // Buscas as informações solicitadas nessa pesquisa

                PrintaFilmeBuscadaTag(ListaFilmeBuscadaTag);
                getchar();
                break;
        }
    }while(escolha_menu != -1);
}

// Entrada: String inserida pelo usuario na "Pesquisa por Genero";
// Saida: Numero e String;
// Numero: Quantidade de filmes solicidados;
// String: Genero pesquisado;
int TrataStringGeneroBuscado(char GeneroAux[]){
    int TamGenero = strlen(GeneroAux);
    int i, j = 0;
    char QuantFilmes[9];
    char Separador[] = "'";
    char *Elemento;

    for(i=0; i<TamGenero; i++)
    {
        if(i > 2 && GeneroAux[i] != ' ' && j != -1)
        {
            QuantFilmes[j] = GeneroAux[i];
            j++;
        }
        if(GeneroAux[i] == ' ')
        {
            QuantFilmes[j] = '\0';
            j = -1;
            i = TamGenero;
        }
    }
    Elemento = strtok(GeneroAux, Separador);
    Elemento = strtok(NULL, Separador);
    strcpy(GeneroAux, Elemento);
    return atoi(QuantFilmes);
}

// Solicita o ID do Usuario a pesquisar ao usuario;
int PedeUsuario()
{
    int UsuarioID;
    printf("\n\n================================================================================");
    printf("\t\t\t  Pesquisa por Usuario\n");
    printf("================================================================================\n");
    printf("Instrucoes de pesquisa:\n");
    printf("A busca eh feita a partir de um numero inteiro.\n");
    printf("Para realizar a busca insira somente o ID do usuario.\n\n");
    printf("================================================================================\n");
    printf("Insira o usuario: ");
    scanf("%d", &UsuarioID);
    printf("\n\nResultado da busca por Usuario: \n\n");
    return UsuarioID;
}

// Solicita as Tags dos filmes a pesquisar ao usuario;
void PedeTags(char TagsBuscadas[])
{
    printf("\n\n================================================================================");
    printf("\t\t\t  Pesquisa por Tags\n");
    printf("================================================================================\n");
    printf("Instrucoes de pesquisa:\n");
    printf("Para realizar a busca insira as tags da seguinte forma: 'tags'.\n");
    printf("Exemplo: 'games' 'brazil' 'anime'.\n\n");
    printf("================================================================================\n");
    printf("Insira as tags: ");
    gets(TagsBuscadas);
    printf("\n\nResultado da busca por Tags: \n\n");
}

// Solicita os Generos dos filmes a pesquisa ao usuario;
int PedeGenero(char Genero[])
{
    int QuantFilmes;
    char GeneroAux[TAM_GENERO_BUSCADO];

    system("cls");

    printf("\n\n================================================================================");
    printf("\t\t\t  Pesquisa por Genero\n");
    printf("================================================================================\n");
    printf("Instruções de pesquisa:\n");
    printf("Para realizar utilize o seguinte formato: top<N> '<genero>'.\n");
    printf("N => eh o numero de filmes que serao printados.\n");
    printf("<genero> => eh o string do genero\n\n");
    printf("================================================================================\n\n");
    printf("Insira a busca: ");

    fflush(stdin);
    gets(GeneroAux);

    QuantFilmes = TrataStringGeneroBuscado(&GeneroAux);
    strcpy(Genero, GeneroAux);
    printf("\n\nResultado da busca por Genero: \n\n");

    return QuantFilmes;
}
