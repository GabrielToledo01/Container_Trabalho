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
    Container container;
    struct node* next;
} ContainerNode;

typedef struct {
    char identificador[50];
    ContainerNode* containers;
} Navio;

typedef struct queue {
    Navio navio;
    struct queue* next;
} QueueNode;

ContainerNode* porto = NULL;
QueueNode* filaNavios = NULL;

void adicionarContainer(int id, const char* origem, const char* destino, const char* tipoCarga) {
    ContainerNode* novoContainer = (ContainerNode*)malloc(sizeof(ContainerNode));
    novoContainer->container.id = id;
    strcpy(novoContainer->container.origem, origem);
    strcpy(novoContainer->container.destino, destino);
    strcpy(novoContainer->container.tipoCarga, tipoCarga);
    novoContainer->next = NULL;

    if (porto == NULL) {
        porto = novoContainer;
    } else {
        ContainerNode* temp = porto;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = novoContainer;
    }

    printf("Contêiner adicionado com sucesso.\n");
}

void listarContainers() {
    printf("ID\tOrigem\t\tDestino\t\tTipo de Carga\n");
    ContainerNode* temp = porto;
    while (temp != NULL) {
        Container container = temp->container;
        printf("%d\t%s\t\t%s\t\t%s\n", container.id, container.origem, container.destino, container.tipoCarga);
        temp = temp->next;
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

    Navio novoNavio;
    strcpy(novoNavio.identificador, identificador);
    novoNavio.containers = NULL;

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

        ContainerNode* novoContainer = (ContainerNode*)malloc(sizeof(ContainerNode));
        novoContainer->container.id = id;
        strcpy(novoContainer->container.origem, origem);
        strcpy(novoContainer->container.destino, destino);
        strcpy(novoContainer->container.tipoCarga, tipoCarga);
        novoContainer->next = NULL;

        if (novoNavio.containers == NULL) {
            novoNavio.containers = novoContainer;
        } else {
            ContainerNode* temp = novoNavio.containers;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = novoContainer;
        }
    }

    QueueNode* novoNavioNode = (QueueNode*)malloc(sizeof(QueueNode));
    novoNavioNode->navio = novoNavio;
    novoNavioNode->next = NULL;

    if (filaNavios == NULL) {
        filaNavios = novoNavioNode;
    } else {
        QueueNode* temp = filaNavios;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = novoNavioNode;
    }

    printf("Navio adicionado com sucesso.\n");
}

void processarNavio() {
    if (filaNavios == NULL) {
        printf("Não há navios na fila para processar.\n");
        return;
    }

    QueueNode* navioProcessado = filaNavios;
    filaNavios = filaNavios->next;

    printf("Navio processado:\n");
    printf("Identificador: %s\n", navioProcessado->navio.identificador);
    printf("Número de containers: ");
    int numContainers = 0;
    ContainerNode* temp = navioProcessado->navio.containers;
    while (temp != NULL) {
        numContainers++;
        temp = temp->next;
    }
    printf("%d\n", numContainers);
    printf("Containers:\n");
    temp = navioProcessado->navio.containers;
    while (temp != NULL) {
        Container container = temp->container;
        printf("ID: %d\tOrigem: %s\tDestino: %s\tTipo de Carga: %s\n", container.id, container.origem, container.destino, container.tipoCarga);
        ContainerNode* next = temp->next;
        free(temp);
        temp = next;
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
//versão teste
