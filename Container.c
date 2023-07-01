#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Container {
    int id;
    int navioId;
    struct Container* next;
} Container;

typedef struct Navio {
    char nome[50];
    Container* containers;
    struct Navio* next;
} Navio;

typedef struct Porto {
    Navio* navios;
    Container* containers;
} Porto;

void adicionarContainer(Porto* porto, int id, int navioId) {
    Container* novoContainer = (Container*)malloc(sizeof(Container));
    novoContainer->id = id;
    novoContainer->navioId = navioId;
    novoContainer->next = NULL;

    if (porto->containers == NULL) {
        porto->containers = novoContainer;
    } else {
        Container* atual = porto->containers;
        while (atual->next != NULL) {
            atual = atual->next;
        }
        atual->next = novoContainer;
    }
}

void adicionarNavio(Porto* porto, const char* nome) {
    Navio* novoNavio = (Navio*)malloc(sizeof(Navio));
    strcpy(novoNavio->nome, nome);
    novoNavio->containers = NULL;
    novoNavio->next = NULL;

    if (porto->navios == NULL) {
        porto->navios = novoNavio;
    } else {
        Navio* atual = porto->navios;
        while (atual->next != NULL) {
            atual = atual->next;
        }
        atual->next = novoNavio;
    }
}

void processarNavio(Porto* porto) {
    if (porto->navios == NULL) {
        printf("Nenhum navio na fila de processamento.\n");
        return;
    }

    Navio* navioProcessado = porto->navios;
    porto->navios = navioProcessado->next;

    printf("Navio processado: %s\n", navioProcessado->nome);

    Container* containerAtual = navioProcessado->containers;
    while (containerAtual != NULL) {
        Container* containerRemovido = containerAtual;
        containerAtual = containerAtual->next;
        free(containerRemovido);
    }

    free(navioProcessado);
}

void exibirPorto(Porto* porto) {
    printf("Navios na fila de processamento:\n");
    Navio* navioAtual = porto->navios;
    while (navioAtual != NULL) {
        printf("- %s\n", navioAtual->nome);
        navioAtual = navioAtual->next;
    }

    printf("\nContainers disponíveis no porto:\n");
    Container* containerAtual = porto->containers;
    while (containerAtual != NULL) {
        printf("- Container %d (Navio: %d)\n", containerAtual->id, containerAtual->navioId);
        containerAtual = containerAtual->next;
    }
}

int main() {
    Porto porto;
    porto.navios = NULL;
    porto.containers = NULL;

    adicionarNavio(&porto, "Navio1");
    adicionarContainer(&porto, 7, 1);
    adicionarContainer(&porto, 8, 1);
    adicionarContainer(&porto, 9, 1);
    adicionarContainer(&porto, 10, 1);

    adicionarNavio(&porto, "Navio2");
    adicionarContainer(&porto, 2, 2);

    exibirPorto(&porto);

    printf("\nProcessando navio...\n\n");
    processarNavio(&porto);

    printf("\nPorto após processamento:\n");
    exibirPorto(&porto);

    return 0;
}
