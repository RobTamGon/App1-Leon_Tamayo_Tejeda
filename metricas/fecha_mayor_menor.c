#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../structs.h"

#define MAX_FECHAS 1000 // Se establece un límite máximo de 1000 fechas distintas


// Define la estructura para almacenar las ventas por fecha
typedef struct
{
	char fecha[20];
	float total_pizzas;
	float total_dinero;
} VentaFecha;


// Encuentra la fecha con más ventas en cantidad de pizzas
char* fecha_mas_vendida(int *size, order *orders)
{
	VentaFecha ventas_fecha[MAX_FECHAS] = {0}; // Inicializa la estructura de ventas por fecha
	int total_fechas = 0; // Contador de fechas

	// Recorre las ventas y almacena las ventas por fecha 
	for (int i = 0; i < *size; i++)
	{
		int idx = -1; // Inicializa el índice a -1 para indicar que no se ha encontrado la fecha

		for (int j = 0; j < total_fechas; j++) {
			if (strcmp(ventas_fecha[j].fecha, orders[i].order_date) == 0)
			{ // Si coincide, la guarda el índice
				idx = j; // Guarda el índice
				break;
			}
		}

		if (idx == -1)
		{ // Si no ha encontrado la fecha, la añade a la lista
			strcpy(ventas_fecha[total_fechas].fecha, orders[i].order_date); // Copia la fecha
			idx = total_fechas; // Guarda el índice
			total_fechas++; // Aumenta el contador de fechas
		}

		// Suma la cantidad de pizzas de la fecha
		ventas_fecha[idx].total_pizzas += orders[i].quantity;
	}

	// Encuentra la fecha con más ventas en cantidad de pizzas
	float max_ventas = 0; // Inicializa la cantidad máxima de pizzas a 0
	for (int i = 0; i < total_fechas; i++)
	{
		if (ventas_fecha[i].total_pizzas > max_ventas)
		{ // Si la cantidad de pizzas es mayor que la máxima, la actualiza
			max_ventas = ventas_fecha[i].total_pizzas; // Actualiza la cantidad máxima
		}
	}

	// Reserva memoria para la respuesta, con un check por si esta acción falla
	char *respuesta = malloc(2048);

	if (!respuesta)
	{
		perror("ERROR al asignar memoria.");
		return "ERROR en fecha_mas_vendida";
	}
	
	char pizzas_recaudado[20]; // Reserva espacio para la cantidad de pizzas
	sprintf(pizzas_recaudado, "%.2f", max_ventas); // Convierte el total de pizzas a string con 2 decimales

	strcpy(respuesta, "Fecha con mas ventas en terminos de cantidad de pizzas: ");  // Escribe la primera parte del mensaje

	// Añade todas las fechas que tienen la cantidad máxima de ventas
	int primera_fecha = 1; // Indica si es la primera fecha a añadir
	for (int i = 0; i < total_fechas; i++)
	{
		if (ventas_fecha[i].total_pizzas == max_ventas)
		{ // Si la cantidad de pizzas es igual a la máxima, la añade
			if (!primera_fecha)
			{
				strcat(respuesta, ", "); // Añade una coma antes de añadir la siguiente fecha
			}

			primera_fecha = 0; // Marca como no primera_fecha

			strcat(respuesta, ventas_fecha[i].fecha); // Añade la fecha
		}
	}

	strcat(respuesta, ". Cantidad de pizzas: ");  // Añade la tercera parte del mensaje
	strcat(respuesta, pizzas_recaudado);  // Añade el total de pizzas

	return respuesta;
}


// Encuentra la fecha con más ventas en dinero
char* fecha_mas_ingresos(int *size, order *orders)
{
	VentaFecha ventas_fecha[MAX_FECHAS] = {0}; // Inicializa la estructura de ventas por fecha
	int total_fechas = 0; // Contador de fechas

	// Recorre las ventas y almacena el total de dinero por fecha
	for (int i = 0; i < *size; i++)
	{
		int idx = -1; // Inicializa el índice a -1 para indicar que no se ha encontrado la fecha
		for (int j = 0; j < total_fechas; j++)
		{
			if (strcmp(ventas_fecha[j].fecha, orders[i].order_date) == 0)
			{ // Si coincide, guarda el índice
				idx = j; // Guarda el índice
				break;
			}
		}

		if (idx == -1)
		{ // Si no ha encontrado la fecha, la añade a la lista
			strcpy(ventas_fecha[total_fechas].fecha, orders[i].order_date); // Copia la fecha
			idx = total_fechas; // Guarda el índice
			total_fechas++; // Aumenta el contador de fechas
		}

		ventas_fecha[idx].total_dinero += orders[i].total_price; // Suma el total de dinero de la fecha
	}

	// Encuentra la fecha con más ingresos
	float max_ingresos = 0; // Inicializa la cantidad máxima de ingresos a 0
	for (int i = 0; i < total_fechas; i++)
	{
		if (ventas_fecha[i].total_dinero > max_ingresos)
		{ // Si la cantidad de ingresos es mayor que la máxima, la actualiza
			max_ingresos = ventas_fecha[i].total_dinero; // Actualiza la cantidad máxima
		}
	}

	// Reserva memoria para la respuesta, con un check por si esta acción falla
	char *respuesta = malloc(2048);

	if (!respuesta)
	{
		perror("ERROR al asignar memoria.");
		return "ERROR en fecha_mas_ingresos";
	}

	// Convierte el total de dinero a string con 2 decimales
	char dinero_recaudado[20]; // Reserva espacio para la cantidad de dinero
	sprintf(dinero_recaudado, "%.2f", max_ingresos); 

	strcpy(respuesta, "Fecha con mas ventas en terminos de dinero: ");  // Escribe la primera parte del mensaje

	// Añade todas las fechas que tienen la cantidad máxima de ingresos    
	int primera_fecha = 1; // Indica si es la primera fecha a añadir
	for (int i = 0; i < total_fechas; i++)
	{
		if (ventas_fecha[i].total_dinero == max_ingresos)
		{ // Si la cantidad de ingresos es igual a la máxima, la añade
			if (!primera_fecha)
			{
				strcat(respuesta, ", "); // Añade una coma antes de añadir la siguiente fecha
			}

			primera_fecha = 0; // Marca como no primera_fecha

			strcat(respuesta, ventas_fecha[i].fecha); // Añade la fecha
		}
	}

	strcat(respuesta, ". Cantidad de dinero recaudado: ");  // Añade la segunda parte del mensaje
	strcat(respuesta, dinero_recaudado);  // Añade el total de dinero

	return respuesta;
}


// Encuentra la fecha con menos ventas en cantidad de pizzas
char* fecha_menos_vendida(int *size, order *orders)
{
	VentaFecha ventas_fecha[MAX_FECHAS] = {0}; // Inicializa la estructura de ventas por fecha
	int total_fechas = 0; // Contador de fechas

	// Recorre las ventas y almacena las ventas por fecha
	for (int i = 0; i < *size; i++)
	{
		int idx = -1; // Inicializa el índice a -1 para indicar que no se ha encontrado la fecha
		for (int j = 0; j < total_fechas; j++)
		{
			if (strcmp(ventas_fecha[j].fecha, orders[i].order_date) == 0)
			{ // Si coincide, guarda el índice
				idx = j; // Guarda el índice
				break;
			}
		}

		if (idx == -1)
		{ // Si no se encontrado la fecha, lo añade a la lista
			strcpy(ventas_fecha[total_fechas].fecha, orders[i].order_date); // Copia la fecha
			idx = total_fechas; // Guarda el índice
			total_fechas++; // Aumenta el contador de fechas
		}

		ventas_fecha[idx].total_pizzas += orders[i].quantity; // Suma la cantidad de pizzas de la fecha
	}
	
	// Encuentra la fecha con menos ventas en cantidad de pizzas
	float min_ventas = ventas_fecha[0].total_pizzas; // Inicializa la cantidad mínima de pizzas a la primera fecha
	for (int i = 1; i < total_fechas; i++)
	{
		if (ventas_fecha[i].total_pizzas >= 0 && ventas_fecha[i].total_pizzas < min_ventas)
		{ // Si la cantidad de pizzas es menor que la mínima, la actualiza
			min_ventas = ventas_fecha[i].total_pizzas; // Actualiza la cantidad mínima
		}
	}

	// Reserva memoria para la respuesta, con un check por si esta acción falla
	char *respuesta = malloc(2048);

	if (!respuesta)
	{
		perror("ERROR al asignar memoria.");
		return "ERROR en fecha_menos_vendida";
	}

	// Convierte el total de dinero a string con 2 decimales
	char pizzas_recaudado[20]; // Reserva espacio para la cantidad de pizzas
	sprintf(pizzas_recaudado, "%.2f", min_ventas);

	strcpy(respuesta, "Fecha con menos ventas en terminos de cantidad de pizzas: ");  // Escribe la primera parte del mensaje

	// Añade todas las fechas que tienen la cantidad mínima de ventas
	int primera_fecha = 1; // Indica si es la primera fecha a añadir
	for (int i = 0; i < total_fechas; i++)
	{
		if (ventas_fecha[i].total_pizzas == min_ventas)
		{ // Si la cantidad de pizzas es igual a la mínima, la añade
			if (!primera_fecha)
			{
				strcat(respuesta, ", "); // Añade una coma antes de añadir la siguiente fecha
			}

			primera_fecha = 0; // Marca como no primera fecha

			strcat(respuesta, ventas_fecha[i].fecha); // Añade la fecha
		}
	}

	strcat(respuesta, ". Cantidad de pizzas: ");  // Añade la tercera parte del mensaje
	strcat(respuesta, pizzas_recaudado);  // Añade el total de pizzas

	return respuesta;
}


// Encuentra la fecha con menos ventas en dinero
char* fecha_menos_ingresos(int *size, order *orders)
{
	VentaFecha ventas_fecha[MAX_FECHAS] = {0}; // Inicializa la estructura de ventas por fecha
	int total_fechas = 0; // Contador de fechas

	// Recorre las ventas y almacena el total de dinero por fecha
	for (int i = 0; i < *size; i++)
	{
		int idx = -1; // Inicializa el índice a -1 para indicar que no se ha encontrado la fecha
		for (int j = 0; j < total_fechas; j++)
		{
			if (strcmp(ventas_fecha[j].fecha, orders[i].order_date) == 0)
			{ // Si coincide, la guarda el índice
				idx = j; // Guarda el índice
				break;
			}
		}

		if (idx == -1)
		{ // Si no se encontrado la fecha, la añade a la lista
			strcpy(ventas_fecha[total_fechas].fecha, orders[i].order_date); // Copia la fecha
			idx = total_fechas; // Guarda el índice
			total_fechas++; // Aumenta el contador de fechas
		}

		ventas_fecha[idx].total_dinero += orders[i].total_price; // Suma el total de dinero de la fecha
	}

	// Encuentra la fecha con menos ingresos
	float min_ingresos = ventas_fecha[0].total_dinero; // Inicializa la cantidad mínima de ingresos a la primera fecha
	for (int i = 1; i < total_fechas; i++)
	{
		if (ventas_fecha[i].total_dinero >= 0 && ventas_fecha[i].total_dinero < min_ingresos)
		{ // Si la cantidad de ingresos es menor que la mínima, la actualiza
			min_ingresos = ventas_fecha[i].total_dinero; // Actualiza la cantidad mínima
		}
	}

	// Reservamos memoria para la respuesta, con un check por si la acción falla
	char *respuesta = malloc(2048);

	if (!respuesta)
	{
		perror("ERROR al asignar memoria.");
		return "ERROR en fecha_menos_ingresos";
	}
	
	// Convierte el total de dinero a string con 2 decimales
	char dinero_recaudado[20];  // Reserva espacio para la cantidad de dinero
	sprintf(dinero_recaudado, "%.2f", min_ingresos);

	strcpy(respuesta, "Fecha con menos ventas en terminos de dinero: ");  // Escribe la primera parte del mensaje

	// Añadir todas las fechas que tienen la cantidad mínima de ingresos
	int primera_fecha = 1;
	for (int i = 0; i < total_fechas; i++)
	{
		if (ventas_fecha[i].total_dinero == min_ingresos)
		{ // Si la cantidad de ingresos es igual a la mínima, la añade
			if (!primera_fecha)
			{
				strcat(respuesta, ", "); // Añade una coma antes de añadir la siguiente fecha
			}

			primera_fecha = 0;  // Marca como no primera fecha

			strcat(respuesta, ventas_fecha[i].fecha); // Añade la fecha
		}
	}

	strcat(respuesta, ". Cantidad de dinero recaudado: ");  // Añade la segunda parte del mensaje
	strcat(respuesta, dinero_recaudado);  // Añade el total de dinero

	return respuesta;
}
