#include "fileSys.h"
//=================================================
// Função para abrir um arquivo no modo especificado
FILE *abrirArquivo(char *nomeArq, char *modo) {
    FILE *arquivo = fopen(nomeArq, modo);
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s\n", nomeArq);
        exit(1);
    }
    printf("\n INFO: Arquivo %s Aberto! Bom uso.\n", nomeArq);
    return arquivo;
}

    // fprintf(arquivo, "\n%3d %-50s %5d %10.2f", cod, nome, qtde, preco  );

/**
 * @brief // Escreve valores inteiros no arquivo
 */
void fWiriteINT (FILE *arquivo, int value){
    fprintf(arquivo, "%d\n", value);
}
/**
 * @brief // Escreve valores string no arquivo
 */
void fWiriteSTRING (FILE *arquivo, char value[]){
    fprintf(arquivo, "%s\n", value);
}
/**
 * @brief // Escreve valores string no arquivo
 */
void fWiriteFLOAT (FILE *arquivo, float value){
    fprintf(arquivo, "%f\n", value);
}
/**
 * @brief // Escreve valores string no arquivo
 */
void fWiriteDOUBLE (FILE *arquivo, double value){
    fprintf(arquivo, "%lf\n", value);
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
void freadSTRING (FILE *arquivo, char destino[]){
    fscanf(arquivo, " %99[^\n]s" , destino);
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
int inputBoleano(){
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