// Feito por: Lucas Garcia E Luis Augusto
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

typedef char string[101];

// Funções que serão implementadas no arquivo .c
FILE *abrirArquivo(char *nomeArq, char *modo);
int freadINT (FILE *arquivo);
void freadSTRING (FILE *arquivo, char valdestino[]);
float freadFloat (FILE *arquivo);
double freadDouble (FILE *arquivo);
float input();
double inputDouble();
long long int inputDLLD();
int inputBoleano();
void inputS(char destino[]);