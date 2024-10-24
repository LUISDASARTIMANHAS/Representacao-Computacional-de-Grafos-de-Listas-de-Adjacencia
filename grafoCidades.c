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
double inputDouble(){
    double value;
    scanf("%lf", &value);
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

//=================================================
// Função para inserir um vizinho a uma cidade existente
void inserirVizinho(TGrafo *grafo,char *nomeCidade, char *nomeVizinho, double distancia) {
    TVizinho *novoVizinho = (TVizinho *) malloc(sizeof(TVizinho));
    TCidade *cidadeVizinha = buscarCidade(grafo, nomeCidade);

    if (cidadeVizinha == NULL) {
        printf("\n Cidade Vizinha '%s' não encontrada!\n", nomeVizinho);
        return;
    }

    strcpy(novoVizinho->nome, nomeVizinho);
    novoVizinho->distancia = distancia;
    novoVizinho->prox = cidadeVizinha->vizinhos;
    cidadeVizinha->vizinhos = novoVizinho;

    printf("\n Vizinho %s Inserida!",nomeVizinho);
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
void removerCidade(TGrafo *grafo, char *nomeCidade) {
    int indice = -1;
    int i;
    // Encontra o índice da cidade a ser removida
    for (i = 0; i < grafo->numCidades; i++) {
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
    for (i = 0; i < grafo->numCidades; i++) {
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
    for (i = indice; i < grafo->numCidades - 1; i++) {
        grafo->cidades[i] = grafo->cidades[i + 1];
    }

    grafo->numCidades--;
    printf("Cidade '%s' removida com sucesso e removida da lista de vizinhos de outras cidades!\n", nomeCidade);
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

// Função para inserir uma cidade e seus vizinhos no grafo
void inserir(TGrafo *grafo, string nomeCidade, string nomeVizinho, double distancia) {
inserirCidade(grafo, nomeCidade);
inserirVizinho(grafo,nomeCidade, nomeVizinho, distancia);
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
double validarPeso(){
    double value;
    printf("\n Digite a Distancia entre as cidades: ");
    value = inputDouble();
    return value;
}
void validarCidade(char *destino){
    printf("\n Digite a Cidade: ");
    inputS(destino);
}
void validarVizinho(TGrafo *grafo,string nomeCidade, char *destino){
    TCidade *cidade = buscarCidade(grafo, nomeCidade);

    if (cidade == NULL) {
        printf("Cidade '%s' não encontrada!\n", nomeCidade);
        return;
    }
    printf("\n Digite o Vizinho: ");
    inputS(destino);
}

void cadastrarCidade(TGrafo *grafo){
    string nomeCidade;
    validarCidade(nomeCidade);
    inserirCidade(grafo, nomeCidade);
}
void cadastrarVizinho(TGrafo *grafo){
    string nomeCidade, nomeVizinho;
    double distancia;

    validarCidade(nomeCidade);
    validarVizinho(grafo,nomeCidade, nomeVizinho);
    distancia = validarPeso();
    inserirVizinho(grafo,nomeCidade,nomeVizinho,distancia);
    inserirVizinho(grafo,nomeVizinho,nomeCidade,distancia);
}
void deletarCidade(TGrafo *grafo){
    string nomeCidade;
    validarCidade(nomeCidade);
    removerCidade(grafo,nomeCidade);
}

void exibirCidadeEVizinho(TGrafo *grafo){
    string nomeCidade;
    validarCidade(nomeCidade);
    exibirCidade(grafo,nomeCidade);
}

void autosave(TGrafo grafo){

}
//=================================================
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
        printf("Insira uma opcao: ");
        opc = input();

            switch (opc){
            case 1:
                cadastrarCidade(grafo);
                break;
            case 2:
                cadastrarVizinho(grafo);
                break;
            case 3:
                deletarCidade(grafo);
                break;
            case 4:
                exibirCidadeEVizinho(grafo);
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
    autosave(grafo);
    exit(0);
}
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
// Função principal (main)
int main() {
    TGrafo grafo;
    mapeandoGrafo(&grafo);
    return 0;
}
