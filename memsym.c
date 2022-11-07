/* Author : Adrian Toral */
/* Codigo : Simulador de memoria cache */
/* Fecha  : 31-10-2022 */

/*

   El tamano maximo de la memoria principal es de 4096 [2^12 (Bus de memoria)] Bytes
   El tamano del bloque y el de linea es de 8 Bytes
   16 Bytes por linea ?

*/

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

void limpiaCache(cacheLinea_t *memoriaCache, int tamano)
{
	/* Funcion que limpia la memoria cache, es decir, inicializa los valores de la cache a default */
	/* - Etiqueta: 0xFF */
	/* - Datos:0x23F */

	for (int i=0; i<tamano; i++) // Inicializacion de la memoria cache
	{
		memoriaCache[i].etiqueta = 0xFF; // Todas las etiquetas a 0xFF

		for (int j=0; j<TAM_LINEA; j++)
			memoriaCache[i].datos[j] = (char) 0x23F; // Todos los datos de las lineas de la memoria cache a 0x23F
	}
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
	// Inicializacion de variables
	int globalTime = 0,
		numeroFallos = 0;

	cacheLinea_t memoriaCache[16]; // Memoria cache

	char memoriaRAM[4096], // Memoria RAM
		 direccion[3]; // Direccion de memoria en hexadecimal

	// Gestion memoria cache
	limpiaCache(memoriaCache, 16);

	// Gestion memoria RAM
	FILE *contentsRam = fopen("CONTENTS_RAM.bin", "r"); // Fichero temporal del .bin
	fgets(memoriaRAM, 4096, contentsRam); // Guardar el .bin en memoria RAM (solo los 4096 caracteres de la primera linea)

	// Gestion direcciones de memoria
	FILE *contentsDir = fopen("accesos_memoria.txt", "r"); // Fichero temporal del .txt
	fgets(direccion, 3, contentsDir); // Guardad la primera linea del .txt en direccion (2 caracteres)

	// Mostrar contenido de la RAM
	printf("%s\n", memoriaRAM);

	// Cerrar punteros de ficheros
	fclose(contentsRam); // Cerrar el .bin
	fclose(contentsDir); // Cerrar el .txt

	return 0;
}

