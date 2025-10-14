#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 100

struct Item_Seq{
    char nome[30];
    char tipo[20];
    int quantidade;
};

struct Item{
    char nome[30];
    char tipo[20];
    int quantidade;
    struct Item* proximo;
};

/* Função para limpar o buffer de entrada */
void limparbuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

}
/* Protótipos das funções da lista sequencial*/
void inserirItemSeq(struct Item inventario[],int *qtditens);
void excluirItemSeq(struct Item inventario[],int *qtditens);
void listarItemSeq(struct Item inventario[],int *qtditens);
void buscarItemSeq(struct Item inventario[],int *qtditens);
void buscarBinItemSeq(struct Item inventario[],int *qtditens);


/* Protótipos das funções da lista ordenada*/
void inserirItem(struct Item** Inicio);
void excluirItem(struct Item** Inicio);
void listarItem(struct Item** Inicio);
void buscarItem(struct Item** Inicio);


int main(){
    int opcao = 0;
    int *qtditens = 0;
    struct Item *Inicio = NULL;
    struct Item_Seq inventario[MAX_ITENS];
    /* Montando menu de escolha do tipo de lista */
    do{
        printf("\n----Escolha do tipo de lista----\n\n");
        printf("1 - Lista Sequencial\n");
        printf("2 - Lista Ordenada\n");
        printf("0 - Sair do inventario\n");
        printf("Selecione a acao: ");
        scanf("%d",&opcao);
        limparbuffer();

        switch (opcao){
            case 1:
                /* Montando menu de Interação com o inventário */
                do{
                    opcao = 0;
                    printf("\n----Menu de Interacao----\n\n");
                    printf("1 - Inserir item\n");
                    printf("2 - Remover item\n");
                    printf("3 - Listar itens\n");
                    printf("4 - Buscar item (Busca Sequencial)\n");
                    printf("5 - Buscar item (Busca Binaria)\n");
                    printf("0 - Sair do inventario\n");
                    printf("Selecione a acao: ");
                    scanf("%d",&opcao);
                    limparbuffer();

                    switch (opcao){
                        case 1:
                            inserirItemSeq(inventario,&qtditens);

                            break;
                        case 2:
                            excluirItemSeq(inventario,&qtditens);
                            break;
                        case 3:
                            listarItemSeq(inventario,&qtditens);
                            break;
                        case 4:
                            buscarItemSeq(inventario,&qtditens);
                            break;
                        case 5:
                            buscarBinItemSeq(inventario,&qtditens);
                            break;
                        case 0:
                            printf("Saindo...");
                            break;
                        default:
                            printf("Opcao invalida!\n");
                            break;
                    }
                }while (opcao != 0);
                break;
            case 2:
                /* Montando menu de Interação com o inventário */
                do{
                    opcao = 0;
                    printf("\n----Menu de Interacao----\n\n");
                    printf("1 - Inserir item\n");
                    printf("2 - Remover item\n");
                    printf("3 - Listar itens\n");
                    printf("4 - Buscar item\n");
                    printf("0 - Sair do inventario\n");
                    printf("Selecione a acao: ");
                    scanf("%d",&opcao);
                    limparbuffer();

                    switch (opcao){
                        case 1:
                            inserirItem(&Inicio);
                            break;
                        case 2:
                            excluirItem(&Inicio);
                            break;
                        case 3:
                            listarItem(&Inicio);
                            break;
                        case 4:
                            buscarItem(&Inicio);
                            break;
                        case 0:
                            printf("Saindo...");
                            break;
                        default:
                            printf("Opcao invalida!\n");
                            break;
                    }
                }while (opcao != 0);
                break;
            case 0:
                printf("Saindo...");
                break;
            default:
                printf("Opcao invalida!\n");
                break;
        }

    }while (opcao !=0);
}


void inserirItemSeq(struct Item inventario[], int *qtditens)
{
    if(*qtditens == MAX_ITENS)
    {
        printf("Inventario cheio!\n");
        return;
    }
    char nome[30], tipo[20];
    int quantidade = 0, i = 0, j = 0;
    printf("\n\nNome do Item: ");
    fgets(nome,30,stdin);
    nome[strcspn(nome, "\n")] = '\0';
    printf("Tipo do Item: ");
    fgets(tipo,20,stdin);
    tipo[strcspn(tipo, "\n")] = '\0';
    printf("Quantidade do item: ");
    scanf("%d",&quantidade);
    limparbuffer();
    /* Atribuindo ao primeiro valor caso esteja vazio */
    if(*qtditens == 0)
    {
        strcpy(inventario[0].nome, nome);
        strcpy(inventario[0].tipo, tipo);
        inventario[0].quantidade = quantidade;
        (*qtditens)++;
        return;
    }

    /* Procurar a posição de inserção (ordem alfabética) */
    while (i < *qtditens && strcmp(inventario[i].nome, nome) < 0)
    {
        i++;
    }

    /* Deslocar elementos à frente para abrir espaço */
    for (j = *qtditens; j > i; j--)
    {
        inventario[j] = inventario[j - 1];
    }

    /* Inserir o novo item na posição correta */
    strcpy(inventario[i].nome, nome);
    strcpy(inventario[i].tipo, tipo);
    inventario[i].quantidade = quantidade;
    (*qtditens)++;
}

void listarItemSeq(struct Item inventario[], int *qtditens)
{
    if(*qtditens == 0)
    {
        printf("Inventario vazio!\n");
        return;
    }
    int i = 0;
    /* Percorrendo o inventario todo, imprimindo cada elemento */
    for(i=0; i<*qtditens; i++)
    {
        printf("Item %d\n",i+1);
        printf("Nome: %s | Tipo: %s |  Quantidade: %d\n",inventario[i].nome,inventario[i].tipo,inventario[i].quantidade);
    }
}

void excluirItemSeq(struct Item inventario[], int *qtditens)
{
    if(*qtditens == 0)
    {
        printf("Inventario vazio!\n");
        return;
    }
    char nome[30], tipo[20];
    int quantidade = 0, i = 0, j = 0;
    printf("\n\nNome do Item: ");
    fgets(nome,30,stdin);
    nome[strcspn(nome, "\n")] = '\0';
    
    /* Buscar qual posicao esta o item desejado */
    while (i < *qtditens && strcmp(inventario[i].nome, nome) != 0)
    {
        i++;
    }
    /* Caso nao encontre o item */
    if(i == *qtditens){
        printf("Item nao encontrado!\n");
    /* Alocando o item seguinte para cada elemento apos o item removido */
    }else{
        for (j = i; j < *qtditens - 1; j++)
        {
            inventario[j] = inventario[j + 1];
            }
        (*qtditens)--;
    }
}

void buscarItemSeq(struct Item inventario[], int *qtditens)
{
    if(*qtditens == 0)
    {
        printf("Inventario vazio!\n");
        return;
    }
    char nome[30], tipo[20];
    int quantidade = 0, i = 0, j = 0;
    printf("\n\nNome do Item: ");
    fgets(nome,30,stdin);
    nome[strcspn(nome, "\n")] = '\0';
    
    /* Buscando qual o elemento possui o mesmo nome passando por todos os elementos ate encontrar */
    while (i < *qtditens && strcmp(inventario[i].nome, nome) != 0)
    {
        i++;
    }
    /* Caso nao encontre o item */
    if(i == *qtditens){
        printf("Numero de Comparacoes: %d\n",i);
        printf("Item nao encontrado!\n");
    /* Imprimindo valores do elemento encontrado */
    }else{
        printf("Numero de Comparacoes: %d\n",i);
        printf("Item %d\n",i+1);
        printf("Nome: %s | Tipo: %s |  Quantidade: %d\n",inventario[i].nome,inventario[i].tipo,inventario[i].quantidade);
    }
}

void buscarBinItemSeq(struct Item inventario[], int *qtditens)
{
    if(*qtditens == 0)
    {
        printf("Inventario vazio!\n");
        return;
    }
    char nome[30], tipo[20];
    int quantidade = 0, inicio = 0, fim = *qtditens - 1, combinacoes = 0;
    printf("\n\nNome do Item: ");
    fgets(nome,30,stdin);
    nome[strcspn(nome, "\n")] = '\0';
    
    while (inicio <= fim) {
        /* Pegando o meio do vetor e comparando com o nome passado pelo usuario */
        int meio = (inicio + fim) / 2;
        /* Caso o item do meio confere com o item procurado */
        if (strcmp(inventario[meio].nome, nome) == 0){
            combinacoes++;
            printf("Numero de Comparacoes: %d\n",combinacoes);
            printf("Item %d\n",meio+1);
            printf("Nome: %s | Tipo: %s |  Quantidade: %d\n",inventario[meio].nome,inventario[meio].tipo,inventario[meio].quantidade);
            return 0;
        /* Caso o item esteja antes do item do meio */
        }else if (strcmp(inventario[meio].nome, nome) < 0){
            combinacoes++;
            inicio = meio + 1;
        }
        /* Caso o item esteja depois do item do meio */
        else{
            combinacoes++;
            fim = meio - 1;
        }
    }
    /* Caso nao encontre o item */
    printf("Item nao encontrado!\n");
    return 0;
}

void inserirItem(struct Item** Inicio)
{
    struct Item* novoItem = (struct Item*)malloc(sizeof(struct Item));
    printf("\n\nNome do Item: ");
    fgets(novoItem->nome,30,stdin);
    printf("Tipo do Item: ");
    fgets(novoItem->tipo,20,stdin);
    printf("Quantidade do item: ");
    scanf("%d",&novoItem->quantidade);
    limparbuffer();
    /* Atribuindo o inicio ao novo item */
    novoItem->proximo = *Inicio;
    *Inicio = novoItem;
}

void excluirItem(struct Item** Inicio)
{
    if (*Inicio == NULL)
    {
        printf("\nInventario vazio. Nada para excluir.\n");
        return;
    }

    char nome[30];
    printf("\nDigite o nome do item que deseja excluir: ");
    fgets(nome, 30, stdin);

    struct Item *Atual = *Inicio;
    struct Item *Anterior = NULL;

    /*  Percorre a lista procurando o item */
    while (Atual != NULL && strcmp(Atual->nome, nome) != 0)
    {
        Anterior = Atual;
        Atual = Atual->proximo;
    }

    /*  Caso o item não tenha sido encontrado */
    if (Atual == NULL)
    {
        printf("\nItem nao encontrado.\n", nome);
        return;
    }

    /*  Caso o item a ser removido seja o primeiro da lista */
    if (Anterior == NULL)
    {
        *Inicio = Atual->proximo;
    }
    else
    {
        /*  Caso esteja no meio ou no fim da lista */
        Anterior->proximo = Atual->proximo;
    }

    /*  Libera a memória do item removido */
    free(Atual);
    printf("\nItem removido com sucesso!\n");
}

void listarItem(struct Item** Inicio)
{
    if (*Inicio == NULL)
    {
        printf("\nInventario vazio\n");
        return;
    }
    struct Item* Atual = *Inicio;
    int i = 0;
    while (Atual != NULL)
    {
        printf("\n--Item %d\n",i+1);
        printf("Nome: %s",Atual->nome);
        printf("Tipo: %s",Atual->tipo);
        printf("Quantidade: %d\n\n",Atual->quantidade);
        Atual = Atual->proximo;
        i++;
    }
    free(Atual);
}

void buscarItem(struct Item** Inicio)
{
        if (*Inicio == NULL) {
            printf("\nInventario vazio\n");
            return;
        }
        struct Item* Atual = *Inicio;
        int i = 0, j = 0;
        char nome[30];
        printf("\nQual o nome do item que deseja buscar: ");
        fgets(nome,30,stdin);
        while (Atual != NULL && i == 0){
            if(strcmp(Atual->nome, nome) == 0){
                printf("\n--Item %d\n",j+1);
                printf("Nome: %s",Atual->nome);
                printf("Tipo: %s",Atual->tipo);
                printf("Quantidade: %d\n\n",Atual->quantidade);
                i = 1;
            }else{
                Atual = Atual->proximo;
                j++;
            }
            if(i == 0)
                printf("Item nao disponivel!\n\n");
        }
    }
