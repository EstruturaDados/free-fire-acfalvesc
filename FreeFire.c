#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 10
#define TAM_NOME 30
#define TAM_TIPO 20

// ----------------- DEFINIÇÃO DA STRUCT -------------------
typedef struct
{
    char nome[TAM_NOME];   // Nome do item (ex: Pistola, Bandagem)
    char tipo[TAM_TIPO];   // Tipo do item (ex: arma, munição, cura)
    int quantidade;        // Quantidade do item
} Item;

// Estrutura para lista encadeada
typedef struct Node
{
    Item item;
    struct Node *prox;
} Node;

// ----------------- VARIÁVEIS GLOBAIS ----------------------
Item mochilaVetor[MAX_ITENS];   // Vetor que armazena os itens
int qtdItensVetor = 0;          // Quantidade de itens no vetor
Node *mochilaLista = NULL;      // Lista encadeada

// ----------------- FUNÇÕES AUXILIARES ---------------------
void limparBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// ----------------- FUNÇÕES DO VETOR -----------------------
void inserirItemVetor()
{
    if (qtdItensVetor == MAX_ITENS)
    {
        printf("\n[Mochila Vetor] A mochila está cheia!\n");
        return;
    }

    Item novo;
    printf("\n--- Inserir Item no Vetor ---\n");
    printf("Nome: ");
    limparBuffer();
    fgets(novo.nome, TAM_NOME, stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0';

    printf("Tipo: ");
    fgets(novo.tipo, TAM_TIPO, stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);

    mochilaVetor[qtdItensVetor++] = novo;
    printf("Item adicionado com sucesso!\n");
}

void removerItemVetor()
{
    if (qtdItensVetor == 0)
    {
        printf("\n[Mochila Vetor] A mochila está vazia!\n");
        return;
    }

    char nomeBusca[TAM_NOME];
    printf("\nDigite o nome do item para remover: ");
    limparBuffer();
    fgets(nomeBusca, TAM_NOME, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    int pos = -1;
    for (int i = 0; i < qtdItensVetor; i++)
    {
        if (strcmp(mochilaVetor[i].nome, nomeBusca) == 0)
        {
            pos = i;
            break;
        }
    }

    if (pos == -1)
    {
        printf("Item não encontrado!\n");
        return;
    }

    for (int i = pos; i < qtdItensVetor - 1; i++)
    {
        mochilaVetor[i] = mochilaVetor[i + 1];
    }
    qtdItensVetor--;
    printf("Item removido com sucesso!\n");
}

void listarItensVetor()
{
    if (qtdItensVetor == 0)
    {
        printf("\n[Mochila Vetor] Vazia!\n");
        return;
    }

    printf("\n--- Mochila Vetor ---\n");
    for (int i = 0; i < qtdItensVetor; i++)
    {
        printf("%d. Nome: %s | Tipo: %s | Quantidade: %d\n",
               i + 1, mochilaVetor[i].nome, mochilaVetor[i].tipo, mochilaVetor[i].quantidade);
    }
}

void buscarItemSequencialVetor()
{
    char nomeBusca[TAM_NOME];
    int comparacoes = 0;

    printf("\nDigite o nome do item para buscar (sequencial): ");
    limparBuffer();
    fgets(nomeBusca, TAM_NOME, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    for (int i = 0; i < qtdItensVetor; i++)
    {
        comparacoes++;
        if (strcmp(mochilaVetor[i].nome, nomeBusca) == 0)
        {
            printf("Item encontrado! Nome: %s | Tipo: %s | Qtd: %d\n",
                   mochilaVetor[i].nome, mochilaVetor[i].tipo, mochilaVetor[i].quantidade);
            printf("Comparações realizadas: %d\n", comparacoes);
            return;
        }
    }

    printf("Item não encontrado! Comparações: %d\n", comparacoes);
}

// Ordenar por nome (Bubble Sort)
void ordenarVetor()
{
    for (int i = 0; i < qtdItensVetor - 1; i++)
    {
        for (int j = 0; j < qtdItensVetor - i - 1; j++)
        {
            if (strcmp(mochilaVetor[j].nome, mochilaVetor[j + 1].nome) > 0)
            {
                Item temp = mochilaVetor[j];
                mochilaVetor[j] = mochilaVetor[j + 1];
                mochilaVetor[j + 1] = temp;
            }
        }
    }
    printf("\nMochila ordenada por nome!\n");
}

// Busca binária
void buscarItemBinariaVetor()
{
    if (qtdItensVetor == 0)
    {
        printf("\nMochila vazia!\n");
        return;
    }

    char nomeBusca[TAM_NOME];
    int comparacoes = 0;

    printf("\nDigite o nome do item para buscar (binária): ");
    limparBuffer();
    fgets(nomeBusca, TAM_NOME, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    int esq = 0, dir = qtdItensVetor - 1;
    while (esq <= dir)
    {
        int meio = (esq + dir) / 2;
        comparacoes++;
        int cmp = strcmp(mochilaVetor[meio].nome, nomeBusca);
        if (cmp == 0)
        {
            printf("Item encontrado! Nome: %s | Tipo: %s | Qtd: %d\n",
                   mochilaVetor[meio].nome, mochilaVetor[meio].tipo, mochilaVetor[meio].quantidade);
            printf("Comparações realizadas: %d\n", comparacoes);
            return;
        }
        else if (cmp < 0)
            esq = meio + 1;
        else
            dir = meio - 1;
    }

    printf("Item não encontrado! Comparações: %d\n", comparacoes);
}

// ----------------- FUNÇÕES DA LISTA -----------------------
void inserirItemLista()
{
    Node *novo = (Node *)malloc(sizeof(Node));

    printf("\n--- Inserir Item na Lista ---\n");
    printf("Nome: ");
    limparBuffer();
    fgets(novo->item.nome, TAM_NOME, stdin);
    novo->item.nome[strcspn(novo->item.nome, "\n")] = '\0';

    printf("Tipo: ");
    fgets(novo->item.tipo, TAM_TIPO, stdin);
    novo->item.tipo[strcspn(novo->item.tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &novo->item.quantidade);

    novo->prox = mochilaLista;
    mochilaLista = novo;

    printf("Item adicionado com sucesso!\n");
}

void removerItemLista()
{
    if (mochilaLista == NULL)
    {
        printf("\n[Mochila Lista] Vazia!\n");
        return;
    }

    char nomeBusca[TAM_NOME];
    printf("\nDigite o nome do item para remover: ");
    limparBuffer();
    fgets(nomeBusca, TAM_NOME, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    Node *atual = mochilaLista, *anterior = NULL;

    while (atual != NULL && strcmp(atual->item.nome, nomeBusca) != 0)
    {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL)
    {
        printf("Item não encontrado!\n");
        return;
    }

    if (anterior == NULL)
        mochilaLista = atual->prox;
    else
        anterior->prox = atual->prox;

    free(atual);
    printf("Item removido com sucesso!\n");
}

void listarItensLista()
{
    if (mochilaLista == NULL)
    {
        printf("\n[Mochila Lista] Vazia!\n");
        return;
    }

    printf("\n--- Mochila Lista ---\n");
    Node *atual = mochilaLista;
    int i = 1;
    while (atual != NULL)
    {
        printf("%d. Nome: %s | Tipo: %s | Quantidade: %d\n",
               i++, atual->item.nome, atual->item.tipo, atual->item.quantidade);
        atual = atual->prox;
    }
}

void buscarItemSequencialLista()
{
    if (mochilaLista == NULL)
    {
        printf("\n[Mochila Lista] Vazia!\n");
        return;
    }

    char nomeBusca[TAM_NOME];
    int comparacoes = 0;

    printf("\nDigite o nome do item para buscar (lista): ");
    limparBuffer();
    fgets(nomeBusca, TAM_NOME, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    Node *atual = mochilaLista;
    while (atual != NULL)
    {
        comparacoes++;
        if (strcmp(atual->item.nome, nomeBusca) == 0)
        {
            printf("Item encontrado! Nome: %s | Tipo: %s | Qtd: %d\n",
                   atual->item.nome, atual->item.tipo, atual->item.quantidade);
            printf("Comparações realizadas: %d\n", comparacoes);
            return;
        }
        atual = atual->prox;
    }

    printf("Item não encontrado! Comparações: %d\n", comparacoes);
}

// ----------------- MENU PRINCIPAL ------------------------
int main()
{
    int opcao;

    do
    {
        printf("\n=== SISTEMA DE INVENTÁRIO ===\n");
        printf("1. Inserir item (Vetor)\n");
        printf("2. Remover item (Vetor)\n");
        printf("3. Listar itens (Vetor)\n");
        printf("4. Buscar Sequencial (Vetor)\n");
        printf("5. Ordenar Vetor\n");
        printf("6. Buscar Binária (Vetor)\n");
        printf("7. Inserir item (Lista)\n");
        printf("8. Remover item (Lista)\n");
        printf("9. Listar itens (Lista)\n");
        printf("10. Buscar Sequencial (Lista)\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1: inserirItemVetor(); break;
        case 2: removerItemVetor(); break;
        case 3: listarItensVetor(); break;
        case 4: buscarItemSequencialVetor(); break;
        case 5: ordenarVetor(); break;
        case 6: buscarItemBinariaVetor(); break;
        case 7: inserirItemLista(); break;
        case 8: removerItemLista(); break;
        case 9: listarItensLista(); break;
        case 10: buscarItemSequencialLista(); break;
        case 0: printf("Saindo...\n"); break;
        default: printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    return 0;
}
