#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char origem[50];
    char destino[50];
    char tipoCarga[50];
} Container;

typedef struct node {
    char identificador[50];
    Container containers[100];
    int numContainers;
    struct node* next;
} NavioNode;

NavioNode* navios = NULL;

Container porto[100];
int numContainers = 0;

void adicionarContainer(int id, const char* origem, const char* destino, const char* tipoCarga) {
    if (numContainers < 100) {
        Container novoContainer;
        novoContainer.id = id;
        strcpy(novoContainer.origem, origem);
        strcpy(novoContainer.destino, destino);
        strcpy(novoContainer.tipoCarga, tipoCarga);

        porto[numContainers] = novoContainer;
        numContainers++;
        printf("Contêiner adicionado com sucesso.\n");
    } else {
        printf("O limite máximo de contêineres foi atingido.\n");
    }
}

void listarContainers() {
    printf("ID\tOrigem\t\tDestino\t\tTipo de Carga\n");
    for (int i = 0; i < numContainers; i++) {
        Container container = porto[i];
        printf("%d\t%s\t\t%s\t\t%s\n", container.id, container.origem, container.destino, container.tipoCarga);
    }
}

void chegadaTerrestre() {
    int id;
    char origem[50];
    char destino[50];
    char tipoCarga[50];

    printf("Digite o ID do contêiner: ");
    scanf("%d", &id);

    printf("Digite a origem: ");
    scanf("%s", origem);

    printf("Digite o destino: ");
    scanf("%s", destino);

    printf("Digite o tipo de carga: ");
    scanf("%s", tipoCarga);

    adicionarContainer(id, origem, destino, tipoCarga);
}

void chegadaMaritima() {
    char identificador[50];
    int numContainers;

    printf("Digite o identificador do navio: ");
    scanf("%s", identificador);

    printf("Digite o número de containers que o navio está transportando: ");
    scanf("%d", &numContainers);

    NavioNode* novoNavio = (NavioNode*)malloc(sizeof(NavioNode));
    strcpy(novoNavio->identificador, identificador);
    novoNavio->numContainers = numContainers;

    printf("Digite os detalhes dos containers:\n");
    for (int i = 0; i < numContainers; i++) {
        int id;
        char origem[50];
        char destino[50];
        char tipoCarga[50];

        printf("Container %d:\n", i + 1);

        printf("Digite o ID do contêiner: ");
        scanf("%d", &id);

        printf("Digite a origem: ");
        scanf("%s", origem);

        printf("Digite o destino: ");
        scanf("%s", destino);

        printf("Digite o tipo de carga: ");
        scanf("%s", tipoCarga);

        Container novoContainer;
        novoContainer.id = id;
        strcpy(novoContainer.origem, origem);
        strcpy(novoContainer.destino, destino);
        strcpy(novoContainer.tipoCarga, tipoCarga);

        novoNavio->containers[i] = novoContainer;
    }

    novoNavio->next = NULL;

    if (navios == NULL) {
        navios = novoNavio;
    } else {
        NavioNode* temp = navios;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = novoNavio;
    }

    printf("Navio adicionado com sucesso.\n");
}

void processarNavio() {
    if (navios == NULL) {
        printf("Não há navios na fila para processar.\n");
        return;
    }

    NavioNode* navioProcessado = navios;
    navios = navios->next;

    printf("Navio processado:\n");
    printf("Identificador: %s\n", navioProcessado->identificador);
    printf("Número de containers: %d\n", navioProcessado->numContainers);
    printf("Containers:\n");
    for (int i = 0; i < navioProcessado->numContainers; i++) {
        Container container = navioProcessado->containers[i];
        printf("ID: %d\tOrigem: %s\tDestino: %s\tTipo de Carga: %s\n", container.id, container.origem, container.destino, container.tipoCarga);
    }

    free(navioProcessado);
}

void exibirMenu() {
    int opcao;
    do {
        printf("\n");
        printf("=== Sistema Portuário ===\n");
        printf("1. Registrar chegada de contêiner por via terrestre\n");
        printf("2. Registrar chegada de contêiner por via marítima\n");
        printf("3. Listar contêineres presentes no porto\n");
        printf("4. Processar próximo navio\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                chegadaTerrestre();
                break;
            case 2:
                chegadaMaritima();
                break;
            case 3:
                listarContainers();
                break;
            case 4:
                processarNavio();
                break;
            case 0:
                printf("Saindo do programa.\n");
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (opcao != 0);
}

int main() {
    exibirMenu();
    return 0;
}
