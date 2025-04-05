#include <stdio.h>
#include <string.h>

#include "structs.h"
#include "archivo/leer_csv.h"
#include "metricas/atributo_mayor_menor.h"

//ESTA PARTE ES TEMPORAL, SOLAMENTE PARA PROBAR

char* f3(int *size, order *orders)
{
	return "f3";
}

char* f4(int *size, order *orders)
{
	return "f4";
}

char* f5(int *size, order *orders)
{
	return "f5";
}

char* f6(int *size, order *orders)
{
	return "f6";
}

char* f7(int *size, order *orders)
{
	return "f7";
}

char* f8(int *size, order *orders)
{
	return "f8";
}

char* f10(int *size, order *orders)
{
	return "f10";
}


#define MAX_ORDENES 1000
#define LARGO_PARAMETROS 10


int main(int argc, char *argv[])
{
	// Definición del tipo de variable que es el puntero a una de las funciones de las métricas
	typedef char* (*PunteroFuncion)(int*, order*);


	// Imprime ayuda si el programa no recibe suficientes argumentos
	if (argc <= 2) {
        printf("No se ingresaron suficientes argumentos, intente ingresar alguna(s) de las siguientes opciones disponibles:\n");
        printf("- pms:     Pizza mas vendida\n");
        printf("- pls:     Pizza menos vendida\n");
        printf("- dms:     Fecha con mas ventas en terminos de dinero (junto a la cantidad de dinero recaudado)\n");
        printf("- dls:     Fecha con menos ventas en terminos de dinero (junto a la cantidad de dinero recaudado)\n");
        printf("- dmsp:    Fecha con mas ventas en terminos de cantidad de pizzas (junto a la cantidad de pizzas)\n");
        printf("- dlsp:    Fecha con menos ventas en terminos de cantidad de pizzas (junto a la cantidad de pizzas)\n");
        printf("- apo:     Promedio de pizzas por orden\n");
        printf("- apd:     Promedio de pizzas por dia\n");
        printf("- ims:     Ingrediente mas vendido\n");
        printf("- hp:      Cantidad de pizzas por categoria vendidas\n\n");
		printf("Por ejemplo:\n./app1 ventas.csv pms pls dms dls dmsp dlsp apo apd ims hp\n\n");
        return 0;
    }


	// Se lee el archivo ingresado como segundo parámetro en la línea de comando y se guardan las estructuras de las órdenes creadas a partir de esa lectura
	order ordenes[MAX_ORDENES];
	int largo_ordenes = leer_csv(argv[1], ordenes, MAX_ORDENES);


	// Parámetros que se reconocerán en la línea de comando
	const char* parametros[LARGO_PARAMETROS] = {"pms", "pls", "dms", "dls", "dmsp", "dlsp", "apo", "apd", "ims", "hp"};

	// Lista de punteros a las funciones de las métricas, asociada implícitamente por el índice con la lista de parámetros anterior
	// (Ejemplo: "pms" en el índice 0 se asocia a pizza_mas_vendida, que también está en el índice 0)
	const PunteroFuncion punteros[LARGO_PARAMETROS] = {pizza_mas_vendida, pizza_menos_vendida, f3, f4, f5, f6, f7, f8, ingrediente_mas_vendido, f10};


	// Se itera por cada parámetro ingresado después del nombre del programa y del nombre del archivo a leer para comparar con los parámetros que se reconocen
	for (int arg_i = 2; arg_i < argc; arg_i++)
	{
		// Se itera por cada parámetro que se reconocerá y se compara con el parámetro ingresado, si coinciden, se ejecuta la función asociada
		for (int i = 0; i < LARGO_PARAMETROS; i++)
		{
			if (strcmp(argv[arg_i], parametros[i]) == 0)
			{
				printf("- %s\n", punteros[i](&largo_ordenes, ordenes));
			}
		}
	}


	return 0;
}