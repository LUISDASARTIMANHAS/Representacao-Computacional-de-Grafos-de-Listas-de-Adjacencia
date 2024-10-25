// Feito por: Lucas Garcia E Luis Augusto
#ifndef FILESYS_H
#define FILESYS_H
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

void fWiriteINT (FILE *arquivo, int value);
void fWiriteSTRING (FILE *arquivo, char value[]);
void fWiriteFLOAT (FILE *arquivo, float value);
void fWiriteDOUBLE (FILE *arquivo, double value);

float input();
double inputDouble();
long long int inputDLLD();
int inputBoleano();
void inputS(char destino[]);
#endif