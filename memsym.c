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

#define NUM_FILAS 8
#define TAM_LINEA 16
#define TAM_CADENA 100
#define TAM_RAM 4096
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
	/* Funcion que muestra por pantalla los datos guardados en la memoria cache */

	for (int i=0; i<NUM_FILAS; i++)
	{
		printf("ETQ: %02X   Data ",tbl[i].ETQ);
		for (int j=0; j<TAM_LINEA; j++) printf("%02X ",tbl[i].Data[j]);
		printf("\n");
	}
}

void ParsearDireccion(unsigned int addr, int *ETQ, int *palabra, int *linea, int *bloque)
{
	*ETQ = (addr & 0b111110000000) >> 7;
	*palabra = (addr & 0b000000001111);
	*linea = (addr & 0b1110000) >> 4;
	*bloque = (addr & 0b111111110000) >> 4;
}

void TratarFallo(T_CACHE_LINE *tbl, char *MRAM, int ETQ, int linea, int bloque)
{
	int posicionInicial = bloque * TAM_LINEA,
		posicionFinal = posicionInicial - 1 + TAM_LINEA;

	printf("Cargando bloque %02X en la linea %02X\n", bloque, linea);

	tbl[linea].ETQ = (unsigned char) ETQ;
	for (int i=posicionFinal, j=0; i>=posicionInicial; i--)
		tbl[linea].Data[j++] = (unsigned char) MRAM[i];
}

int main(int argc, char **argv)
{
	// Inicializacion de variables
	int globalTime = 0,
		numeroFallos = 0,
		direccion = 0; // Direccion de memoria en hexadecimal

	char memoriaRAM[TAM_RAM]; // Memoria RAM

	T_CACHE_LINE memoriaCache[NUM_FILAS]; // Memoria cache

	// Gestion memoria cache
	LimpiarCACHE(memoriaCache);

	// Gestion memoria y direcciones de memoria
	FILE *contentsRam = fopen("CONTENTS_RAM.bin", "rb"); // Fichero temporal del .bin
	FILE *contentsDir = fopen("accesos_memoria.txt", "r"); // Fichero temporal del .txt

	if (!contentsRam || !contentsDir) // Comprueba si existen los ficheros
	{
		printf(!contentsRam ? "No existe el fichero CONTENTS_RAM.bin\n" : "No existe el fichero accesos_memoria.txt\n");
		return -1;
	}

	// Lectura de los contenidos
	fread(memoriaRAM, TAM_RAM, 1, contentsRam); // Guardar el .bin en memoria RAM (4096 caracteres)
	fscanf(contentsDir, "%x", &direccion); // Guardar la primera linea del .txt en direccion (numero hexadecimal)

	// Mostrar contenido de la RAM y direccion
	printf("%s\n%x\n", memoriaRAM, direccion);

	// Cerrar punteros de ficheros
	fclose(contentsRam); // Cerrar el .bin
	fclose(contentsDir); // Cerrar el .txt

	return 0;
}

