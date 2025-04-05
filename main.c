#include <stdio.h>								// Para imprimir (printf y perror)
#include <stdlib.h>								// Para utilizar memoria dinámica (malloc y free)
#include <string.h>								// Para comparar Strings fácilmente (strcmp)

#include "structs.h"							// Contiene la estructura de datos order
#include "archivo/cargar_ordenes.h"				// Contiene la funcionalidad de leer la cantidad de órdenes en el archivo y completar las estructuras de datos de tipo order con los datos del archivo
#include "metricas/atributo_mayor_menor.h"		// Contiene las funciones para las métricas de categoría Atributo Mayor o Menor: pms (Pizza más vendida), pls (Pizza menos vendida) e ims (Ingrediente más vendido)
#include "metricas/fecha_mayor_menor.h"			// Contiene las funciones para las métricas de categoría Fecha con Mayor o Menor: dms (Fecha con más ventas en términos de dinero), dls (Fecha con menos ventas en términos de dinero), dmsp (Fecha con más ventas en términos de cantidad de pizzas) y dlsp (Fecha con menos ventas en términos de cantidad de pizzas)
#include "metricas/estadisticas_cantidades.h"	// Contiene las funciones para las métricas de categoría Estadísticas y Cantidades: apo (Promedio de pizzas por orden), apd (Promedio de pizzas por día) y hp (Cantidad de pizzas por categoría vendidas)


#define INDICE_PARAMETRO_ARCHIVO 1				// Índice del parámetro que indica el nombre del archivo de datos a leer
#define PARAMETROS_ANTES_DE_METRICAS 2			// Cantidad de parámetros que deben haber antes de ingresar parámetros asociados a métricas
#define LARGO_METRICAS 10						// Largo de la lista metricas, es decir, la cantidad de métricas/funciones que el programa reconoce
#define MAX_ORDENES 1000						// Cantidad máxima de órdenes a guardar [SE PODRÍA ELIMINAR CON UNA FUNCIÓN PREVIA QUE REGRESA LA CANTIDAD DE ÓRDENES SIN RELLENAR LAS ESTRUCTURAS]



// Define el tipo de variable que es el puntero a una de las funciones de las métricas
typedef char* (*PunteroFuncion)(int*, order*);

// Define el tipo de variable que contiene el puntero a la función de su métrica correspondiente, junto con los Strings que se asocian a esa métrica
typedef struct
{
	const int largo_comandos;
	const char *comandos[2];
	const PunteroFuncion funcion_metrica;
} Metrica;


int main(int argc, char *argv[])
{
	// Lista de estructuras de tipo Metrica, es decir, inicializa todas las opciones que reconocerá el programa
	const Metrica metricas[LARGO_METRICAS] =
	{
		{2, {"pms", "pizza_mas_vendida"}, pizza_mas_vendida},
		{2, {"pls", "pizza_menos_vendida"}, pizza_menos_vendida},
		{2, {"dms", "encontrar_fecha_mas_vendida"}, encontrar_fecha_mas_vendida},
		{2, {"dls", "encontrar_fecha_menos_vendida"}, encontrar_fecha_menos_vendida},
		{2, {"dmsp", "encontrar_fecha_mas_ingresos"}, encontrar_fecha_mas_ingresos},
		{2, {"dlsp", "encontrar_fecha_menos_ingresos"}, encontrar_fecha_menos_ingresos},
		{2, {"apo", "encontrar_promedio_pizzas_orden"}, encontrar_promedio_pizzas_orden},
		{2, {"apd", "encontrar_promedio_pizzas_dia"}, encontrar_promedio_pizzas_dia},
		{2, {"ims", "ingrediente_mas_vendido"}, ingrediente_mas_vendido},
		{2, {"hp", "ventas_categoria"}, ventas_categoria}
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


	// Obtiene la cantidad de órdenes en el archivo CSV entregado
	int cantidad_ordenes = obtener_cantidad_ordenes(argv[INDICE_PARAMETRO_ARCHIVO]);
	
	// Asigna memoria dinámica para almacenar las estructuras de las órdenes, con un check para avisar si no se puede asignar todo el espacio necesario
	order *ordenes = malloc(cantidad_ordenes * sizeof(order));
	if (!ordenes)
	{
		perror("ERROR al asignar memoria");
		return 1;
	}

	// Carga los datos del archivo CSV entregado en las estructuras
	cargar_ordenes(argv[INDICE_PARAMETRO_ARCHIVO], ordenes);


	// De manera general: itera por cada parámetro, métrica, y comando reconocido para encontrar la métrica correcta asociada al parámetro ingresado
	// Específicamente: itera por cada parámetro desde el primero que debe considerarse asociado a una métrica
	for (int arg_i = PARAMETROS_ANTES_DE_METRICAS; arg_i < argc; arg_i++)
	{
		// Variable que guarda si el parámetro ingresado fue asociado a una métrica o no
		int metrica_encontrada = 0;

		// Itera por cada estructura de tipo Metrica
		for (int metrica_i = 0; metrica_i < LARGO_METRICAS; metrica_i++)
		{
			// Itera por cada comando reconocido en la estructura Metrica y los compara con el parámetro ingresado
			// Si coinciden, ejecuta la función asociada en el puntero dentro de la estructura Metrica en la que se encuentre la coincidencia, e imprime el resultado
			for (int comando_i = 0; comando_i < metricas[metrica_i].largo_comandos; comando_i++)
			{
				if (strcmp(argv[arg_i], metricas[metrica_i].comandos[comando_i]) == 0)
				{
					metrica_encontrada = 1;
					printf("- %s\n", metricas[metrica_i].funcion_metrica(&cantidad_ordenes, ordenes));
				}
			}
		}

		// Si el parámetro ingresado no fue asociado a ninguna métrica, imprime un mensaje para notificarlo y sugerir ver los argumentos que sí se reconocen
		if (!metrica_encontrada)
		{
			printf("! El argumento ingresado: '%s' no se encuentra asociado a ninguna metrica, ejecuta el programa sin argumentos para ver los argumentos reconocidos.\n", argv[arg_i]);
		}
	}


	// Se libera la memoria dinámica usada en almacenar las órdenes
	free(ordenes);


	return 0;
}