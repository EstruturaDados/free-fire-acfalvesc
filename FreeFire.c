#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ITENS 10
#define TAM_NOME 30
#define TAM_TIPO 20

// --- NOVO: componentes da torre ---
#define MAX_COMPONENTES 20
#define TAM_NOME_COMP 30
#define TAM_TIPO_COMP 20

typedef struct
{
    char nome[TAM_NOME]; // Nome do item (ex: Pistola, Bandagem)
    char tipo[TAM_TIPO]; // Tipo do item (ex: arma, munição, cura)
    int quantidade;      // Quantidade do item
} Item;

// Estrutura para lista encadeada
typedef struct Node
{
    Item item;
    struct Node *prox;
} Node;

// ----------------- STRUCT COM COMPONENTES DA TORRE -------------------
typedef struct
{
    char nome[TAM_NOME_COMP]; // ex: "chip central"
    char tipo[TAM_TIPO_COMP]; // ex: "controle", "suporte", "propulsão"
    int prioridade;           // 1..10 (1 menos importante, 10 mais importante)
} Componente;

// ----------------- VARIÁVEIS GLOBAIS ----------------------
Item mochilaVetor[MAX_ITENS]; // Vetor que armazena os itens
int qtdItensVetor = 0;        // Quantidade de itens no vetor
Node *mochilaLista = NULL;    // Lista encadeada

// Componente da torre
Componente componentes[MAX_COMPONENTES];
int qtdComponentes = 0;

// Indica por qual critério o array de componentes está ordenado atualmente
enum
{
    NAO_ORDENADO = 0,
    ORDENADO_NOME,
    ORDENADO_TIPO,
    ORDENADO_PRIORIDADE
} ultimoOrdenamento = NAO_ORDENADO;

// ----------------- FUNÇÕES AUXILIARES ---------------------
void limparBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

// ----------------- FUNÇÕES DO VETOR (seu código original) -----------------------
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

// Ordenar por nome (Bubble Sort) - versão para mochilaVetor (mantida)
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

// Busca binária (para mochilaVetor)
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

// ----------------- MÓDULO: COMPONENTES DA TORRE -----------------------

// Cadastro de componentes (até MAX_COMPONENTES)
void cadastrarComponente()
{
    if (qtdComponentes == MAX_COMPONENTES)
    {
        printf("\n[Componentes] Capacidade máxima atingida (%d).\n", MAX_COMPONENTES);
        return;
    }

    Componente c;
    printf("\n--- Cadastrar Componente da Torre ---\n");
    printf("Nome (ex: chip central): ");
    limparBuffer();
    fgets(c.nome, TAM_NOME_COMP, stdin);
    c.nome[strcspn(c.nome, "\n")] = '\0';

    printf("Tipo (ex: controle, suporte, propulsão): ");
    fgets(c.tipo, TAM_TIPO_COMP, stdin);
    c.tipo[strcspn(c.tipo, "\n")] = '\0';

    do
    {
        printf("Prioridade (1-10): ");
        if (scanf("%d", &c.prioridade) != 1)
        {
            limparBuffer();
            c.prioridade = 0;
        }
    } while (c.prioridade < 1 || c.prioridade > 10);

    componentes[qtdComponentes++] = c;
    ultimoOrdenamento = NAO_ORDENADO;
    printf("Componente cadastrado com sucesso! Total: %d\n", qtdComponentes);
}

void listarComponentes()
{
    if (qtdComponentes == 0)
    {
        printf("\n[Nenhum componente cadastrado]\n");
        return;
    }

    printf("\n--- Componentes da Torre (%d) ---\n", qtdComponentes);
    for (int i = 0; i < qtdComponentes; i++)
    {
        printf("%2d. Nome: %-25s | Tipo: %-12s | Prioridade: %d\n",
               i + 1, componentes[i].nome, componentes[i].tipo, componentes[i].prioridade);
    }
}

// --- Bubble Sort por nome (strings) --- conta comparações e tempo
void bubbleSort_nome(long long *comparacoes, double *tempo)
{
    *comparacoes = 0;
    clock_t inicio = clock();

    for (int i = 0; i < qtdComponentes - 1; i++)
    {
        for (int j = 0; j < qtdComponentes - i - 1; j++)
        {
            (*comparacoes)++;
            if (strcmp(componentes[j].nome, componentes[j + 1].nome) > 0)
            {
                Componente tmp = componentes[j];
                componentes[j] = componentes[j + 1];
                componentes[j + 1] = tmp;
            }
        }
    }

    clock_t fim = clock();
    *tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    ultimoOrdenamento = ORDENADO_NOME;
}

// --- Insertion Sort por tipo (string) --- conta comparações e tempo
void insertionSort_tipo(long long *comparacoes, double *tempo)
{
    *comparacoes = 0;
    clock_t inicio = clock();

    for (int i = 1; i < qtdComponentes; i++)
    {
        Componente chave = componentes[i];
        int j = i - 1;
        // enquanto j >= 0 e componentes[j].tipo > chave.tipo
        while (j >= 0)
        {
            (*comparacoes)++;
            if (strcmp(componentes[j].tipo, chave.tipo) > 0)
            {
                componentes[j + 1] = componentes[j];
                j--;
            }
            else
                break;
        }
        componentes[j + 1] = chave;
    }

    clock_t fim = clock();
    *tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    ultimoOrdenamento = ORDENADO_TIPO;
}

// --- Selection Sort por prioridade (int) --- conta comparações e tempo
void selectionSort_prioridade(long long *comparacoes, double *tempo)
{
    *comparacoes = 0;
    clock_t inicio = clock();

    for (int i = 0; i < qtdComponentes - 1; i++)
    {
        int idxMin = i;
        for (int j = i + 1; j < qtdComponentes; j++)
        {
            (*comparacoes)++;
            // queremos ordenar do maior para o menor prioridade?
            // Requisito não especifica, assumiremos ordem decrescente (prioridade maior primeiro).
            if (componentes[j].prioridade > componentes[idxMin].prioridade)
                idxMin = j;
        }
        if (idxMin != i)
        {
            Componente tmp = componentes[i];
            componentes[i] = componentes[idxMin];
            componentes[idxMin] = tmp;
        }
    }

    clock_t fim = clock();
    *tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    ultimoOrdenamento = ORDENADO_PRIORIDADE;
}

// Busca binária por nome: só válida se o vetor estiver ordenado por nome
int buscaBinaria_nome(const char *chave, long long *comparacoes)
{
    *comparacoes = 0;
    int esq = 0, dir = qtdComponentes - 1;
    while (esq <= dir)
    {
        int meio = (esq + dir) / 2;
        (*comparacoes)++;
        int cmp = strcmp(componentes[meio].nome, chave);
        if (cmp == 0)
            return meio; // índice encontrado
        else if (cmp < 0)
            esq = meio + 1;
        else
            dir = meio - 1;
    }
    return -1; // não encontrado
}

// Função que permite ao jogador escolher estratégia (critério) e executar ordenação
void escolherEOrdenar()
{
    if (qtdComponentes == 0)
    {
        printf("\nNenhum componente cadastrado. Cadastre antes de ordenar.\n");
        return;
    }

    int opc;
    printf("\n--- Escolher Estratégia de Ordenação ---\n");
    printf("1. Ordenar por NOME (Bubble Sort)\n");
    printf("2. Ordenar por TIPO (Insertion Sort)\n");
    printf("3. Ordenar por PRIORIDADE (Selection Sort - decrescente)\n");
    printf("Escolha: ");
    scanf("%d", &opc);

    long long comps = 0;
    double tempo = 0.0;

    switch (opc)
    {
    case 1:
        bubbleSort_nome(&comps, &tempo);
        printf("Ordenado por NOME usando Bubble Sort.\n");
        printf("Comparações: %lld | Tempo: %.6f s\n", comps, tempo);
        break;
    case 2:
        insertionSort_tipo(&comps, &tempo);
        printf("Ordenado por TIPO usando Insertion Sort.\n");
        printf("Comparações: %lld | Tempo: %.6f s\n", comps, tempo);
        break;
    case 3:
        selectionSort_prioridade(&comps, &tempo);
        printf("Ordenado por PRIORIDADE usando Selection Sort (maior prioridade primeiro).\n");
        printf("Comparações: %lld | Tempo: %.6f s\n", comps, tempo);
        break;
    default:
        printf("Opção inválida.\n");
        return;
    }

    listarComponentes();
}

// Função para buscar componente-chave (apenas após ordenação por nome)
void buscarComponenteChave()
{
    if (qtdComponentes == 0)
    {
        printf("\nNenhum componente cadastrado.\n");
        return;
    }

    if (ultimoOrdenamento != ORDENADO_NOME)
    {
        printf("\nBusca binária só está disponível após ordenar por NOME (use a opção de ordenar por nome primeiro).\n");
        return;
    }

    char chave[TAM_NOME_COMP];
    printf("\nDigite o nome do componente-chave para buscar (busca binária): ");
    limparBuffer();
    fgets(chave, TAM_NOME_COMP, stdin);
    chave[strcspn(chave, "\n")] = '\0';

    long long comps = 0;
    int idx = buscaBinaria_nome(chave, &comps);

    if (idx >= 0)
    {
        printf("Componente-CHAVE encontrado! (índice %d)\n", idx);
        printf("Nome: %s | Tipo: %s | Prioridade: %d\n",
               componentes[idx].nome, componentes[idx].tipo, componentes[idx].prioridade);
        printf("Comparações na busca: %lld\n", comps);
    }
    else
    {
        printf("Componente-CHAVE NÃO encontrado. Comparações: %lld\n", comps);
    }
}

// Montagem final: exibe os componentes na ordem atual e confirma presença do componente-chave (opcional)
void montagemFinal()
{
    if (qtdComponentes == 0)
    {
        printf("\nNenhum componente cadastrado para montar a torre.\n");
        return;
    }

    printf("\n--- Montagem Final da Torre ---\n");
    listarComponentes();

    char chave[TAM_NOME_COMP];
    printf("\nDigite o nome do componente-chave para confirmar sua presença (pode usar busca binária se ordenado por nome): ");
    limparBuffer();
    fgets(chave, TAM_NOME_COMP, stdin);
    chave[strcspn(chave, "\n")] = '\0';

    int encontrado = -1;
    long long compsSeq = 0;

    // Se ordenado por nome, usamos busca binária
    if (ultimoOrdenamento == ORDENADO_NOME)
    {
        long long compsBin = 0;
        int idx = buscaBinaria_nome(chave, &compsBin);
        if (idx >= 0)
            encontrado = idx;
        printf("Busca usada: BUSCA BINÁRIA (ordenado por nome). Comparações: %lld\n", compsBin);
    }
    else
    {
        // busca sequencial e contagem
        for (int i = 0; i < qtdComponentes; i++)
        {
            compsSeq++;
            if (strcmp(componentes[i].nome, chave) == 0)
            {
                encontrado = i;
                break;
            }
        }
        printf("Busca usada: BUSCA SEQUENCIAL. Comparações: %lld\n", compsSeq);
    }

    if (encontrado >= 0)
    {
        printf("Componente-chave PRESENTE: %s (Tipo: %s | Prioridade: %d)\n",
               componentes[encontrado].nome, componentes[encontrado].tipo, componentes[encontrado].prioridade);
        printf(">>> Torre de resgate: ativação desbloqueada!\n");
    }
    else
    {
        printf("Componente-chave ausente: impossibilita ativação da torre.\n");
    }
}

// ----------------- MENU PRINCIPAL ------------------------
int main()
{
    int opcao;

    do
    {
        printf("\n=== SISTEMA DE INVENTÁRIO & MÓDULO TORRE DE RESGATE ===\n");
        printf("1. Inserir item (Vetor)\n");
        printf("2. Remover item (Vetor)\n");
        printf("3. Listar itens (Vetor)\n");
        printf("4. Buscar Sequencial (Vetor)\n");
        printf("5. Ordenar Vetor (bubble por nome) [mochila]\n");
        printf("6. Buscar Binária (Vetor)\n");
        printf("7. Inserir item (Lista)\n");
        printf("8. Remover item (Lista)\n");
        printf("9. Listar itens (Lista)\n");
        printf("10. Buscar Sequencial (Lista)\n");
        printf("---- MÓDULO TORRE DE RESGATE ----\n");
        printf("11. Cadastrar Componente da Torre (até %d)\n", MAX_COMPONENTES);
        printf("12. Listar Componentes da Torre\n");
        printf("13. Escolher estratégia e ordenar componentes (Bubble/Insertion/Selection)\n");
        printf("14. Buscar componente-chave (busca binária) [exige ordenado por nome]\n");
        printf("15. Montagem final da torre (confirma componente-chave)\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        if (scanf("%d", &opcao) != 1)
        {
            limparBuffer();
            opcao = -1;
        }

        switch (opcao)
        {
        case 1:
            inserirItemVetor();
            break;
        case 2:
            removerItemVetor();
            break;
        case 3:
            listarItensVetor();
            break;
        case 4:
            buscarItemSequencialVetor();
            break;
        case 5:
            ordenarVetor();
            break;
        case 6:
            buscarItemBinariaVetor();
            break;
        case 7:
            inserirItemLista();
            break;
        case 8:
            removerItemLista();
            break;
        case 9:
            listarItensLista();
            break;
        case 10:
            buscarItemSequencialLista();
            break;
        case 11:
            cadastrarComponente();
            break;
        case 12:
            listarComponentes();
            break;
        case 13:
            escolherEOrdenar();
            break;
        case 14:
            buscarComponenteChave();
            break;
        case 15:
            montagemFinal();
            break;
        case 0:
            printf("Saindo...\n");
            break;
        default:
            printf("Opção inválida!\n");
            break;
        }
    } while (opcao != 0);

    // liberar lista encadeada
    Node *atual = mochilaLista;
    while (atual != NULL)
    {
        Node *prox = atual->prox;
        free(atual);
        atual = prox;
    }

    return 0;
}
