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
// Função auxiliar para separar as cidades e distâncias em uma linha
void processarLinhaDeCidades(TGrafo *grafo, char *linha) {
    char *token = strtok(linha, ",");  // Usa a vírgula como delimitador
    char cidadeAtual[101];
    strcpy(cidadeAtual, token);  // A primeira cidade é a cidade principal

    inserirCidade(grafo, cidadeAtual);  // Insere a cidade principal

    // Continua processando os vizinhos e distâncias
    while (token != NULL) {
        token = strtok(NULL, ",");  // Pega a próxima cidade vizinha ou distância
        if (token == NULL || strcmp(token, ":") == 0) {
            break;  // Se chegamos ao fim do bloco
        }

        char vizinhoAtual[101];
        strcpy(vizinhoAtual, token);  // Vizinho

        token = strtok(NULL, ",");  // Próximo token será a distância
        if (token != NULL && strcmp(token, ":") != 0) {
            float distancia = atof(token);  // Converte a string para float
            inserirVizinho(grafo, cidadeAtual, vizinhoAtual, distancia);  // Insere o vizinho com a distância
        }
    }
}
//=================================================
// 1ª etapa: Lê o arquivo e cria todas as cidades e seus vizinhos
void lerCidadesEVizinhos(TGrafo *grafo, FILE *arquivo) {
    char linha[1024];  // Buffer para leitura de linha (ajustado para o formato linear com vírgulas)

    while (fgets(linha, sizeof(linha), arquivo)) {
        linha[strcspn(linha, "\n")] = '\0';  // Remove o '\n' no final da linha
        if (strcmp(linha, ":") == 0 || strlen(linha) == 0) {
            continue;  // Pula linhas vazias ou com apenas ":"
        }

        processarLinhaDeCidades(grafo, linha);  // Processa a linha para criar as cidades e vizinhos
    }
}
//=================================================
// Exibe o grafo (as cidades e seus vizinhos)
void exibirGrafo(TGrafo *grafo) {
    for (int i = 0; i < grafo->numCidades; i++) {
        printf("Cidade: %s\n", grafo->cidades[i].nome);
        TVizinho *vizinho = grafo->cidades[i].vizinhos;
        while (vizinho != NULL) {
            printf("  -> Vizinho: %s, Distância: %.2f\n", vizinho->nome, vizinho->distancia);
            vizinho = vizinho->prox;
        }
        printf("%s\n", CORTE);
    }
}
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
