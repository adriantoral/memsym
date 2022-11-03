/* Author : Adrian Toral */
/* Codigo : Simulador de memoria cache */
/* Fecha  : 31-10-2022 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_FILAS 4
#define TAM_LINEA 8
#define MAX_LINEA 100
#define LRAM 1024

typedef struct
{
	unsigned char etiqueta;
	unsigned char datos[TAM_LINEA];
}
cacheLinea_t;

void limpiaCache(cacheLinea_t tbl[NUM_FILAS])
{
}

void vuelcaCache(cacheLinea_t *tbl)
{
}

void parseaAddr(unsigned int addr, int *etiqueta, int *palabra, int *linea, int *bloque)
{
}

void trataFallo(cacheLinea_t *tbl, char *memoriaRam, int etiqueta, int linea, int bloque)
{
}

int main(int argc, char **argv)
{
	return 0;
}
