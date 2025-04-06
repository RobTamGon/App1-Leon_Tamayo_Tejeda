#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../structs.h"


// Define la estructura para almacenar la cantidad de pizzas por categoría
typedef struct
{
	char nombre[50];
	float cantidad;
} Categoria;


// Encuentra el promedio de pizzas por orden
char* promedio_pizzas_orden(int *size, order *orders)
{
	float suma_pizzas = 0;      // Suma de pizzas por orden
	int cantidad_ordenes = 0;   // Cantidad de órdenes diferentes

	// Asume que como máximo hay 'size' órdenes diferentes
	int *id_ordenes = malloc((*size) * sizeof(int));   // Reserva espacio de sobra
	
	// Check al asignar memoria
	if (!id_ordenes)
	{
		perror("ERROR al asignar memoria.");
		return "ERROR en promedio_pizzas_orden";
	}

	// Cuenta la cantidad de órdenes diferentes y suma las pizzas por orden
	for (int i = 0; i < *size; i++)
	{
		int ya_contada = 0;                             // Indica si ya se ha encontrado la orden

		for (int j = 0; j < cantidad_ordenes; j++)
		{
			if (id_ordenes[j] == orders[i].order_id)
			{
				ya_contada = 1;                         // Si coincide, la marca como ya encontrada
				break;
			}
		}

		// Si no ha encontrado la orden, la añade a la lista
		if (!ya_contada)
		{
			id_ordenes[cantidad_ordenes++] = orders[i].order_id;
		}

		suma_pizzas += orders[i].quantity; // Suma las pizzas por orden
	}

	// Calcula el promedio de pizzas por orden
	float promedio_orden = (cantidad_ordenes > 0) ? suma_pizzas / cantidad_ordenes : 0; // Evitando división por cero

	// Reserva memoria para el string de salida, con un check por si esta acción falla
	char *respuesta = malloc(100);

	if (!respuesta)
	{
		free(id_ordenes);
		perror("ERROR al asignar memoria.");
		return "ERROR en promedio_pizzas_orden";
	}

	// Convierte el promedio de pizzas a string con 2 decimales y añade a la respuesta
	char pizzas_promedio[20];
	sprintf(pizzas_promedio, "%.2f", promedio_orden);

	// Construye la respuesta
	strcpy(respuesta, "Promedio de pizzas por orden: ");
	strcat(respuesta, pizzas_promedio);

	// Liberar memoria usada para órdenes
	free(id_ordenes);

	return respuesta;
}


// Encuentra el promedio de pizzas por día
char* promedio_pizzas_dia(int *size, order *orders)
{
	float suma_pizzas = 0;			// Suma de pizzas por día
	int cantidad_dias = 0;			// Cantidad de días diferentes

	// Asume que como máximo hay 'largo' días diferentes
	char **dias = malloc((*size) * sizeof(int));

	// Check al asignar memoria
	if (!dias)
	{
		perror("ERROR al asignar memoria.");
		return "ERROR en promedio_pizzas_dia";
	}

	// Cuenta la cantidad de días diferentes y suma las pizzas por día
	for (int i = 0; i < *size; i++)
	{
		int ya_contado = 0;										// Indica si ya se ha encontrado el día

		for (int j = 0; j < cantidad_dias; j++) {
			if (strcmp(dias[j], orders[i].order_date) == 0)
			{ 
				ya_contado = 1;									// Si coincide, lo marca como ya encontrado
				break;
			}
		}

		// Si no ha encontrado el día, lo añade a la lista
		if (!ya_contado)
		{
			dias[cantidad_dias] = malloc(strlen(orders[i].order_date) + 1); // Reserva espacio

			if (!dias[cantidad_dias])
			{
				// Liberar memoria usada para fechas
				for (int k = 0; k < cantidad_dias; k++) free(dias[k]);

				free(dias);

				perror("ERROR al asignar memoria.");
				return "ERROR en promedio_pizzas_dia";
			}

			strcpy(dias[cantidad_dias], orders[i].order_date); // Copia el día
			cantidad_dias++;
		}

		suma_pizzas += orders[i].quantity; // Suma de pizzas por día
	}

	// Calcula el promedio de pizzas por día
	float promedio_dia = (cantidad_dias > 0) ? suma_pizzas / cantidad_dias : 0; // Evitando división por cero

	// Reserva memoria para el string de salida, con un check por si esta acción falla
	char *respuesta = malloc(100);

	if (!respuesta)
	{
		// Libera memoria usada para fechas
		for (int i = 0; i < cantidad_dias; i++) free(dias[i]);

		free(dias);

		perror("ERROR al asignar memoria.");
		return "ERROR en promedio_pizzas_dia";
	}

	// Convierte el promedio de pizzas a string con 2 decimales
	char pizzas_promedio[20];
	sprintf(pizzas_promedio, "%.2f", promedio_dia);

	// Construye la respuesta
	strcpy(respuesta, "Promedio de pizzas por dia: ");
	strcat(respuesta, pizzas_promedio);

	// Libera memoria usada para las fechas
	for (int i = 0; i < cantidad_dias; i++) free(dias[i]);

	free(dias);

	return respuesta;
}



// Encuentra la cantidad de pizzas por categoría vendidas
char* ventas_categoria(int *size, order *orders)
{
	Categoria *categorias = malloc((*size) * sizeof(Categoria)); // Reserva memoria para categorías, con check por si esta acción falla

	if (!categorias)
	{
		perror("ERROR al asignar memoria.");
		return "ERROR en ventas_categoria";
	}

	// Contador de categorías
	int total_categorias = 0;

	// Cuenta la cantidad de pizzas vendidas por categoría
	for (int i = 0; i < *size; i++)
	{
		int idx = -1;

		for (int j = 0; j < total_categorias; j++)
		{
			if (strcmp(categorias[j].nombre, orders[i].pizza_category) == 0)
			{ // Comprueba si la categoría coincide
				idx = j; // Si coincide, guarda el índice
				break;
			}
		}

		// Si no ha encontrado la categoría, la añade a la lista
		if (idx == -1)
		{
			strcpy(categorias[total_categorias].nombre, orders[i].pizza_category); // Copia la categoría
			categorias[total_categorias].cantidad = 0; // Inicializa la cantidad de pizzas
			idx = total_categorias; // Guarda el índice
			total_categorias++; // Aumenta el contador de categorías
		}

		// Suma la cantidad de pizzas
		categorias[idx].cantidad += orders[i].quantity;
	}

	// Reserva memoria para el string de salida
	char *respuesta = malloc(2048);

	if (!respuesta)
	{
		free(categorias);

		perror("ERROR al asignar memoria.");
		return "ERROR ventas_categoria";
	}

	// Construye la respuesta
	strcpy(respuesta, "Cantidad de pizzas vendidas por categoria: ");

	// Añade la lista de categorías y cantidades de pizzas
	int primera_categoria = 1;
	for (int i = 0; i < total_categorias; i++)
	{
		if (categorias[i].cantidad > 0)
		{
			if (!primera_categoria)
			{ // Añade una coma antes de añadir la siguiente categoría
				strcat(respuesta, ", ");
			}

			primera_categoria = 0; // Marca como no primera_categoría

			char cantidad[1000]; // Reserva espacio para la cantidad de pizzas y categorias
			sprintf(cantidad, "%s: %.2f pizzas", categorias[i].nombre, categorias[i].cantidad); // Convierte la cantidad a string
			strcat(respuesta, cantidad); // Añade la cantidad de pizzas a la respuesta
		}
	}

	free(categorias); // Liberar memoria usada para categorías

	return respuesta;
}