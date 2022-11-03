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
cacheLine_t;

int main(int argc, char **argv)
{
	unsigned int globalTime = 0,
				 numFail = 0;

	cacheLine_t cache = {.etiqueta = 0xFF};
	for (int i=0; i<TAM_LINEA; i++) cache.datos[i] = (char) 0x23F;

	unsigned char simulRam[4096];

	return 0;
}
