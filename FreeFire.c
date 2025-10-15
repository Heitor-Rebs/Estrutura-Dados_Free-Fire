#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#define MAX_COMPONENTES 20


/* Estrutura do componente */
struct Componente
{
    char nome[30];
    char tipo[20];
    int prioridade;
};

void limparbuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

}

void trocar(struct Componente *a, struct Componente *b)
{
    struct Componente temp = *a;
    *a = *b;
    *b = temp;
}

/* Protótipos das funções da lista sequencial*/
void inserircomponente(struct Componente componentes[], int *qtditens);
void mostrarComponentes(struct Componente componentes[], int *qtditens);
void bubbleSortNome(struct Componente componentes[], int *qtditens, int *comparacoes);
void insertionSortTipo(struct Componente componentes[], int *qtditens, int *comparacoes);
void selectionSortPrioridade(struct Componente componentes[], int *qtditens, int *comparacoes);
void buscaBinariaPorNome(struct Componente componentes[], int *qtditens, int *comparacoes);
void medirTempo(void (*algoritmo)(struct Componente[], int*, int*), struct Componente componentes[], int *qtditens);


int main()
{
    struct Componente componentes[MAX_COMPONENTES];
    int n = 0;
    int opcao, *comparacoes = 0, *tipoordenacao = 0;
    int qtditens = 0;
    /* Montando menu de Interação com o inventário */
    do
    {
        opcao = 0;
        printf("\n----Menu de Interacao----\n\n");
        printf("1 - Cadastrar componente (ate %d)\n", MAX_COMPONENTES);
        printf("2 - Mostrar componentes\n");
        printf("3 - Ordenar por nome (Bubble Sort)\n");
        printf("4 - Ordenar por tipo (Insertion Sort)\n");
        printf("5 - Ordenar por prioridade (Selection Sort)\n");
        printf("6 - Buscar componente-chave por nome (Busca Binaria - funciona so apos ordenar por nome)\n");
        printf("7 - Escolher ordenacao\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d",&opcao);
        limparbuffer();

        switch (opcao)
        {
        case 1:
            inserircomponente(componentes, &qtditens);
            break;
        case 2:
            mostrarComponentes(componentes, &qtditens);
            break;
        case 3:
            if(qtditens == 0)
            {
                printf("Inventario vazio!\n");
                continue;
            }
            /* Apenas roda uma simulação para calcular comparações e tempo */
            medirTempo(bubbleSortNome, componentes, &qtditens);
            break;
        case 4:
            if(qtditens == 0)
            {
                printf("Inventario vazio!\n");
                continue;
            }
            medirTempo(insertionSortTipo, componentes, &qtditens);
            break;
        case 5:
            if(qtditens == 0)
            {
                printf("Inventario vazio!\n");
                continue;
            }
            medirTempo(selectionSortPrioridade, componentes, &qtditens);
            break;
        case 6:
            buscaBinariaPorNome(componentes, &qtditens, &comparacoes);
            break;
        case 7:
            /* Deixa o usuário escolher o tipo de ordenação baseado nas comparações feitas antes */
            do
            {
                opcao = 0;
                printf("\n----Escolha de Ordenacao----\n\n");
                printf("1 - Por nome (Bubble Sort)\n");
                printf("2 - Por tipo (Insertion Sort)\n");
                printf("3 - Por nome (Selection Sort)\n");
                scanf("%d",&opcao);
                limparbuffer();
                switch(opcao)
                {
                    case 1:
                        bubbleSortNome(componentes, &qtditens, &comparacoes);
                        mostrarComponentes(componentes, &qtditens);
                        break;
                    case 2:
                        insertionSortTipo(componentes, &qtditens, &comparacoes);
                        mostrarComponentes(componentes, &qtditens);
                        break;
                    case 3:
                        selectionSortPrioridade(componentes, &qtditens, &comparacoes);
                        mostrarComponentes(componentes, &qtditens);
                        break;
                    default:
                        printf("Opcao Invalida!\n");
                        break;
                }
            }while(opcao != 0);
            break;
        case 0:
            printf("Saindo...");
            break;
        default:
            printf("Opcao Invalida!\n");
            break;
        }

    }
    while(opcao != 0);
}

/* Insere componentes */
void inserircomponente(struct Componente componentes[], int *qtditens)
{
    if(*qtditens == MAX_COMPONENTES)
    {
        printf("Inventario cheio!\n");
        return;
    }
    printf("\n#Cadastrando Componente#");
    printf("\nNome do Componente: ");
    fgets(componentes[*qtditens].nome,30,stdin);
    componentes[*qtditens].nome[strcspn(componentes[*qtditens].nome, "\n")] = '\0';
    printf("Tipo do Item: ");
    fgets(componentes[*qtditens].tipo,20,stdin);
    componentes[*qtditens].tipo[strcspn(componentes[*qtditens].tipo, "\n")] = '\0';
    printf("Prioridade do item: ");
    scanf("%d",&componentes[*qtditens].prioridade);
    limparbuffer();
    (*qtditens)++;
}

/* Mostra componentes */
void mostrarComponentes(struct Componente componentes[], int *qtditens)
{
    if(*qtditens == 0)
    {
        printf("Inventario vazio!\n");
        return;
    }
    int i = 0;
    printf("\n#Listando Componentes#");
    /* Percorrendo o inventario todo, imprimindo cada elemento */
    for(i=0; i<*qtditens; i++)
    {
        printf("\nComponente %d\n",i+1);
        printf("Nome: %s | Tipo: %s |  Prioridade: %d\n",componentes[i].nome,componentes[i].tipo,componentes[i].prioridade);
    }
}

/* Ordena componentes por nome (Bubble Sort) */
void bubbleSortNome(struct Componente componentes[], int *qtditens, int *comparacoes)
{
    if(*qtditens == 0)
    {
        printf("\nInventario vazio!\n");
        return;
    }
    *comparacoes = 0;
    int i = 0, j = 0;
    for (i = 0; i < *qtditens - 1; i++)
    {
        for (j = 0; j < *qtditens - 1 - i; j++)
        {
            (*comparacoes)++;
            if (strcmp(componentes[j].nome, componentes[j + 1].nome) > 0)
            {
                trocar(&componentes[j], &componentes[j + 1]);
            }
        }
    }
    printf("\n#Componentes Ordenados#\n");
}

/* Ordena componentes por tipo (Insertion Sort) */
void insertionSortTipo(struct Componente componentes[], int *qtditens, int *comparacoes)
{
    if(*qtditens == 0)
    {
        printf("\nInventario vazio!\n");
        return;
    }
    *comparacoes = 0;
    int i = 1, j = 0;
    for (i = 1; i < *qtditens; i++)
    {
        struct Componente chave = componentes[i];
        j = i - 1;

        /* Move os elementos maiores que a chave uma posição à frente */
        while (j >= 0 && strcmp(componentes[j].tipo, chave.tipo) > 0)
        {
            (*comparacoes)++;
            componentes[j + 1] = componentes[j];
            j--;
        }

        componentes[j + 1] = chave;
    }
    printf("\n#Componentes Ordenados#\n");
}

/* Ordena componentes por prioridade (Selection Sort) */
void selectionSortPrioridade(struct Componente componentes[], int *qtditens, int *comparacoes)
{
    if(*qtditens == 0)
    {
        printf("\nInventario vazio!\n");
        return;
    }
    int i = 0, j = 0;
    *comparacoes = 0;
    for (i = 0; i < *qtditens - 1; i++)
    {
        int indiceMenor = i;
        for (j = i + 1; j < *qtditens; j++)
        {
            (*comparacoes)++;
            if (componentes[j].prioridade < componentes[indiceMenor].prioridade)
            {
                indiceMenor = j;
            }
        }
        if (indiceMenor != i)
        {
            trocar(&componentes[i], &componentes[indiceMenor]);
        }
    }
    printf("\n#Componentes Ordenados#\n");
}

/* Busca componente por uma busca ninário */
void buscaBinariaPorNome(struct Componente componentes[], int *qtditens, int *comparacoes)
{
    if(*comparacoes == 0)
    {
        printf("Componentes nao ordenados!\n");
        return;
    }
    printf("\n#Buscando Componente#");
    char nome[30];
    int inicio = 0, fim = *qtditens - 1, combinacoes = 0;
    printf("\nNome do Item: ");
    fgets(nome,30,stdin);
    nome[strcspn(nome, "\n")] = '\0';

    while (inicio <= fim)
    {
        /* Pegando o meio do vetor e comparando com o nome passado pelo usuario */
        int meio = (inicio + fim) / 2;
        /* Caso o item do meio confere com o item procurado */
        if (strcmp(componentes[meio].nome, nome) == 0)
        {
            combinacoes++;
            printf("\nNumero de Comparacoes: %d\n",combinacoes);
            printf("Componente %d\n",meio+1);
            printf("Nome: %s | Tipo: %s |  Quantidade: %d\n",componentes[meio].nome,componentes[meio].tipo,componentes[meio].prioridade);
            return 0;
            /* Caso o item esteja antes do item do meio */
        }
        else if (strcmp(componentes[meio].nome, nome) < 0)
        {
            combinacoes++;
            inicio = meio + 1;
        }
        /* Caso o item esteja depois do item do meio */
        else
        {
            combinacoes++;
            fim = meio - 1;
        }
    }
    /* Caso nao encontre o item */
    printf("Item nao encontrado!\n");
    return 0;
}

/* Função para medir o tempo de execução e número de comparações de um algoritmo */
void medirTempo(void (*algoritmo)(struct Componente[], int*, int*), struct Componente componentes[], int *qtditens)
{
    struct Componente copia[MAX_COMPONENTES];
    int comparacoes = 0, i = 0;

    /* Cria uma cópia dos componentes originais */
    for (i = 0; i < *qtditens; i++)
        copia[i] = componentes[i];

    /* Inicia a contagem do tempo */
    clock_t inicio = clock();

    /* Executa o algoritmo passado como parâmetro */
    algoritmo(copia, qtditens, &comparacoes);

    /* Finaliza a contagem do tempo */
    clock_t fim = clock();

    /* Calcula o tempo total em segundos */
    double tempo_exec = (double)(fim - inicio) / CLOCKS_PER_SEC;

    /* Exibe os resultados */
    printf("Tempo de execucao: %.6f segundos\n", tempo_exec);
    printf("Numero de comparacoes: %d\n", comparacoes);

    /* Atualiza o vetor original com a versão ordenada */
    for (i = 0; i < *qtditens; i++)
        componentes[i] = copia[i];
}
