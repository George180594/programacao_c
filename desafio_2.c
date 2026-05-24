#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAMANHO_FILA 5
#define TAMANHO_PILHA 3

//Definifição da estrutura de uma peça
typedef struct {
    char nome;
    int id;
} Peca;

// Fila 
Peca fila[TAMANHO_FILA];
int inicioFila = 0;
int fimFila = 0;
int qFila = 0;


// Pilha de reserva

Peca pilha[TAMANHO_PILHA];
int topoPilha = -1;

int proximoId = 0;

// Gera uma peça aleatória
Peca gerarPeca() {
    char tipos[] = {'I', 'O', 'T', 'L'};
    int indice = rand() % 4;

    Peca novaPeca;
    novaPeca.nome = tipos[indice];
    novaPeca.id = proximoId;

    proximoId++;

    return novaPeca;
}

// Andamento da fila e pilha
int filaCheia() {
    return qFila == TAMANHO_FILA;
}

int pilhaCheia() {
    return topoPilha == TAMANHO_PILHA - 1;
}

int filaVazia() {
    return qFila == 0;
}
int pilhaVazia() {
    return topoPilha == -1;
}
// --------------------------------

void inserirNaFila(Peca peca) {
    if (filaCheia()) {
        printf("\nA fila esta cheia!\n");
        return;
    }

    fila[fimFila] = peca;
    fimFila = (fimFila + 1) % TAMANHO_FILA;
    qFila++;
}


Peca removerDaFila() {
    Peca peca_rem = fila[inicioFila];

    inicioFila = (inicioFila + 1) % TAMANHO_FILA;
    qFila--;

    return peca_rem;
}

void completarFila() {
    if (!filaCheia()) {
        Peca novaPeca = gerarPeca();
        inserirNaFila(novaPeca);
    }
}

// Inicializa a fila com 5 peças
void inicializarFila() {
    for (int i = 0; i < TAMANHO_FILA; i++) {
        Peca novaPeca = gerarPeca();
        inserirNaFila(novaPeca);
    }
}


void jogarPeca() {
    if (filaVazia()) {
        printf("\nNao ha pecas na fila para jogar.\n");
        return;
    }

    Peca pecaJogada = removerDaFila();

    printf("\nPeca jogada: [%c %d]\n", pecaJogada.nome, pecaJogada.id);

    completarFila();
}


void reservarPeca() {
    if (filaVazia()) {
        printf("\nNao ha pecas na fila para reservar.\n");
        return;
    }

    if (pilhaCheia()) {
        printf("\nA pilha de reserva esta cheia! Nao e possivel reservar outra peca.\n");
        return;
    }

    Peca pecaReservada = removerDaFila();

    topoPilha++;
    pilha[topoPilha] = pecaReservada;

    printf("\nPeca reservada: [%c %d]\n", pecaReservada.nome, pecaReservada.id);

    completarFila();
}

void usarPecaReservada() {
    if (pilhaVazia()) {
        printf("\nNao ha pecas reservadas para usar.\n");
        return;
    }

    Peca pecaUsada = pilha[topoPilha];
    topoPilha--;

    printf("\nPeca reservada usada: [%c %d]\n", pecaUsada.nome, pecaUsada.id);

}

// Exibe a fila e a pilha
void exibirEstadoAtual() {
    printf("\n====================================\n");
    printf("           ESTADO ATUAL\n");
    printf("====================================\n");

    printf("\nFila de pecas:\n");

    if (filaVazia()) {
        printf("Fila vazia!");
    } else {
        int posicao = inicioFila;

        for (int i = 0; i < qFila; i++) {
            printf("[%c %d] ", fila[posicao].nome, fila[posicao].id);
            posicao = (posicao + 1) % TAMANHO_FILA;
        }
    }

    printf("\n\nPilha de reserva (Topo -> Base):\n");

    if (pilhaVazia()) {
        printf("Pilha vazia!");
    } else {
        for (int i = topoPilha; i >= 0; i--) {
            printf("[%c %d] ", pilha[i].nome, pilha[i].id);
        }
    }

    printf("\n\nFila: %d/%d", qFila, TAMANHO_FILA);
    printf("\nPilha: %d/%d\n", topoPilha + 1, TAMANHO_PILHA);

    printf("\n");
}

// menu
void menu() {
    printf("\nOpcoes de acao:\n");
    printf("1-Jogar peca\n");
    printf("2-Reservar peca\n");
    printf("3-Usar peca reservada\n");
    printf("0-Sair\n");
    printf("Opcao: ");
}

int main() {
    int opcao;

    srand(time(NULL));

    printf("TETRIS STACK - FILA E PILHA DE PECAS\n");

    inicializarFila();

    do {
        exibirEstadoAtual();
        menu();

        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                jogarPeca();
                break;

            case 2:
                reservarPeca();
                break;

            case 3:
                usarPecaReservada();
                break;

            case 0:
                printf("\nSaindo do jogo...\n");
                break;

            default:
                printf("\nOpcao invalida! Tente novamente.\n");

        }

    } while (opcao != 0);

    return 0;
}