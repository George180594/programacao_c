#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10

typedef struct {
    char nome[50];
    char tipo[50];
    int quantidade;
} Item;

Item mochila[MAX_ITENS];
int totalItens = 0;

// Limpa o buffer do teclado
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Pausa
void pausar() {
    printf("\nPressione Enter para continuar...");
    limparBuffer();
    getchar();
}

// Listar itens
void listarItens() {

    printf("\n====================================\n");
    printf("   ITENS NA MOCHILA (%d/%d)\n", totalItens, MAX_ITENS);
    printf("====================================\n");

    if (totalItens == 0) {
        printf("Mochila vazia!\n");
    } else {
        printf("%-18s | %-14s | %s\n", "NOME", "TIPO", "QUANTIDADE");
        printf("-----------------------------------------------\n");

        for (int i = 0; i < totalItens; i++) {
            printf("%-18s | %-14s | %d\n",
                   mochila[i].nome,
                   mochila[i].tipo,
                   mochila[i].quantidade);
        }
    }

    printf("\n");
}

// Inserir item
void inserirItem() {

    if (totalItens >= MAX_ITENS) {
        printf("\nMochila cheia! Nao e possivel adicionar mais itens.\n");
        pausar();
        return;
    }

    Item novo;

    printf("\n--- ADICIONAR ITEM ---\n");

    printf("Nome do item: ");
    scanf(" %[^\n]", novo.nome);

    printf("Tipo do item: ");
    scanf(" %[^\n]", novo.tipo);

    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);

    if (novo.quantidade <= 0) {
        printf("\nQuantidade invalida! O item nao foi adicionado.\n");
        pausar();
        return;
    }

    mochila[totalItens] = novo;
    totalItens++;

    printf("\nItem '%s' adicionado com sucesso!\n", novo.nome);

    listarItens();
    pausar();
}

// Remover item
void removerItem() {

    if (totalItens == 0) {
        printf("\nMochila vazia!\n");
        pausar();
        return;
    }

    char nome[50];
    int pos = -1;

    printf("\n--- REMOVER ITEM ---\n");
    printf("Digite o nome do item a remover: ");
    scanf(" %[^\n]", nome);

    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            pos = i;
            break;
        }
    }

    if (pos == -1) {
        printf("\nItem nao encontrado!\n");
    } else {
        for (int i = pos; i < totalItens - 1; i++) {
            mochila[i] = mochila[i + 1];
        }

        totalItens--;

        printf("\nItem '%s' removido com sucesso!\n", nome);
    }

    listarItens();
    pausar();
}

// Buscar item por nome
void buscarItem() {

    if (totalItens == 0) {
        printf("\nMochila vazia!\n");
        pausar();
        return;
    }

    char nome[50];
    int encontrado = 0;

    printf("\n--- BUSCAR ITEM ---\n");
    printf("Digite o nome do item: ");
    scanf(" %[^\n]", nome);

    for (int i = 0; i < totalItens; i++) {

        if (strcmp(mochila[i].nome, nome) == 0) {

            encontrado = 1;

            printf("\nItem encontrado!\n");
            printf("Nome: %s\n", mochila[i].nome);
            printf("Tipo: %s\n", mochila[i].tipo);
            printf("Quantidade: %d\n", mochila[i].quantidade);

            break;
        }
    }

    if (!encontrado) {
        printf("\nO item '%s' nao foi encontrado na mochila.\n", nome);
    }

    pausar();
}

// Menu
void menu() {

    printf("\n\n");
    printf("========== MOCHILA DE SOBREVIVENCIA ==========\n");
    printf("Itens cadastrados: %d/%d\n\n", totalItens, MAX_ITENS);

    printf("1. Adicionar item\n");
    printf("2. Remover item\n");
    printf("3. Listar itens\n");
    printf("4. Buscar item por nome\n");
    printf("0. Sair\n");

    printf("\nEscolha uma opcao: ");
}

// Main
int main() {

    int opcao;

    do {
        menu();
        scanf("%d", &opcao);

        switch (opcao) {

            case 1:
                inserirItem();
                break;

            case 2:
                removerItem();
                break;

            case 3:
                listarItens();
                pausar();
                break;

            case 4:
                buscarItem();
                break;

            case 0:
                printf("\nGame Over... Mochila fechada.\n");
                break;

            default:
                printf("\nOpcao invalida! Tente novamente.\n");
                pausar();
        }

    } while (opcao != 0);

    return 0;
}