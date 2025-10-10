#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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

/* Protótipos das funções */
void inserirItem(struct Item** Inicio);
void excluirItem(struct Item** Inicio);
void buscarItem(struct Item** Inicio);


int main(){
    int opcao = 0;
    int qtditens = 0;
    struct Item *Inicio = NULL;
    /* Montando menu de Interação com o inventário */
    do{
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
            default:
                printf("Opcao invalida!\n");
                break;
        }
    }while (opcao != 0);

}

void inserirItem(struct Item** Inicio){
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

void excluirItem(struct Item** Inicio) {
    if (*Inicio == NULL) {
        printf("\nInventario vazio. Nada para excluir.\n");
        return;
    }

    char nome[30];
    printf("\nDigite o nome do item que deseja excluir: ");
    fgets(nome, 30, stdin);

    struct Item *Atual = *Inicio;
    struct Item *Anterior = NULL;

    /*  Percorre a lista procurando o item */
    while (Atual != NULL && strcmp(Atual->nome, nome) != 0) {
        Anterior = Atual;
        Atual = Atual->proximo;
    }

    /*  Caso o item não tenha sido encontrado */
    if (Atual == NULL) {
        printf("\nItem nao encontrado.\n", nome);
        return;
    }

    /*  Caso o item a ser removido seja o primeiro da lista */
    if (Anterior == NULL) {
        *Inicio = Atual->proximo;
    } else {
        /*  Caso esteja no meio ou no fim da lista */
        Anterior->proximo = Atual->proximo;
    }

    /*  Libera a memória do item removido */
    free(Atual);
    printf("\nItem removido com sucesso!\n");
}


void listarItem(struct Item** Inicio){
    if (*Inicio == NULL) {
        printf("\nInventario vazio\n");
        return;
    }
    struct Item* Atual = *Inicio;
    int i = 0;
    while (Atual != NULL){
        printf("\n--Item %d\n",i+1);
        printf("Nome: %s",Atual->nome);
        printf("Tipo: %s",Atual->tipo);
        printf("Quantidade: %d\n\n",Atual->quantidade);
        Atual = Atual->proximo;
        i++;
    }
    free(Atual);
}

void buscarItem(struct Item** Inicio){
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
