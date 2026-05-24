// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// struct No {
//     char valor[50];
//     struct No* esquerda;
//     struct No* direita;
// };

// struct No* criarNo(char valor[]) {
//     struct No* novo = (struct No*) malloc(sizeof(struct No));

//     strcpy(novo->valor, valor);
//     novo->esquerda = NULL;
//     novo->direita = NULL;

//     return novo;
// }

// int altura(struct No* raiz) {
//     if (raiz == NULL) 
//         return 0;

//     int alt_esq = altura(raiz->esquerda);
//     int alt_dir = altura(raiz->direita);

//     return 1 + (alt_esq > alt_dir ? alt_esq : alt_dir);
// }

// int profundidade(struct No* raiz, struct No* alvo, int nivel) {
//     if (raiz == NULL) 
//         return -1;

//     if (raiz == alvo) 
//         return nivel;

//     int esq = profundidade(raiz->esquerda, alvo, nivel + 1);

//     if (esq != -1) 
//         return esq;

//     return profundidade(raiz->direita, alvo, nivel + 1);
// }

// int main() {
//     struct No* raiz = criarNo("A");

//     raiz->esquerda = criarNo("B");
//     raiz->direita = criarNo("C");

//     raiz->esquerda->esquerda = criarNo("D");
//     raiz->esquerda->direita = criarNo("E");

//     printf("Altura da árvore: %d\n", altura(raiz));

//     printf("Profundidade da raiz %s: %d\n", raiz->valor, profundidade(raiz, raiz, 0));

//     printf("Profundidade do nó %s: %d\n", 
//            raiz->esquerda->valor, 
//            profundidade(raiz, raiz->esquerda, 0));

//     printf("Profundidade do nó %s: %d\n", 
//            raiz->esquerda->esquerda->valor, 
//            profundidade(raiz, raiz->esquerda->esquerda, 0));

//     return 0;
// }

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Sala da mansão
typedef struct Sala {
    char nome[50];
    struct Sala *esquerda;
    struct Sala *direita;
} Sala;

Sala* criarSala(char nome[]) {
    Sala *novaSala = (Sala*) malloc(sizeof(Sala));

    if (novaSala == NULL) {
        printf("Sala vazia.\n");
        exit(1);
    }

    strcpy(novaSala->nome, nome);
    novaSala->esquerda = NULL;
    novaSala->direita = NULL;

    return novaSala;
}

// Explorar as salas
void explorarSalas(Sala *salaAtual) {
    char opcao;

    while (salaAtual != NULL) {
        printf("\nVoce esta na sala: %s\n", salaAtual->nome);
        if (salaAtual->esquerda == NULL && salaAtual->direita == NULL) {
            printf("Voce chegou a um comodo sem saida.\n");
            printf("Fim da exploracao.\n");
            break;
        }
        printf("\nCaminhos disponiveis:\n");
        if (salaAtual->esquerda != NULL) {
            printf("e - Ir para a esquerda\n");
        }
        if (salaAtual->direita != NULL) {
            printf("d - Ir para a direita\n");
        }
        printf("s - Sair da exploracao\n");
        printf("Escolha uma opcao: ");
        scanf(" %c", &opcao);

        if (opcao == 'e' || opcao == 'E') {
            if (salaAtual->esquerda != NULL) {
                salaAtual = salaAtual->esquerda;
            } else {
                printf("Nao existe caminho a esquerda.\n");
            }
        } 
        else if (opcao == 'd' || opcao == 'D') {
            if (salaAtual->direita != NULL) {
                salaAtual = salaAtual->direita;
            } else {
                printf("Nao existe caminho a direita.\n");
            }
        } 
        else if (opcao == 's' || opcao == 'S') {
            printf("Exploracao encerrada pelo jogador.\n");
            break;
        } 
        else {
            printf("Opcao invalida. Tente novamente.\n");
        }
    }
}


void liberarMemoria(Sala *sala) {
    if (sala == NULL) {
        return;
    }

    liberarMemoria(sala->esquerda);
    liberarMemoria(sala->direita);
    free(sala);
}

// Mapa da sala
int main() {
    Sala *hall = criarSala("Hall de Entrada");

    hall->esquerda = criarSala("Sala de Estar");
    hall->direita = criarSala("Corredor Principal");

    hall->esquerda->esquerda = criarSala("Biblioteca");
    hall->esquerda->direita = criarSala("Cozinha");

    hall->direita->esquerda = criarSala("Escritorio");
    hall->direita->direita = criarSala("Jardim");

    hall->esquerda->esquerda->esquerda = criarSala("Sala Secreta");
    hall->direita->direita->direita = criarSala("Deposito Antigo");

    printf("*********************************\n");
    printf("        DETECTIVE QUEST\n");
    
    printf("*********************************\n");
    printf("Explore a mansao e descubra seus caminhos.\n");

    explorarSalas(hall);

    liberarMemoria(hall);

    return 0;
}