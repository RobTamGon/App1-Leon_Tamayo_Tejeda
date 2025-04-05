#include <stdio.h>								// Para imprimir (printf)
#include <string.h>								// Para comparar Strings fácilmente (strcmp)

#include "structs.h"							// Contiene la estructura de datos order
#include "archivo/leer_csv.h"					// Contiene la funcionalidad de leer el archivo de datos y completar las estructuras de datos de tipo order
#include "metricas/atributo_mayor_menor.h"		// Contiene las funciones para las métricas de categoría Atributo Mayor o Menor: pms (Pizza más vendida), pls (Pizza menos vendida) e ims (Ingrediente más vendido)


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


#define INDICE_PARAMETRO_ARCHIVO 1				// Índice del parámetro que indica el nombre del archivo de datos a leer
#define PARAMETROS_ANTES_DE_METRICAS 2			// Cantidad de parámetros que deben haber antes de ingresar parámetros asociados a métricas
#define LARGO_METRICAS 10						// Largo de la lista metricas, es decir, la cantidad de métricas/funciones que el programa reconoce
#define MAX_ORDENES 1000						// Cantidad máxima de órdenes a guardar [SE PODRÍA ELIMINAR CON UNA FUNCIÓN PREVIA QUE REGRESA LA CANTIDAD DE ÓRDENES SIN RELLENAR LAS ESTRUCTURAS]



int main(int argc, char *argv[])
{
	// Define el tipo de variable que es el puntero a una de las funciones de las métricas
	typedef char* (*PunteroFuncion)(int*, order*);

	// Define el tipo de variable que contiene el puntero a la función de su métrica correspondiente, junto con los Strings que se asocian a esa métrica
	typedef struct
	{
		const int largo_comandos;
		const char *comandos[2];
		const PunteroFuncion funcion_metrica;
	} Metrica;


	// Lista de estructuras de tipo Metrica, es decir, inicializa todas las opciones que reconocerá el programa
	const Metrica metricas[LARGO_METRICAS] =
	{
		{2, {"pms", "pizza_mas_vendida"}, pizza_mas_vendida},
		{2, {"pls", "pizza_menos_vendida"}, pizza_menos_vendida},
		{2, {"dms", "encontrar_fecha_mas_vendida"}, f3},
		{2, {"dls", "encontrar_fecha_menos_vendida"}, f4},
		{2, {"dmsp", "encontrar_fecha_mas_ingresos"}, f5},
		{2, {"dlsp", "encontrar_fecha_menos_ingresos"}, f6},
		{2, {"apo", "promedio_pizzas_por_orden"}, f7},
		{2, {"apd", "promedio_pizzas_por_dia"}, f8},
		{2, {"ims", "ingrediente_mas_vendido"}, ingrediente_mas_vendido},
		{2, {"hp", "cantidad_de_pizzas_por_categoria_vendidas"}, f10}
	};


	// Imprime ayuda si el programa no recibe suficientes parámetros
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


	// Lee el archivo ingresado como segundo parámetro en la línea de comando y guarda las estructuras de las órdenes creadas a partir de esa lectura
	order ordenes[MAX_ORDENES];
	int largo_ordenes = leer_csv(argv[INDICE_PARAMETRO_ARCHIVO], ordenes, MAX_ORDENES);


	// De manera general: itera por cada parámetro, métrica, y comando reconocido para encontrar la métrica correcta asociada al parámetro ingresado
	// Específicamente: itera por cada parámetro desde el primero que debe considerarse asociado a una métrica
	for (int arg_i = PARAMETROS_ANTES_DE_METRICAS; arg_i < argc; arg_i++)
	{
		// Itera por cada estructura de tipo Metrica
		for (int metrica_i = 0; metrica_i < LARGO_METRICAS; metrica_i++)
		{
			// Itera por cada comando reconocido en la estructura Metrica y los compara con el parámetro ingresado
			// Si coinciden, ejecuta la función asociada en el puntero dentro de la estructura Metrica en la que se encuentre la coincidencia, e imprime el resultado
			for (int comando_i = 0; comando_i < metricas[metrica_i].largo_comandos; comando_i++)
			{
				if (strcmp(argv[arg_i], metricas[metrica_i].comandos[comando_i]) == 0)
				{
					printf("- %s\n", metricas[metrica_i].funcion_metrica(&largo_ordenes, ordenes));
				}
			}
		}
	}


	return 0;
}