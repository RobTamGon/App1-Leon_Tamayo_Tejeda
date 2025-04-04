#include <stdio.h>
#include <string.h>

//ESTA PARTE ES TEMPORAL, SOLAMENTE PARA PROBAR
struct order
{
	int a;
};

char* f1(int *size, struct order *orders)
{
	return "f1 ";
}

char* f2(int *size, struct order *orders)
{
	return "f2 ";
}

char* f3(int *size, struct order *orders)
{
	return "f3 ";
}

char* f4(int *size, struct order *orders)
{
	return "f4 ";
}

char* f5(int *size, struct order *orders)
{
	return "f5 ";
}

char* f6(int *size, struct order *orders)
{
	return "f6 ";
}

char* f7(int *size, struct order *orders)
{
	return "f7 ";
}

char* f8(int *size, struct order *orders)
{
	return "f8 ";
}

char* f9(int *size, struct order *orders)
{
	return "f9 ";
}

char* f10(int *size, struct order *orders)
{
	return "f10 ";
}


#define LARGO_PARAMETROS 10


int main(int argc, char *argv[])
{
	// Definición del tipo de variable que es el puntero a una de las funciones de las métricas
	typedef char* (*PunteroFuncion)(int*, struct order*);


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


	// SECCIÓN PARA LEER Y PARAMETRIZAR LAS ÓRDENES
	int largo_ordenes = 20;
	struct order ordenes[largo_ordenes];


	// Parámetros que se reconocerán en la línea de comando
	char* parametros[LARGO_PARAMETROS] = {"pms", "pls", "dms", "dls", "dmsp", "dlsp", "apo", "apd", "ims", "hp"};

	// Lista de punteros a las funciones de las métricas, asociada implícitamente por el índice con la lista de parámetros anterior
	// (Ejemplo: "pms" en el índice 0 se asocia a f1, también en el índice 0)
	const PunteroFuncion punteros[LARGO_PARAMETROS] = {f1, f2, f3, f4, f5, f6, f7, f8, f9, f10};
	

	// Se itera por cada parámetro ingresado después del nombre del programa y del nombre del archivo a leer para comparar con los parámetros que se reconocen
	for (int arg_i = 2; arg_i < argc; arg_i++)
	{
		// Se itera por cada parámetro aceptado y se compara con el parámetro ingresado, si coinciden, se ejecuta la función asociada
		for (int i = 0; i < LARGO_PARAMETROS; i++)
		{
			if (strcmp(argv[arg_i], parametros[i]) == 0)
			{
				printf("%s", punteros[i](&largo_ordenes, ordenes));
			}
		}
	}


	return 0;
}