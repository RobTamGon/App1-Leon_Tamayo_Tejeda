#include <stdio.h>					// Para imprimir
#include <stdlib.h>					// Para usar memoria dinámica
#include <string.h>					// Para trabajar con texto

#include "../structs.h"				// Archivo donde está definida la estructura order

#define MAX_PIZZAS 1000				// Se establece un límite máximo de 1000 tipos de pizzas a procesar
#define MAX_INGREDIENTES 1000		// Se establece un límite máximo de 1000 ingredientes diferentes


// Define el tipo de variable que contiene un tipo de pizza y la cantidad de ventas que tuvo
typedef struct
{
	char nombre[128];
	float cantidad_total;
} PizzaVenta;


// Obtiene cuál(es) fue(ron) la(s) pizza(s) más vendida(s) y cuántas unidades de esta(s) se vendieron
char* pizza_mas_vendida(int *size, order *orders)
{
	// Inicializa la lista a contener los tipos de pizza que se encuentren en el archivo CSV entregado
	PizzaVenta resumen[MAX_PIZZAS];
	int total_pizzas = 0;

	// Itera por todas las órdenes
	for (int i = 0; i < *size; i++)
	{
		// Variable que guarda si la pizza actual había sido vista antes o no
		int encontrada = 0;

		// Recorre el resumen de pizzas hecho hasta ahora
		for (int j = 0; j < total_pizzas; j++)
		{
			// Si la pizza ya existía, suma la cantidad encontrada
			if (strcmp(orders[i].pizza_name, resumen[j].nombre) == 0)
			{
				resumen[j].cantidad_total += orders[i].quantity;
				encontrada = 1;
				break;
			}
		}

		// Si no encuentra la pizza, la añade como una nueva entrada en el resumen
		if (!encontrada)
		{
			strcpy(resumen[total_pizzas].nombre, orders[i].pizza_name);
			resumen[total_pizzas].cantidad_total = orders[i].quantity;
			total_pizzas++;
		}
	}

	// Con todas las pizzas registradas, busca la de mayor venta
	float mayor_venta = 0;
	for (int i = 0; i < total_pizzas; i++)
	{
		if (resumen[i].cantidad_total > mayor_venta)
		{
			mayor_venta = resumen[i].cantidad_total;
		}
	}

	// Si por alguna razón no hay ventas, imprime un mensaje que diga eso
	if (mayor_venta == 0)
	{
		return "ERROR: No se encontraron ventas válidas.";
	}

	// Crea el texto final a regresar, asignando memoria dinámica con un check por si esta acción falla
	char *respuesta = malloc(2048);

	if (!respuesta)
	{
		perror("ERROR al asignar memoria.");
		return "ERROR en pizza_mas_vendida.";
	}

	// Primera parte del mensaje
	strcpy(respuesta, "Pizza mas vendida: ");

	// En caso de empates, se itera por todas las pizzas en resumen y se añaden todas las que tengan la mayor cantidad de ventas
	int primera = 1;
	for (int i = 0; i < total_pizzas; i++)
	{
		if (resumen[i].cantidad_total == mayor_venta)
		{
			if (!primera)
			{
				strcat(respuesta, ", ");
			}

			primera = 0;
			strcat(respuesta, resumen[i].nombre);
		}
	}

	// Al final del texto se agrega la cantidad exacta de ventas
	char cantidad_texto[32];
	sprintf(cantidad_texto, " (%.1f unidades)", mayor_venta);
	strcat(respuesta, cantidad_texto);

	return respuesta;
}


// Obtiene cuál(es) fue(ron) la(s) pizza(s) menos vendida(s) y cuántas unidades de esta(s) se vendieron
char* pizza_menos_vendida(int *size, order *orders)
{
	// Inicializa la lista a contener los tipos de pizza que se encuentren en el archivo CSV entregado
	PizzaVenta resumen[MAX_PIZZAS];
	int total_pizzas = 0;

	// Itera por todas las órdenes
	for (int i = 0; i < *size; i++)
	{
		// Variable que guarda si la pizza actual había sido vista antes o no
		int encontrada = 0;

		// Recorre el resumen de pizzas hecho hasta ahora
		for (int j = 0; j < total_pizzas; j++)
		{
			// Si la pizza ya existía, suma la cantidad encontrada
			if (strcmp(orders[i].pizza_name, resumen[j].nombre) == 0)
			{
				resumen[j].cantidad_total += orders[i].quantity;
				encontrada = 1;
				break;
			}
		}

		// Si no encuentra la pizza, la añade como una nueva entrada en el resumen
		if (!encontrada)
		{
			strcpy(resumen[total_pizzas].nombre, orders[i].pizza_name);
			resumen[total_pizzas].cantidad_total = orders[i].quantity;
			total_pizzas++;
		}
	}

	// Si por alguna razón no hay ventas, imprime un mensaje que diga eso
	if (total_pizzas == 0)
	{
		return "ERROR: No se encontraron ventas válidas.";
	}

	// Con todas las pizzas registradas, busca la de menor venta
	float menor_venta = resumen[0].cantidad_total;
	for (int i = 1; i < total_pizzas; i++)
	{
		if (resumen[i].cantidad_total < menor_venta)
		{
			menor_venta = resumen[i].cantidad_total;
		}
	}

	// Crea el texto final a regresar, asignando memoria dinámica con un check por si esta acción falla
	char *respuesta = malloc(2048);

	if (!respuesta)
	{
		perror("ERROR al asignar memoria.");
		return "ERROR en pizza_menos_vendida.";
	}

	// Primera parte del mensaje
	strcpy(respuesta, "Pizza menos vendida: ");

	// En caso de empates, se itera por todas las pizzas en resumen y se añaden todas las que tengan la mayor cantidad de ventas
	int primera = 1;
	for (int i = 0; i < total_pizzas; i++)
	{
		if (resumen[i].cantidad_total == menor_venta)
		{
			if (!primera)
			{
				strcat(respuesta, ", ");
			}

			primera = 0;
			strcat(respuesta, resumen[i].nombre);
		}
	}

	// Al final del texto se agrega la cantidad exacta de ventas
	char cantidad_texto[32];
	sprintf(cantidad_texto, " (%.1f unidades)", menor_venta);
	strcat(respuesta, cantidad_texto);

	return respuesta;
}



// Obtiene cuál(es) fue(ron) el/los ingrediente(s) más vendido(s) y cuántas unidades de esto(s) se vendieron
char* ingrediente_mas_vendido(int *size, order *orders)
{
	// Define el tipo de variable que contiene un tipo de pizza y la cantidad de ventas que tuvo
	typedef struct
	{
		char nombre[64];
		float cantidad_total;
	} IngredienteVenta;

	IngredienteVenta resumen[MAX_INGREDIENTES];  // Aquí vamos guardando los ingredientes
	int total_ingredientes = 0;

	// Itera por todas las órdenes
	for (int i = 0; i < *size; i++)
	{
		// Crea una copia de valor de los ingredientes para no modificar el original
		char ingredientes[256];
		strcpy(ingredientes, orders[i].pizza_ingredients);

		// Separa los ingredientes uno por uno
		char *token = strtok(ingredientes, ",");
		while (token != NULL) {
			// Elimina espacios iniciales si es que hay
			while (*token == ' ') token++;

			int encontrado = 0;

			// Buscar si este ingrediente ya fue guardado antes
			for (int j = 0; j < total_ingredientes; j++)
			{
				if (strcmp(token, resumen[j].nombre) == 0)
				{
					resumen[j].cantidad_total += orders[i].quantity;
					encontrado = 1;
					break;
				}
			}

			// Si es un ingrediente nuevo, se agrega como una nueva entrada en resumen
			if (!encontrado)
			{
				strcpy(resumen[total_ingredientes].nombre, token);
				resumen[total_ingredientes].cantidad_total = orders[i].quantity;
				total_ingredientes++;
			}

			// Pasa al siguiente ingrediente
			token = strtok(NULL, ",");
		}
	}

	// Si por alguna razón no hay ingredientes, imprime un mensaje que diga eso
	if (total_ingredientes == 0)
	{
		return "ERROR: No se encontraron ingredientes válidos.";
	}

	// Con todos los ingredientes registrados, busca el que más se repita
	float mayor_venta = 0;
	for (int i = 0; i < total_ingredientes; i++)
	{
		if (resumen[i].cantidad_total > mayor_venta)
		{
			mayor_venta = resumen[i].cantidad_total;
		}
	}

	// Crea el texto final a regresar, asignando memoria dinámica con un check por si esta acción falla
	char *respuesta = malloc(2048);

	if (!respuesta)
	{
		perror("ERROR al asignar memoria.");
		return "ERROR en ingrediente_mas_vendido.";
	}

	// Primera parte del mensaje
	strcpy(respuesta, "Ingrediente mas vendido: ");

	// En caso de empates, se itera por todos los ingredientes en resumen y se añaden todos los que se repitan la mayor cantidad de veces
	int primera = 1;
	for (int i = 0; i < total_ingredientes; i++)
	{
		if (resumen[i].cantidad_total == mayor_venta)
		{
			if (!primera)
			{
				strcat(respuesta, ", ");
			}

			primera = 0;
			strcat(respuesta, resumen[i].nombre);
		}
	}

	// Al final del texto se agrega la cantidad exacta de repeticiones
	char cantidad_texto[32];
	sprintf(cantidad_texto, " (%.1f unidades)", mayor_venta);
	strcat(respuesta, cantidad_texto);

	return respuesta;
}