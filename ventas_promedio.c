#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ventas_promedio.h"

// Encuentra el promedio de pizzas por orden
char* encontrar_promedio_pizzas_orden(int *largo, Venta *ventas) {
    float suma_pizzas = 0;
    int cantidad_ordenes = 0;

    // Asumimos que como máximo hay 'largo' órdenes diferentes
    int *ordenes = malloc((*largo) * sizeof(int));
    if (!ordenes) {
        return strdup("Error al asignar memoria.");
    }

    for (int i = 0; i < *largo; i++) {
        int ya_contada = 0;
        for (int j = 0; j < cantidad_ordenes; j++) {
            if (ordenes[j] == ventas[i].order_id) {
                ya_contada = 1;
                break;
            }
        }

        if (!ya_contada) {
            ordenes[cantidad_ordenes++] = ventas[i].order_id;
        }

        suma_pizzas += ventas[i].quantity;
    }

    // Calcular el promedio de pizzas por orden
    float promedio_orden = (cantidad_ordenes > 0) ? suma_pizzas / cantidad_ordenes : 0;

    // Reservar memoria para el string de salida
    char *respuesta = malloc(100);
    if (!respuesta) {
        free(ordenes);
        return strdup("Error al asignar memoria.");
    }
    // Convertir el promedio de pizzas a string con 2 decimales
    char pizzas_promedio[20];
    sprintf(pizzas_promedio, "%.2f", promedio_orden);

    // Construir la respuesta
    strcpy(respuesta, "Promedio de pizzas por orden: ");  // Empezamos escribiendo la primera parte del mensaje
    strcat(respuesta, pizzas_promedio);  // Añadimos el promedio de pizzas

    free(ordenes);
    return respuesta;
}

// Encuentra el promedio de pizzas por día
char* encontrar_promedio_pizzas_por_dia(int *largo, Venta *ventas) {
    float suma_pizzas = 0;
    int cantidad_dias = 0;

    // Asumimos que como máximo hay 'largo' dias diferentes
    char **dias = malloc((*largo) * sizeof(int));
    if (!dias) {
        return strdup("Error al asignar memoria.");
    }

    for (int i = 0; i < *largo; i++) {
        int ya_contada = 0;
        for (int j = 0; j < cantidad_dias; j++) {
            if (strcmp(dias[j], ventas[i].order_date) == 0) {
                ya_contada = 1;
                break;
            }
        }
        if (!ya_contada) {
            dias[cantidad_dias] = malloc(strlen(ventas[i].order_date) + 1);
            if (!dias[cantidad_dias]) {
                // Liberar memoria usada para fechas
                for (int k = 0; k < cantidad_dias; k++) free(dias[k]);
                free(dias);
                return strdup("Error al asignar memoria.");
            }
            strcpy(dias[cantidad_dias], ventas[i].order_date);
            cantidad_dias++;
        }

        suma_pizzas += ventas[i].quantity;
    }

    // Calcular el promedio de pizzas por día
    float promedio_dia = (cantidad_dias > 0) ? suma_pizzas / cantidad_dias : 0;

    // Reservar memoria para el string de salida
    char *respuesta = malloc(100);
    if (!respuesta) {
        // Liberar memoria usada para fechas
        for (int i = 0; i < cantidad_dias; i++) free(dias[i]);
        free(dias);
        return strdup("Error al asignar memoria.");
    }
    // Convertir el promedio de pizzas a string con 2 decimales
    char pizzas_promedio[20];
    sprintf(pizzas_promedio, "%.2f", promedio_dia);

    // Construir la respuesta
    strcpy(respuesta, "Promedio de pizzas por dia: ");  // Empezamos escribiendo la primera parte del mensaje
    strcat(respuesta, pizzas_promedio);  // Añadimos el promedio de pizzas

    // Liberar memoria usada para fechas
    for (int i = 0; i < cantidad_dias; i++) free(dias[i]);
    free(dias);
    return respuesta;
}

typedef struct {
    char nombre[50];
    float cantidad;
} Categoria;

// Encuentra la cantidad de pizzas por categoría vendidas
char* encontrar_categorias_vendidas(int *largo, Venta *ventas) {
    Categoria *categorias = malloc((*largo) * sizeof(Categoria));
    if (!categorias) {
        return strdup("Error al asignar memoria.");
    }

    int total_categorias = 0;

    // Contar la cantidad de pizzas vendidas por categoría
    for (int i = 0; i < *largo; i++) {
        int idx = -1;
        for (int j = 0; j < total_categorias; j++) {
            if (strcmp(categorias[j].nombre, ventas[i].pizza_category) == 0) {
                idx = j;
                break;
            }
        }
        if (idx == -1) {
            strcpy(categorias[total_categorias].nombre, ventas[i].pizza_category);
            categorias[total_categorias].cantidad = 0; // Inicializamos la cantidad
            idx = total_categorias;
            total_categorias++;
        }
        categorias[idx].cantidad += ventas[i].quantity;
    }

    // Reservar memoria para el string de salida
    char *respuesta = malloc(2048);
    if (!respuesta) {
        free(categorias);
        return strdup("Error al asignar memoria.");
    }

    // Construir la respuesta
    strcpy(respuesta, "Cantidad de pizzas vendidas por categoria: ");  // Empezamos escribiendo la primera parte del mensaje

    int primera_categoria = 1;
    for (int i = 0; i < total_categorias; i++) {
        if (categorias[i].cantidad > 0) {
            if (!primera_categoria) {
                strcat(respuesta, ", ");
            }
            char cantidad[1000];
            sprintf(cantidad, "%s: %.2f pizzas", categorias[i].nombre, categorias[i].cantidad);
            strcat(respuesta, cantidad);
            primera_categoria = 0;
        }
    }

    free(categorias);
    return respuesta;
}