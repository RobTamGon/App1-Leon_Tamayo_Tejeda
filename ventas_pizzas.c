#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ventas_pizzas.h"

// Función para encontrar la pizza más vendida
char* encontrar_pizza_mas_vendida(int *largo, Venta *ventas) {
    float pizzas[1000] = {0}; // Supongamos que hay un máximo de 1000 tipos de pizzas
    char nombres[1000][50]; // Almacenamos los nombres de pizzas
    //char *pizza_mas_vendida = malloc(2048);  // Reservamos espacio de sobra

    int total_pizzas = 0;
    for (int i = 0; i < *largo; i++) {
        int idx = -1;
        for (int j = 0; j < total_pizzas; j++) {
            if (strcmp(nombres[j], ventas[i].pizza_name) == 0) {
                idx = j;
                break;
            }
        }
        if (idx == -1) {
            strcpy(nombres[total_pizzas], ventas[i].pizza_name);
            idx = total_pizzas;
            total_pizzas++;
        }
        pizzas[idx] += ventas[i].quantity;
    }
    //printf("Pizzas y cantidades procesadas:\n");
    //for (int i = 0; i < total_pizzas; i++) {
    //    printf("Pizza: %s, Cantidad: %.2f\n", nombres[i], pizzas[i]);
    //}

    // Encontrar la pizza más vendida
    float max_ventas = 0;
    //int index_max = 0;
    for (int i = 0; i < total_pizzas; i++) {
        if (pizzas[i] > max_ventas) {
            max_ventas = pizzas[i];
            //index_max = i;
        }
    }

    char *respuesta = malloc(2048);  // Reservamos espacio de sobra
    if (!respuesta) {
        return "Error al asignar memoria.";
    }

    strcpy(respuesta, "Pizza mas vendida: ");  // Empezamos escribiendo la primera parte del mensaje
    //strcat(respuesta, pizza_mas_vendida);  // Añadimos la pizza
    // Añadir todas las pizzas que tienen la cantidad máxima de ventas
    int primera_pizza = 1;
    for (int i = 0; i < total_pizzas; i++) {
        if (pizzas[i] == max_ventas) {
            if (!primera_pizza) {
                strcat(respuesta, ", ");
            }
            strcat(respuesta, nombres[i]);
            primera_pizza = 0;
        }
    }
    char cantidad_maxima[10];
    // Convertir la cantidad máxima a string
    sprintf(cantidad_maxima, "%.2f", max_ventas);

    strcat(respuesta, ". Cantidad: ");
    strcat(respuesta, cantidad_maxima);

    return respuesta;
}

// Función para encontrar la pizza menos vendida
char* encontrar_pizza_menos_vendida(int *largo, Venta *ventas) {
    float pizzas[1000] = {0}; 
    char nombres[1000][50];
    //char *pizza_menos_vendida = malloc(2048);  // Reservamos espacio de sobra

    int total_pizzas = 0;
    for (int i = 0; i < *largo; i++) {
        int idx = -1;
        for (int j = 0; j < total_pizzas; j++) {
            if (strcmp(nombres[j], ventas[i].pizza_name) == 0) {
                idx = j;
                break;
            }
        }
        if (idx == -1) {
            strcpy(nombres[total_pizzas], ventas[i].pizza_name);
            idx = total_pizzas;
            total_pizzas++;
        }
        pizzas[idx] += ventas[i].quantity;
    }

    // Encontrar la pizza menos vendida
    float min_ventas = pizzas[0], index_min = 0;
    for (int i = 1; i < total_pizzas; i++) {
        if (pizzas[i] < min_ventas) {
            min_ventas = pizzas[i];
            //index_min = i;
        }
    }
    //strcpy(pizza_menos_vendida, nombres[index_min]);

    char *respuesta = malloc(2048);  // Reservamos espacio de sobra
    if (!respuesta) {
        return "Error al asignar memoria.";
    }

    strcpy(respuesta, "Pizza menos vendida: ");  // Empezamos escribiendo la primera parte del mensaje
    //strcat(respuesta, pizza_menos_vendida);  // Añadimos la pizza

    int primera_pizza = 1;
    for (int i = 0; i < total_pizzas; i++) {
        if (pizzas[i] == min_ventas) {
            if (!primera_pizza) {
                strcat(respuesta, ", ");
            }
            strcat(respuesta, nombres[i]);
            primera_pizza = 0;
        }
    }

    char cantidad_minima[10];
    // Convertir la cantidad máxima a string
    sprintf(cantidad_minima, "%.2f", min_ventas);

    strcat(respuesta, ". Cantidad: ");
    strcat(respuesta, cantidad_minima);

    return respuesta;
}

// Función para encontrar el ingrediente más vendido
char* encontrar_ingrediente_mas_vendido(int *largo, Venta *ventas) {
    char ingredientes[500][50]; // Máximo 500 ingredientes distintos
    int cantidades[500] = {0};
    int total_ingredientes = 0;
    //char *ingrediente_mas_vendido = malloc(2048);  // Reservamos espacio de sobra

    for (int i = 0; i < *largo; i++) {
        char ingredientes_temp[200];
        strcpy(ingredientes_temp, ventas[i].pizza_ingredients);

        char *token = strtok(ingredientes_temp, ",");
        while (token != NULL) {
            // Eliminar espacios iniciales
            while (*token == ' ') token++;

            int idx = -1;
            for (int j = 0; j < total_ingredientes; j++) {
                if (strcmp(ingredientes[j], token) == 0) {
                    idx = j;
                    break;
                }
            }
            if (idx == -1) {
                strcpy(ingredientes[total_ingredientes], token);
                idx = total_ingredientes;
                total_ingredientes++;
            }
            cantidades[idx] += ventas[i].quantity;
            token = strtok(NULL, ",");
        }
    }
    //printf("Ingredientes y cantidades procesadas:\n");
    //for (int i = 0; i < total_ingredientes; i++) {
    //    printf("Ingrediente: %s, Cantidad: %d\n", ingredientes[i], cantidades[i]);
    //}

    // Encontrar el ingrediente más usado
    float max_cantidad = 0;
    //int index_max = 0;
    for (int i = 0; i < total_ingredientes; i++) {
        if (cantidades[i] > max_cantidad) {
            max_cantidad = cantidades[i];
            //index_max = i;
        }
    }
    //strcpy(ingrediente_mas_vendido, ingredientes[index_max]);

    char *respuesta = malloc(2048);  // Reservamos espacio de sobra
    if (!respuesta) {
        return "Error al asignar memoria.";
    }

    strcpy(respuesta, "Ingrediente mas vendido: ");  // Empezamos escribiendo la primera parte del mensaje
    //strcat(respuesta, ingrediente_mas_vendido);  // Añadimos el ingrediente

    int primer_ingrediente = 1;
    for (int i = 0; i < total_ingredientes; i++) {
        if (cantidades[i] == max_cantidad) {
            if (!primer_ingrediente) {
                strcat(respuesta, ", ");
            }
            strcat(respuesta, ingredientes[i]);
            primer_ingrediente = 0;
        }
    }

    char cantidad_maxima_ingrediente[10];
    // Convertir la cantidad máxima a string
    sprintf(cantidad_maxima_ingrediente, "%.2f", max_cantidad);

    strcat(respuesta, ". Cantidad: ");
    strcat(respuesta, cantidad_maxima_ingrediente);

    return respuesta;
}
