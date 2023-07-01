#include <stdio.h>
#include <stdlib.h>

typedef struct Navio {
    int id;
    int vazio;
    struct Container* containers;
    struct Navio* prox;
} Navio;

typedef struct Container {
    int id;
    int id_navio;
    struct Container* prox;
} Container;

typedef struct {
    Navio* navios;
    Container* containers_porto;
} Porto;

void inicializarPorto(Porto* porto) {
    porto->navios = NULL;
    porto->containers_porto = NULL;
}

void adicionarContainer(Porto* porto, int id_container, int id_navio) {
    Container* container = malloc(sizeof(Container));
    container->id = id_container;
    container->id_navio = id_navio;
    container->prox = NULL;

    if (porto->containers_porto == NULL) {
        porto->containers_porto = container;
    } else {
        Container* atual = porto->containers_porto;
        while (atual->prox != NULL) {
            atual = atual->prox;
        }
        atual->prox = container;
    }

    printf("Container %d adicionado ao porto.\n", id_container);
}

void adicionarNavio(Porto* porto, int id_navio) {
    Navio* navio = malloc(sizeof(Navio));
    navio->id = id_navio;
    navio->vazio = 1;
    navio->containers = NULL;
    navio->prox = NULL;

    if (porto->navios == NULL) {
        porto->navios = navio;
    } else {
        Navio* atual = porto->navios;
        while (atual->prox != NULL) {
            atual = atual->prox;
        }
        atual->prox = (struct Navio*)navio;
    }

    printf("Navio %d adicionado à fila de navios.\n", id_navio);
}

void processarNavio(Porto* porto) {
    if (porto->navios == NULL) {
        printf("Nenhum navio na fila.\n");
        return;
    }

    Navio* navio = porto->navios;

    if (navio->vazio) {
        printf("Navio %d carregado e removido da fila.\n", navio->id);
    } else {
        printf("Navio %d descarregado e removido da fila.\n", navio->id);
        Container* atual = porto->containers_porto;
        Container* anterior = NULL;
        while (atual != NULL) {
            if (atual->id_navio == navio->id) {
                printf("Container %d removido do porto.\n", atual->id);
                if (anterior == NULL) {
                    porto->containers_porto = atual->prox;
                } else {
                    anterior->prox = atual->prox;
                }
                free(atual);
                atual = anterior == NULL ? porto->containers_porto : anterior->prox;
            } else {
                anterior = atual;
                atual = atual->prox;
            }
        }
    }

    porto->navios = (struct Navio*)navio->prox;
    free(navio);
}

void limparPorto(Porto* porto) {
    Navio* atual_navio = porto->navios;
    while (atual_navio != NULL) {
        Navio* prox_navio = (struct Navio*)atual_navio->prox;
        free(atual_navio);
        atual_navio = prox_navio;
    }

    Container* atual_container = porto->containers_porto;
    while (atual_container != NULL) {
        Container* prox_container = atual_container->prox;
        free(atual_container);
        atual_container = prox_container;
    }
}

int main() {
    Porto porto;
    inicializarPorto(&porto);

    adicionarContainer(&porto, 7, 1);
    adicionarContainer(&porto, 8, 1);
    adicionarContainer(&porto, 9, 1);
    adicionarContainer(&porto, 10, 1);

    adicionarNavio(&porto, 1);
    adicionarNavio(&porto, 2);

    processarNavio(&porto);
    processarNavio(&porto);

    limparPorto(&porto);

    return 0;
}
