//Feito por: Lucas Garcia E Luis Augusto
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

typedef char string[101];
typedef clock_t processTime;

typedef struct tipoCidade{
    string nome;
    float pesoAresta;
}Cidade;

typedef struct tipoGrafo{
    Cidade *cidades;
}Grafo;