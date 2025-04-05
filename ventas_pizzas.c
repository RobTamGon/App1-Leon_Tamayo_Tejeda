#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ventas_pizzas.h"

// Función para encontrar la pizza más vendida
char* encontrar_pizza_mas_vendida(int *largo, Venta *ventas) {
    int ventas_1[1000] = {0}; // Supongamos que hay un máximo de 1000 tipos de pizzas
    char nombres[1000][50]; // Almacenamos los nombres de pizzas
    char *pizza_mas_vendida = malloc(2048);  // Reservamos espacio de sobra

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
        ventas_1[idx] += ventas[i].quantity;
    }

    // Encontrar la pizza más vendida
    int max_ventas = 0, index_max = 0;
    for (int i = 0; i < total_pizzas; i++) {
        if (ventas_1[i] > max_ventas) {
            max_ventas = ventas_1[i];
            index_max = i;
        }
    }
    strcpy(pizza_mas_vendida, nombres[index_max]);
    return pizza_mas_vendida;
}

// Función para encontrar la pizza menos vendida
char* encontrar_pizza_menos_vendida(int *largo, Venta *ventas) {
    int ventas_1[1000] = {0}; 
    char nombres[1000][50];
    char *pizza_menos_vendida = malloc(2048);  // Reservamos espacio de sobra

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
        ventas_1[idx] += ventas[i].quantity;
    }

    // Encontrar la pizza menos vendida
    int min_ventas = ventas_1[0], index_min = 0;
    for (int i = 1; i < total_pizzas; i++) {
        if (ventas_1[i] < min_ventas) {
            min_ventas = ventas_1[i];
            index_min = i;
        }
    }
    strcpy(pizza_menos_vendida, nombres[index_min]);
}

// Función para encontrar el ingrediente más vendido
char* encontrar_ingrediente_mas_usado(int *largo, Venta *ventas) {
    char ingredientes[500][50]; // Máximo 500 ingredientes distintos
    int cantidades[500] = {0};
    int total_ingredientes = 0;
    char *ingrediente_mas_usado = malloc(2048);  // Reservamos espacio de sobra

    for (int i = 0; i < *largo; i++) {
        char ingredientes_temp[200];
        strcpy(ingredientes_temp, ventas[i].pizza_ingredients);

        char *token = strtok(ingredientes_temp, ",");
        while (token != NULL) {
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

    // Encontrar el ingrediente más usado
    int max_cantidad = 0, index_max = 0;
    for (int i = 0; i < total_ingredientes; i++) {
        if (cantidades[i] > max_cantidad) {
            max_cantidad = cantidades[i];
            index_max = i;
        }
    }
    strcpy(ingrediente_mas_usado, ingredientes[index_max]);
}
