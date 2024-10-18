#include "grafoCidades.h"

//=================================================
// Função para abrir um arquivo no modo especificado
FILE *abrirArquivo(char *nomeArq, char *modo) {
    FILE *arquivo = fopen(nomeArq, modo);
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s\n", nomeArq);
        exit(1);
    }
    return arquivo;
}

int freadINT (FILE *arquivo){
    int value;
    fscanf(arquivo, "%d" , &value);
    return value;
}
void freadSTRING (FILE *arquivo, string *value){
    fscanf(arquivo, " %99[^\n]s" , &value);
}
float freadINT (FILE *arquivo){
    float value;
    fscanf(arquivo, "%f" , &value);
    return value;
}
double freadINT (FILE *arquivo){
    double value;
    fscanf(arquivo, "%f" , &value);
    return value;
}

//=================================================
// Inicializa o grafo com uma capacidade inicial de cidades
void inicializarGrafo(TGrafo *grafo, int capacidade) {
    grafo->cidades = (TCidade*) malloc(capacidade * sizeof(TCidade));
    grafo->numCidades = 0;
    grafo->capacidade = capacidade;
}
//=================================================
// Insere uma cidade no grafo (adiciona um vértice)
void inserirCidade(TGrafo *grafo, string nomeCidade) {
    if (grafo->numCidades >= grafo->capacidade) {
        grafo->capacidade *= 2; // Dobra a capacidade se necessário
        grafo->cidades = realloc(grafo->cidades, grafo->capacidade * sizeof(TCidade));
    }

    strcpy(grafo->cidades[grafo->numCidades].nome, nomeCidade);
    grafo->cidades[grafo->numCidades].vizinhos = NULL; // Inicializa sem vizinhos
    grafo->numCidades++;
}
//=================================================
// Insere um vizinho em uma cidade
void inserirVizinho(TGrafo *grafo, string nomeCidade, string nomeVizinho, float distancia) {
    TCidade *cidade = buscarCidade(grafo, nomeCidade);
    if (cidade == NULL) return;

    // Cria um novo vizinho
    TVizinho *novoVizinho = (TVizinho*) malloc(sizeof(TVizinho));
    strcpy(novoVizinho->nome, nomeVizinho);
    novoVizinho->distancia = distancia;
    novoVizinho->prox = cidade->vizinhos; // Insere no início da lista
    cidade->vizinhos = novoVizinho;
}
//=================================================
// Busca uma cidade pelo nome
TCidade* buscarCidade(TGrafo *grafo, string nomeCidade) {
    for (int i = 0; i < grafo->numCidades; i++) {
        if (strcmp(grafo->cidades[i].nome, nomeCidade) == 0) {
            return &grafo->cidades[i];
        }
    }
    return NULL;
}
//=================================================
// Libera a memória alocada para o grafo
void destruirGrafo(TGrafo *grafo) {
    for (int i = 0; i < grafo->numCidades; i++) {
        // Libera a lista de vizinhos de cada cidade
        TVizinho *vizinho = grafo->cidades[i].vizinhos;
        while (vizinho != NULL) {
            TVizinho *temp = vizinho;
            vizinho = vizinho->prox;
            free(temp);
        }
    }

    // Libera o vetor de cidades
    free(grafo->cidades);
}
//=================================================

//=================================================

//=================================================

//=================================================
void mapeandoGrafo(TGrafo *grafo){
    inicializarGrafo(grafo, 5);  // Inicializa com uma capacidade de 5 cidades

    // Abre o arquivo "cidades.txt"
    FILE *arquivo = abrirArquivo("../data/cidades.txt", "r");

    // Ler todas as cidades, vizinhos e distâncias
    lerCidadesEVizinhos(grafo, arquivo);

    // Fecha o arquivo
    fclose(arquivo);

    // Exibe o grafo
    exibirGrafo(grafo);

    // Libera a memória
    destruirGrafo(grafo);
}
//=================================================

//=================================================
// Função principal (main)
int main() {
    TGrafo grafo;
    mapeandoGrafo(&grafo);
    return 0;
}
