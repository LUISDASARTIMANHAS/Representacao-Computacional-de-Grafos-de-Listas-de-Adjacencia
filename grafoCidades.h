// Feito por: Lucas Garcia E Luis Augusto
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

#define INICIO "------------INICIO------------"
#define RESULTADO "------------RESULTADO------------"
#define CORTE "------------------------"
#define ARQUIVOCIDADES "../data/cidades.txt"

typedef char string[101];
typedef clock_t processTime;

// Estrutura que representa um vizinho de uma cidade
typedef struct tipoVizinho {
    string nome;                 // Nome da cidade vizinha
    double distancia;             // Distância (peso da aresta) entre as cidades
    struct tipoVizinho *prox;    // Ponteiro para o próximo vizinho (lista encadeada)
} TVizinho;

// Estrutura que representa uma cidade
typedef struct tipoCidade {
    string nome;                 // Nome da cidade
    TVizinho *vizinhos;          // Lista encadeada de vizinhos (cada um com a distância/peso)
} TCidade;

// Estrutura que representa o grafo como um todo
typedef struct tipoGrafo {
    TCidade *cidades;            // Vetor de cidades (vértices do grafo)
    int numCidades;              // Número total de cidades no grafo
    int capacidade;              // Capacidade máxima de cidades no grafo (inicialmente alocada)
} TGrafo;

// Funções que serão implementadas no arquivo .c
void inicializarGrafo(TGrafo *grafo, int capacidade);
void inserirCidade(TGrafo *grafo, string nomeCidade);
void inserirVizinho(TGrafo *grafo,string nomeCidade, char *nomeVizinho, double distancia);
void lerArquivo(TGrafo *grafo, FILE *arquivo);
TCidade* buscarCidade(TGrafo *grafo, string nomeCidade);
void exibirGrafo(TGrafo *grafo);
void removerCidade(TGrafo *grafo, char *nomeCidade);