#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 10
#define TAM_NOME 30
#define TAM_TIPO 20

// ----------------- DEFINIÇÃO DA STRUCT -------------------
// Representa um item da mochila do jogador
typedef struct
{
    char nome[TAM_NOME]; // Nome do item (ex: Pistola, Bandagem)
    char tipo[TAM_TIPO]; // Tipo do item (ex: arma, munição, cura)
    int quantidade;      // Quantidade do item
} Item;

// ----------------- VARIÁVEIS GLOBAIS ----------------------
Item mochila[MAX_ITENS]; // Vetor que armazena os itens
int qtdItens = 0;        // Quantidade de itens cadastrados

// ----------------- FUNÇÕES PRINCIPAIS ---------------------

// Inserir item na mochila
void inserirItem()
{
    if (qtdItens == MAX_ITENS)
    {
        printf("\nA mochila está cheia! Não é possível adicionar mais itens.\n");
        return;
    }

    Item novo;

    printf("\n--- Cadastro de Item ---\n");
    printf("Nome: ");
    getchar(); // limpar \n pendente
    fgets(novo.nome, TAM_NOME, stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0'; // remove \n

    printf("Tipo (arma, municao, cura, ferramenta...): ");
    fgets(novo.tipo, TAM_TIPO, stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);

    // Adiciona ao vetor
    mochila[qtdItens] = novo;
    qtdItens++;

    printf("\nItem \"%s\" adicionado com sucesso!\n", novo.nome);
}

// Remover item pelo nome
void removerItem()
{
    if (qtdItens == 0)
    {
        printf("\nA mochila está vazia! Nada para remover.\n");
        return;
    }

    char nomeBusca[TAM_NOME];
    printf("\nDigite o nome do item a ser removido: ");
    getchar();
    fgets(nomeBusca, TAM_NOME, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    int pos = -1;
    for (int i = 0; i < qtdItens; i++)
    {
        if (strcmp(mochila[i].nome, nomeBusca) == 0)
        {
            pos = i;
            break;
        }
    }

    if (pos == -1)
    {
        printf("\nItem \"%s\" não encontrado na mochila.\n", nomeBusca);
        return;
    }

    // Desloca os itens à esquerda
    for (int i = pos; i < qtdItens - 1; i++)
    {
        mochila[i] = mochila[i + 1];
    }
    qtdItens--;

    printf("\nItem \"%s\" removido com sucesso!\n", nomeBusca);
}

// Listar todos os itens
void listarItens()
{
    if (qtdItens == 0)
    {
        printf("\nA mochila está vazia!\n");
        return;
    }

    printf("\n--- Itens da Mochila ---\n");
    for (int i = 0; i < qtdItens; i++)
    {
        printf("%d. Nome: %s | Tipo: %s | Quantidade: %d\n",
               i + 1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
}

// Buscar item pelo nome (busca sequencial)
void buscarItem()
{
    if (qtdItens == 0)
    {
        printf("\nA mochila está vazia!\n");
        return;
    }

    char nomeBusca[TAM_NOME];
    printf("\nDigite o nome do item para buscar: ");
    getchar();
    fgets(nomeBusca, TAM_NOME, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    for (int i = 0; i < qtdItens; i++)
    {
        if (strcmp(mochila[i].nome, nomeBusca) == 0)
        {
            printf("\nItem encontrado!\n");
            printf("Nome: %s | Tipo: %s | Quantidade: %d\n",
                   mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
            return;
        }
    }

    printf("\nItem \"%s\" não encontrado na mochila.\n", nomeBusca);
}

// ----------------- MENU PRINCIPAL ------------------------
int main()
{
    int opcao;

    do
    {
        printf("\n=== SISTEMA DE INVENTÁRIO ===\n");
        printf("1. Adicionar item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Buscar item\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            inserirItem();
            listarItens();
            break;
        case 2:
            removerItem();
            listarItens();
            break;
        case 3:
            listarItens();
            break;
        case 4:
            buscarItem();
            break;
        case 0:
            printf("\nSaindo do sistema... Até a próxima!\n");
            break;
        default:
            printf("\nOpção inválida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}
