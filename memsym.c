/* Author : Adrian Toral */
/* Author : Miguel Gracia */
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
	unsigned char ETQ;
	unsigned char Data[TAM_LINEA];
}
T_CACHE_LINE;

void LimpiarCACHE(T_CACHE_LINE tbl[NUM_FILAS])
{
	/* Funcion que limpia la memoria cache, es decir, inicializa los valores de la cache a default */
	/* - Etiqueta: 0xFF */
	/* - Datos:0x23F */

	for (int i=0; i<NUM_FILAS; i++) // Inicializacion de la memoria cache
	{
		tbl[i].ETQ = 0xFF; // Todas las etiquetas a 0xFF

		for (int j=0; j<TAM_LINEA; j++)
			tbl[i].Data[j] = (char) 0x23F; // Todos los datos de las lineas de la memoria cache a 0x23F
	}
}

void VolcarCACHE(T_CACHE_LINE *tbl)
{
}

void ParsearDireccion(unsigned int addr, int *ETQ, int *palabra, int *linea, int *bloque)
{
}

void TratarFallo(T_CACHE_LINE *tbl, char *MRAM, int ETQ, int linea, int bloque)
{
}

int main(int argc, char **argv)
{
	// Inicializacion de variables
	int globalTime = 0,
		numeroFallos = 0;

	T_CACHE_LINE memoriaCache[16]; // Memoria cache

	char memoriaRAM[4096], // Memoria RAM
		 direccion[3]; // Direccion de memoria en hexadecimal

	// Gestion memoria cache
	LimpiarCACHE(memoriaCache);

	// Gestion memoria 
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

