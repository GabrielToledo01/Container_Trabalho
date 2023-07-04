#ifndef FUNCTIONS_H
#define FUNCTIONS_H

// Função para adicionar um contêiner ao porto
void adicionarContainer(int id, const char* origem, const char* destino, const char* tipoCarga);

// Função para listar os contêineres presentes no porto
void listarContainers();

// Função para registrar a chegada de um contêiner por via terrestre
void chegadaTerrestre();

// Função para registrar a chegada de um contêiner por via marítima
void chegadaMaritima();

// Função para processar o próximo navio na fila
void processarNavio();

// Função para exibir o menu de opções
void exibirMenu();

#endif

