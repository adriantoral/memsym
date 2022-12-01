/* Author : Adrian Toral */
/* Author : Miguel Gracia */
/* Codigo : Simulador de memoria cache */
/* Fecha  : 31-10-2022 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define NUM_FILAS 8
#define TAM_LINEA 16
#define TAM_RESULTADO 100
#define TAM_CACHE 256
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
	/* - Datos: 0x23F */

	for (int i=0; i<NUM_FILAS; i++) // Inicializacion de la memoria cache
	{
		tbl[i].ETQ = 0xFF; // Todas las etiquetas a 0xFF

		for (int j=0; j<TAM_LINEA; j++)
			tbl[i].Data[j] = 0x23; // Todos los datos de las lineas de la memoria cache a 0x23F
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

	printf("\n");
}

void ParsearDireccion(unsigned int addr, int *ETQ, int *palabra, int *linea, int *bloque)
{
	/* Funcion que convierte los bits de la addr a ETQ, palabra, linea, bloque */
	/* ETQ: 5 primeros bits de la addr */
	/* palabra: 4 ultimos bits de la addr */
	/* linea: 3 bits despues de la ETQ de la addr */
	/* bloque: 8 primeros bits de la addr (ETQ + linea) */

	*ETQ = (addr & 0b111110000000) >> 7;
	*palabra = (addr & 0b000000001111);
	*linea = (addr & 0b1110000) >> 4;
	*bloque = (addr & 0b111111110000) >> 4;
}

void TratarFallo(T_CACHE_LINE *tbl, unsigned char *MRAM, int ETQ, int linea, int bloque)
{
	/* Funcion que carga los datos de la MRAM */

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
	int globalTime = 0, // Tiempo total
		numeroFallos = 0, // Numero de fallos de la cache
		numeroAccesos = 0, // Numero de accesos de la cache
		numeroResultado = 0; // Contador de los resultados

	int addr = 0, // Direccion de memoria
		ETQ = 0, // Etiqueta de la cache
		linea = 0, // Linea de la cache
		palabra = 0, // Palabra de la cache
		bloque = 0; // Bloque de la cache (ETQ + linea)

	unsigned char memoriaRAM[TAM_RAM], // Memoria RAM
				  contenidoCache[TAM_CACHE], // Contenido cache
				  resultado[TAM_RESULTADO]; // Contenido valores resultantes

	T_CACHE_LINE memoriaCache[NUM_FILAS]; // Memoria cache

	// Gestion memoria cache
	LimpiarCACHE(memoriaCache);

	// Gestion memoria y direcciones de memoria
	FILE *contentsRam = fopen("CONTENTS_RAM.bin", "rb"); // Fichero temporal del .bin
	FILE *contentsDir = fopen("accesos_memoria.txt", "r"); // Fichero temporal del .txt

	if (!contentsRam || !contentsDir) // Comprueba si existen los ficheros
	{
		printf(!contentsRam && !contentsDir ? "No existen los ficheros\n" : !contentsRam ? "No existe el fichero CONTENTS_RAM.bin\n" : "No existe el fichero accesos_memoria.txt\n");
		return -1;
	}

	// Lectura de los contenidos
	fread(memoriaRAM, TAM_RAM, 1, contentsRam); // Guardar el .bin en memoria RAM (4096 caracteres)

	while (fscanf(contentsDir, "%x", &addr) != EOF) // Guardar la primera linea del .txt en direccion (numero hexadecimal)
	{
		ParsearDireccion(addr, &ETQ, &palabra, &linea, &bloque);
		globalTime++;

		// Comparamos las etiquetas
		if (ETQ != memoriaCache[linea].ETQ)
		{
			printf("T: %d Fallo cache: %d => ADDR: %04X ETQ: %X Linea: %02X Palabra: %02X Bloque: %02X\n", globalTime, ++numeroFallos, addr, ETQ, linea, palabra, bloque);
			globalTime += 10;

			TratarFallo(memoriaCache, memoriaRAM, ETQ, linea, bloque);
		}

		numeroAccesos++;
		printf("T: %d Acierto cache => ADDR: %04X ETQ: %X Linea: %02X Palabra: %02X Datos: %02X\n", globalTime, addr, ETQ, linea, palabra, memoriaCache[linea].Data[15 - palabra]);

		resultado[numeroResultado++] = memoriaCache[linea].Data[15 - palabra];

		VolcarCACHE(memoriaCache);

		sleep(1);
	}

	resultado[numeroResultado] = '\0';

	printf("Accesos totales: %d ; Fallos totales: %d ; Tiempo medio: %lf\nTexto leido: %s\n", numeroAccesos, numeroFallos, (double) globalTime / numeroAccesos, resultado);

	// Cerrar punteros de ficheros
	fclose(contentsRam); // Cerrar el .bin
	fclose(contentsDir); // Cerrar el .txt

	return 0;
}



