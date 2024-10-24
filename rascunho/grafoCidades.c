#include "grafoCidades.h"
//========================================================
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
//========================================================
// Função para inicializar o grafo
void inicializarGrafo(TGrafo *grafo, int capacidade) {
    grafo->cidades = (TCidade*) malloc(capacidade * sizeof(TCidade));
    grafo->numCidades = 0;
    grafo->capacidade = capacidade;
}
//========================================================
// Função para inserir uma cidade no grafo
void inserirCidade(TGrafo *grafo, string nomeCidade) {
    TCidade *guardaCidades = (TCidade *) realloc(grafo->cidades, grafo->capacidade * sizeof(TCidade));

    if (buscarCidade(grafo, nomeCidade) != NULL) {
        return;
    }

    if (grafo->numCidades == grafo->capacidade) {
        grafo->capacidade *= 2;
        grafo->cidades = guardaCidades;
    }

    strcpy(grafo->cidades[grafo->numCidades].nome, nomeCidade);
    grafo->cidades[grafo->numCidades].vizinhos = NULL;
    grafo->numCidades++;
}
//========================================================
// Função para inserir um vizinho a uma cidade existente
void inserirVizinho(TCidade *cidade, char *nomeVizinho, double distancia) {
    TVizinho *novoVizinho = (TVizinho *) malloc(sizeof(TVizinho));
    strcpy(novoVizinho->nome, nomeVizinho);
    novoVizinho->distancia = distancia;
    novoVizinho->prox = cidade->vizinhos;
    cidade->vizinhos = novoVizinho;
}
//========================================================
// Função para inserir uma cidade e seus vizinhos no grafo
void inserir(TGrafo *grafo, string nomeCidade, string nomeVizinho, double distancia) {
    inserirCidade(grafo, nomeCidade);
    TCidade *cidade = buscarCidade(grafo, nomeCidade);
    inserirVizinho(cidade, nomeVizinho, distancia);
}
//========================================================
// Função para buscar uma cidade pelo nome
TCidade * buscarCidade(TGrafo *grafo, string nomeCidade) {
    for (int i = 0; i < grafo->numCidades; i++) {
        if (strcmp(grafo->cidades[i].nome, nomeCidade) == 0) {
            return &grafo->cidades[i];
        }
    }
    return NULL;
}
//========================================================
// Função para exibir todas as cidades e seus vizinhos
void exibirGrafo(TGrafo *grafo) {
    for (int i = 0; i < grafo->numCidades; i++) {
        printf("Cidade: %s\n", grafo->cidades[i].nome);
        TVizinho *vizinho = grafo->cidades[i].vizinhos;
        while (vizinho != NULL) {
            printf("  Vizinho: %s, Distância: %.2f\n", vizinho->nome, vizinho->distancia);
            vizinho = vizinho->prox;
        }
    }
}
//========================================================
// Função para destruir o grafo e liberar a memória
void destruirGrafo(TGrafo *grafo) {
    for (int i = 0; i < grafo->numCidades; i++) {
        TVizinho *vizinho = grafo->cidades[i].vizinhos;
        while (vizinho != NULL) {
            TVizinho *temp = vizinho;
            vizinho = vizinho->prox;
            free(temp);
        }
    }
    free(grafo->cidades);
}
//========================================================
// Função para ler o arquivo e popular o grafo
void lerArquivo(TGrafo *grafo, FILE *arquivo) {
    char nomeCidade[101], nomeVizinho[101];
    double distancia;
    while (!feof(arquivo)) {
        if (fscanf(arquivo, " %100[^\n]\n", nomeCidade) == 1) {
            while (fscanf(arquivo, " %100[^\n]\n", nomeVizinho) == 1) {
                if (strcmp(nomeVizinho, ":") == 0) {
                    break;
                }
                if (fscanf(arquivo, "%lf\n", &distancia) == 1) {
                    inserir(grafo, nomeCidade, nomeVizinho, distancia);
                }
            }
        }
    }
}
//========================================================
// Função para remover uma cidade do grafo
// Função para remover uma cidade do grafo e removê-la como vizinha de outras cidades
void removerCidade(TGrafo *grafo, char *nomeCidade) {
    int indice = -1;
    
    // Encontra o índice da cidade a ser removida
    for (int i = 0; i < grafo->numCidades; i++) {
        if (strcmp(grafo->cidades[i].nome, nomeCidade) == 0) {
            indice = i;
            break;
        }
    }

    if (indice == -1) {
        printf("Cidade '%s' não encontrada!\n", nomeCidade);
        return;
    }

    // Remove todos os vizinhos da cidade a ser excluída
    TVizinho *vizinho = grafo->cidades[indice].vizinhos;
    while (vizinho != NULL) {
        TVizinho *temp = vizinho;
        vizinho = vizinho->prox;
        free(temp);
    }

    // Remover a cidade como vizinha de outras cidades
    for (int i = 0; i < grafo->numCidades; i++) {
        if (i != indice) {  // Não é necessário atualizar a cidade que está sendo removida
            TVizinho *atual = grafo->cidades[i].vizinhos;
            TVizinho *anterior = NULL;
            while (atual != NULL) {
                if (strcmp(atual->nome, nomeCidade) == 0) {
                    // Remover o vizinho
                    if (anterior == NULL) { // Primeiro da lista de vizinhos
                        grafo->cidades[i].vizinhos = atual->prox;
                    } else {
                        anterior->prox = atual->prox;
                    }
                    free(atual);
                    break;  // Como os nomes de vizinhos são únicos, saímos após encontrar
                }
                anterior = atual;
                atual = atual->prox;
            }
        }
    }

    // Remove a cidade do vetor
    for (int i = indice; i < grafo->numCidades - 1; i++) {
        grafo->cidades[i] = grafo->cidades[i + 1];
    }

    grafo->numCidades--;
    printf("Cidade '%s' removida com sucesso e removida da lista de vizinhos de outras cidades!\n", nomeCidade);
}


// Função para exibir uma cidade específica e seus vizinhos
void exibirCidade(TGrafo *grafo, char *nomeCidade) {
    TCidade *cidade = buscarCidade(grafo, nomeCidade);

    if (cidade == NULL) {
        printf("Cidade '%s' não encontrada!\n", nomeCidade);
        return;
    }

    printf("Cidade: %s\n", cidade->nome);
    TVizinho *vizinho = cidade->vizinhos;
    if (vizinho == NULL) {
        printf("  Não possui vizinhos cadastrados.\n");
    } else {
        while (vizinho != NULL) {
            printf("  Vizinho: %s, Distância: %.2f\n", vizinho->nome, vizinho->distancia);
            vizinho = vizinho->prox;
        }
    }
}

// Função para salvar o grafo em um arquivo
void salvarGrafo(TGrafo *grafo, char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s para escrita!\n", nomeArquivo);
        return;
    }

    for (int i = 0; i < grafo->numCidades; i++) {
        // Escreve o nome da cidade
        fprintf(arquivo, "%s\n", grafo->cidades[i].nome);

        // Percorre todos os vizinhos da cidade
        TVizinho *vizinho = grafo->cidades[i].vizinhos;
        while (vizinho != NULL) {
            // Escreve o nome do vizinho e a distância
            fprintf(arquivo, "%s\n%.2f\n", vizinho->nome, vizinho->distancia);
            vizinho = vizinho->prox;
        }

        // Escreve o delimitador de final de bloco ":"
        fprintf(arquivo, ":\n");
    }

    fclose(arquivo);
    printf("Grafo salvo com sucesso no arquivo %s!\n", nomeArquivo);
}

//========================================================
// Menu CRUD para o grafo
void menu(TGrafo *grafo) {
    int opcao;
    char nomeCidade[101], nomeVizinho[101];
    double distancia;

    do {
        printf("\n----- Menu de Operações -----\n");
        printf("1. Inserir Cidade\n");
        printf("2. Inserir Vizinho em Cidade\n");
        printf("3. Exibir Grafo\n");
        printf("4. Remover Cidade\n");
        printf("5. Exibir Cidade Específica\n");
        printf("6. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // Limpar o buffer do newline

        switch (opcao) {
            case 1:
                printf("Digite o nome da cidade a ser inserida: ");
                fgets(nomeCidade, 100, stdin);
                nomeCidade[strcspn(nomeCidade, "\n")] = '\0'; // Remove o newline
                inserirCidade(grafo, nomeCidade);
                break;

            case 2:
                printf("Digite o nome da cidade que terá um vizinho: ");
                fgets(nomeCidade, 100, stdin);
                nomeCidade[strcspn(nomeCidade, "\n")] = '\0';

                if (buscarCidade(grafo, nomeCidade) == NULL) {
                    printf("Cidade '%s' não encontrada!\n", nomeCidade);
                    break;
                }

                printf("Digite o nome do vizinho: ");
                fgets(nomeVizinho, 100, stdin);
                nomeVizinho[strcspn(nomeVizinho, "\n")] = '\0';

                printf("Digite a distância para o vizinho: ");
                scanf("%lf", &distancia);
                getchar(); // Limpar o buffer

                inserir(grafo, nomeCidade, nomeVizinho, distancia);
                printf("Vizinho '%s' com distância %.2f adicionado à cidade '%s'.\n", nomeVizinho, distancia, nomeCidade);
                break;

            case 3:
                exibirGrafo(grafo);
                break;

            case 4:
                printf("Digite o nome da cidade a ser removida: ");
                fgets(nomeCidade, 100, stdin);
                nomeCidade[strcspn(nomeCidade, "\n")] = '\0';
                removerCidade(grafo, nomeCidade);
                break;

            case 5:
                printf("Digite o nome da cidade para exibir seus detalhes: ");
                fgets(nomeCidade, 100, stdin);
                nomeCidade[strcspn(nomeCidade, "\n")] = '\0';
                exibirCidade(grafo, nomeCidade);
                break;

            case 6:
                printf("Saindo...\n");
                salvarGrafo(grafo, "cidades.txt");
                destruirGrafo(grafo);
                break;

            default:
                printf("Opção inválida! Tente novamente.\n");
                break;
        }
    } while (opcao != 6);
}
//========================================================
int main() {
    TGrafo grafo;
    inicializarGrafo(&grafo, 20); 

    FILE *arquivo = abrirArquivo("../data/cidades.txt", "r");

    lerArquivo(&grafo,arquivo);
    
    // Executa o menu CRUD
    menu(&grafo);

    return 0;
}