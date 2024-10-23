#include "grafoCidades.h"

//=================================================
// Função para abrir um arquivo no modo especificado
FILE *abrirArquivo(char *nomeArq, char *modo) {
    FILE *arquivo = fopen(nomeArq, modo);
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s\n", nomeArq);
        exit(1);
    }
    printf("INFO: Arquivo %s Aberto! Bom uso.\n", nomeArq);
    return arquivo;
}


/**
 * @brief // input para captar int do arquivo
 */
int freadINT (FILE *arquivo){
    int value;
    fscanf(arquivo, "%d" , &value);
    return value;
}

/**
 * @brief // string para captar  do arquivo
 */
void freadSTRING (FILE *arquivo, string *value){
    fscanf(arquivo, " %99[^\n]s" , &value);
}

/**
 * @brief // input para float Double do arquivo
 */
float freadFloat (FILE *arquivo){
    float value;
    fscanf(arquivo, "%f" , &value);
    return value;
}

/**
 * @brief // input para captar Double do arquivo
 */
double freadDouble (FILE *arquivo){
    double value;
    fscanf(arquivo, "%lf" , &value);
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

// void lerCidadesEVizinhos(TGrafo *grafo,FILE *arquivo){
//     int cont = 0;
//     string cidade, vizinho;
//     double distancia;
//     string frase;

//     while (! feof(arquivo)){
//      while(strcmp(nome,":") != 0 &&!feof(arquivo)){
//             freadSTRING(arquivo,&nome);
//             freadSTRING(arquivo,&vizinho);
//             distancia = freadDouble(arquivo);
//             if(strcmp(vizinho,":") != 0){
//                 inserir(grafo->cidades->vizinhos,nome,vizinho,distancia);  
//             }
            
//         }
    
//     cont++;
//     }
    
// }

void inserir(TVizinho *vizinhos, char * nome, char* vizinho, double peso){
    printf("\nCidade mae: %s, cidade vizinha: %s, peso: %lf", nome, vizinho, peso);
}

//=================================================
void inserirDadosDoArquivo(TGrafo *grafo, FILE *arquivo) {
    double distancia;
    string nome;
    string vizinho;
    while(!feof(arquivo)){
        while(strcmp(nome,":") != 0 &&!feof(arquivo)){
            fscanf(arquivo,"%[^\n]s",nome);
            fscanf(arquivo,"\n%[^\n]s",vizinho);
            fscanf(arquivo,"%ls",&distancia);
            if(strcmp(vizinho,":") != 0){
                inserir(grafo->cidades->vizinhos,nome,vizinho,distancia);  
            }
            
        }
    }
}
//=================================================

//=================================================
void mapeandoGrafo(TGrafo *grafo){
    inicializarGrafo(grafo, 5);  // Inicializa com uma capacidade de 5 cidades

    // Abre o arquivo "cidades.txt"
    FILE *arquivo = abrirArquivo("../data/cidades.txt", "r");

    // Ler todas as cidades, vizinhos e distâncias
    inserirDadosDoArquivo(grafo,arquivo);

    // Fecha o arquivo
    fclose(arquivo);

    // // Exibe o grafo
    // exibirGrafo(grafo);

    // // Libera a memória
    // destruirGrafo(grafo);
}
//=================================================

//=================================================
// Função principal (main)
int main() {
    TGrafo grafo;
    mapeandoGrafo(&grafo);
    return 0;
}
