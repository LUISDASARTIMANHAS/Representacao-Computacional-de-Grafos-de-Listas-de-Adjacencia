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

float input(){
    float value;
    scanf("%f", &value);
    return value;
}

/**
 * @brief // input para captar long long int do teclado do usuario
 */
long long int inputDLLD(){
    long long int value;
    scanf("%lld", &value);
    return value;
}

/**
 * @brief // input para captar Verdadeiro ou falso (Bloeano) do teclado do usuario
 */
float inputBoleano(){
	int value;
	do{
		fflush(stdin);
		scanf("%d", &value);
	}while(value != 1 && value != 0);
	return value;
}

/**
 * @brief // input para captar Strings do teclado do usuario
 */
void inputS(char destino[]){
    scanf(" %100[^\n]s", destino);
}

// Função para exibir todas as cidades e seus vizinhos
void exibirGrafo(TGrafo *grafo) {
    for (int i = 0; i < grafo->numCidades; i++) {
    printf("\nCidade: %s\n", grafo->cidades[i].nome);
    TVizinho *vizinho = grafo->cidades[i].vizinhos;
        while (vizinho != NULL) {
        printf(" Vizinho: %s, Distância: %.2f\n", vizinho->nome, vizinho->distancia);
        vizinho = vizinho->prox;
        }
    }
}

void menu(TGrafo *grafo){
    int opc = -1;
    while (opc != 0){
        printf("\n======= GRAFO DE CIDADES =======\n");
        printf("1 - Inserir Cidade\n");
        printf("2 - Inserir Vizinho\n");
        printf("3 - Remover Vizinho e Cidade \n");
        printf("4 - Imprimir Cidade e seu Vizinhos \n");
        printf("5 - Imprimir Todo o Grafo\n");
        printf("0 - Sair\n");
        printf("=====================\n");
        printf("Forma: ");
        opc = input();

            switch (opc){
            case 1:
                string nomeCidade;
                inputS(nomeCidade);
                inserirCidade(grafo, nomeCidade);
                break;
            case 2:
                /* code */
                break;
            case 3:
                /* code */
                break;
            case 4:
                /* code */
                break;
            case 5:
                exibirGrafo(grafo);
                break;
            default:
                printf("\n Opcao Invalida!");
                break;
            }
    }
    printf("\n Saindo e Salvando automaticamente...");
    exit(0);
}

//=================================================
// Inicializa o grafo com uma capacidade inicial de cidades
void inicializarGrafo(TGrafo *grafo, int capacidade) {
    grafo->cidades = (TCidade*) malloc(capacidade * sizeof(TCidade));
    grafo->numCidades = 0;
    grafo->capacidade = capacidade;
}
//=================================================
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

//=================================================
// Função para inserir um vizinho a uma cidade existente
void inserirVizinho(TCidade *cidade, char *nomeVizinho, double distancia) {
TVizinho *novoVizinho = (TVizinho *) malloc(sizeof(TVizinho));
strcpy(novoVizinho->nome, nomeVizinho);
novoVizinho->distancia = distancia;
novoVizinho->prox = cidade->vizinhos;
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

// Função para inserir uma cidade e seus vizinhos no grafo
void inserir(TGrafo *grafo, string nomeCidade, string nomeVizinho, double distancia) {
inserirCidade(grafo, nomeCidade);
TCidade *cidade = buscarCidade(grafo, nomeCidade);
inserirVizinho(cidade, nomeVizinho, distancia);
}

//=================================================
void inserirDadosDoArquivo(TGrafo *grafo, FILE *arquivo) {
    double distancia;
    string nomeCidade;
    string nomeVizinho;

    while(!feof(arquivo)){
        while(strcmp(nomeCidade,":") != 0 &&!feof(arquivo)){
            fscanf(arquivo,"%[^\n]s",nomeCidade);
            
            fscanf(arquivo,"\n%[^\n]s",nomeVizinho);
            fscanf(arquivo,"%lf",&distancia);
            if(strcmp(nomeVizinho,":") != 0){
                inserir(grafo,nomeCidade,nomeVizinho,distancia);
            }
            
        }
    }
}
//=================================================

//=================================================
void mapeandoGrafo(TGrafo *grafo){
    inicializarGrafo(grafo, 20);  // Inicializa com uma capacidade de 5 cidades

    // Abre o arquivo "cidades.txt"
    FILE *arquivo = abrirArquivo("../data/cidades.txt", "r");
    // Ler todas as cidades, vizinhos e distâncias
    inserirDadosDoArquivo(grafo,arquivo);
    

    // Fecha o arquivo
    fclose(arquivo);
    menu(grafo);

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
