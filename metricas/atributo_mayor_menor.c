#include <stdio.h>    // Para imprimir
#include <stdlib.h>   // Para usar memoria dinámica
#include <string.h>   // Para trabajar con texto (strcmp, strcpy, strtok)

#include "../structs.h"   // Archivo donde están definidas nuestras estructuras

#define MAX_PIZZAS 1000   // Vamos a asumir que como máximo hay 1000 tipos de pizzas
#define MAX_INGREDIENTES 1000  // Suponemos máximo 1000 ingredientes distintos


typedef struct
{
    char nombre[128];
    float cantidad_total;
} PizzaVenta;


// Función principal que encuentra cuál fue la pizza más vendida
char* pizza_mas_vendida(int *size, order *orders)
{
	PizzaVenta resumen[MAX_PIZZAS];   // Aquí vamos a guardar las pizzas distintas y cuánto vendieron
	int total_pizzas = 0;             // Cuántas pizzas distintas hemos encontrado
	int cantidad_ventas = *size;      // Cuántas ventas hay en total

	// Vamos a recorrer todas las ventas una por una
	for (int i = 0; i < cantidad_ventas; i++)
	{
		int encontrada = 0;  // Esta variable nos dice si ya habíamos visto esta pizza antes

		// Recorremos el resumen que llevamos hecho hasta ahora
		for (int j = 0; j < total_pizzas; j++)
		{
			// Comparamos si la pizza ya estaba
			if (strcmp(orders[i].pizza_name, resumen[j].nombre) == 0)
			{
				// Si la encontramos, sumamos las unidades vendidas
				resumen[j].cantidad_total += orders[i].quantity;
				encontrada = 1;  // Ya la encontramos, no hay que agregarla de nuevo
				break;           // Salimos del for
			}
		}

		// Si no la encontramos, es una pizza nueva
		if (!encontrada)
		{
			strcpy(resumen[total_pizzas].nombre, orders[i].pizza_name);  // Guardamos su nombre
			resumen[total_pizzas].cantidad_total = orders[i].quantity;   // Guardamos cuántas unidades se vendieron
			total_pizzas++;  // Aumentamos el contador de pizzas distintas
		}
	}

	// Ahora que ya tenemos todo el resumen, buscamos cuál pizza se vendió más veces
	float mayor_venta = 0;  // Aquí vamos a guardar el número mayor de unidades vendidas
	for (int i = 0; i < total_pizzas; i++)
	{
		if (resumen[i].cantidad_total > mayor_venta)
		{
			mayor_venta = resumen[i].cantidad_total;  // Actualizamos si encontramos una pizza con más ventas
		}
	}

	// Si por alguna razón no hubo ventas, devolvemos un mensaje que diga eso
	if (mayor_venta == 0)
	{
		char *mensaje = malloc(64);  // Reservamos espacio para el mensaje
		strcpy(mensaje, "No se encontraron ventas válidas.");  // Copiamos el mensaje
		return mensaje;  // Lo devolvemos
	}

	// Ahora creamos el texto final que vamos a devolver
	char *respuesta = malloc(2048);  // Reservamos espacio de sobra
	strcpy(respuesta, "Pizza mas vendida: ");  // Empezamos escribiendo la primera parte del mensaje

	int primera = 1;  // Esto nos ayuda a saber si tenemos que poner coma o no
	// Recorremos otra vez todas las pizzas
	for (int i = 0; i < total_pizzas; i++)
	{
		if (resumen[i].cantidad_total == mayor_venta)
		{
			if (!primera)
			{
				strcat(respuesta, ", ");  // Si ya pusimos una pizza antes, agregamos una coma
			}
			strcat(respuesta, resumen[i].nombre);  // Agregamos el nombre de la pizza
			primera = 0;  // Después de la primera, siempre agregaremos comas
		}
	}

	// Al final agregamos entre paréntesis la cantidad de unidades vendidas
	char cantidad_texto[64];
	sprintf(cantidad_texto, " (%.0f unidades)", mayor_venta);  // Convertimos el número en texto
	strcat(respuesta, cantidad_texto);  // Lo pegamos al mensaje

	return respuesta;  // Devolvemos el texto completo para que lo impriman donde quieran
}



char* pizza_menos_vendida(int *size, order *orders)
{
    PizzaVenta resumen[MAX_PIZZAS];  // Aquí guardamos las pizzas que vayamos encontrando
    int total_pizzas = 0;
    int cantidad_ventas = *size;     // Cuántas ventas hay

    // 1. Recorrer todas las ventas
    for (int i = 0; i < cantidad_ventas; i++)
	{
        int encontrada = 0;  // Para saber si ya vimos esta pizza antes

        // Revisar si ya tenemos esta pizza
        for (int j = 0; j < total_pizzas; j++)
		{
            if (strcmp(orders[i].pizza_name, resumen[j].nombre) == 0)
			{
                resumen[j].cantidad_total += orders[i].quantity;  // Sumamos la cantidad
                encontrada = 1;
                break;
            }
        }

        // Si es una pizza nueva, la agregamos al resumen
        if (!encontrada)
		{
            strcpy(resumen[total_pizzas].nombre, orders[i].pizza_name);
            resumen[total_pizzas].cantidad_total = orders[i].quantity;
            total_pizzas++;
        }
    }

    // 2. Si no hay ventas, devolvemos un mensaje
    if (total_pizzas == 0)
	{
        char *mensaje = malloc(64);
        strcpy(mensaje, "No se encontraron ventas válidas.");
        return mensaje;
    }

    // 3. Buscar la menor cantidad de ventas
    float menor_venta = resumen[0].cantidad_total;  // Empezamos con la primera pizza
    for (int i = 1; i < total_pizzas; i++)
	{
        if (resumen[i].cantidad_total < menor_venta)
		{
            menor_venta = resumen[i].cantidad_total;
        }
    }

    // 4. Armar el resultado
    char *respuesta = malloc(2048);  // Reservamos espacio suficiente
    strcpy(respuesta, "Pizza menos vendida: ");

    int primera = 1;  // Para manejar las comas
    for (int i = 0; i < total_pizzas; i++)
	{
        if (resumen[i].cantidad_total == menor_venta)
		{
            if (!primera)
			{
                strcat(respuesta, ", ");  // Agregamos coma si no es la primera
            }
            strcat(respuesta, resumen[i].nombre);  // Agregamos el nombre de la pizza
            primera = 0;
        }
    }

    // Agregar al final la cantidad de unidades vendidas
    char cantidad_texto[64];
    sprintf(cantidad_texto, " (%.0f unidades)", menor_venta);
    strcat(respuesta, cantidad_texto);

    return respuesta;  // Devolvemos el texto completo
}



char* ingrediente_mas_vendido(int *size, order *orders)
{
    // Estructura temporal para guardar ingredientes
    typedef struct
	{
        char nombre[64];
        float cantidad_total;
    } IngredienteVenta;

    IngredienteVenta resumen[MAX_INGREDIENTES];  // Aquí vamos guardando los ingredientes
    int total_ingredientes = 0;
    int cantidad_ventas = *size;

    // 1. Recorrer todas las ventas
    for (int i = 0; i < cantidad_ventas; i++)
	{
        char ingredientes[256];
        strcpy(ingredientes, orders[i].pizza_ingredients);  // Copiar ingredientes para no modificar el original

        // Separar ingredientes uno por uno
        char *token = strtok(ingredientes, ",");
        while (token != NULL) {
            // Eliminar espacio inicial si hay
            while (*token == ' ') token++;

            int encontrado = 0;

            // Buscar si ya vimos este ingrediente antes
            for (int j = 0; j < total_ingredientes; j++)
			{
                if (strcmp(token, resumen[j].nombre) == 0)
				{
                    resumen[j].cantidad_total += orders[i].quantity;
                    encontrado = 1;
                    break;
                }
            }

            // Si es un ingrediente nuevo, lo agregamos
            if (!encontrado)
			{
                strcpy(resumen[total_ingredientes].nombre, token);
                resumen[total_ingredientes].cantidad_total = orders[i].quantity;
                total_ingredientes++;
            }

            // Pasar al siguiente ingrediente
            token = strtok(NULL, ",");
        }
    }

    // 2. Si no encontramos ingredientes
    if (total_ingredientes == 0)
	{
        char *mensaje = malloc(64);
        strcpy(mensaje, "No se encontraron ingredientes válidos.");
        return mensaje;
    }

    // 3. Buscar el ingrediente más vendido
    float mayor_venta = 0;
    for (int i = 0; i < total_ingredientes; i++)
	{
        if (resumen[i].cantidad_total > mayor_venta)
		{
            mayor_venta = resumen[i].cantidad_total;
        }
    }

    // 4. Armar la respuesta
    char *respuesta = malloc(2048);
    strcpy(respuesta, "Ingrediente mas vendido: ");

    int primera = 1;
    for (int i = 0; i < total_ingredientes; i++)
	{
        if (resumen[i].cantidad_total == mayor_venta)
		{
            if (!primera)
			{
                strcat(respuesta, ", ");  // Coma si ya agregamos uno antes
            }
            strcat(respuesta, resumen[i].nombre);  // Agregamos el nombre del ingrediente
            primera = 0;
        }
    }

    // Agregar la cantidad de unidades vendidas
    char cantidad_texto[64];
    sprintf(cantidad_texto, " (%.0f unidades)", mayor_venta);
    strcat(respuesta, cantidad_texto);

    return respuesta;
}
