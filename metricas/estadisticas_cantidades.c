#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../structs.h"

// Encuentra el promedio de pizzas por orden
char* encontrar_promedio_pizzas_orden(int *size, order *orders) {
    float suma_pizzas = 0; // Suma de pizzas por orden
    int cantidad_ordenes = 0; // Cantidad de órdenes diferentes

    // Asumimos que como máximo hay 'largo' órdenes diferentes
    int *ordenes = malloc((*size) * sizeof(int)); // Reservamos espacio de sobra
    if (!ordenes) {
        perror("Error al asignar memoria."); // Error al asignar memoria
        return NULL;
    }

    // Contar la cantidad de órdenes diferentes y sumar las pizzas por orden
    for (int i = 0; i < *size; i++) {
        int ya_contada = 0; // Indica si ya se ha encontrado la órden
        for (int j = 0; j < cantidad_ordenes; j++) {
            if (ordenes[j] == orders[i].order_id) {
                ya_contada = 1; // Si coincide, se marca como ya encontrado
                break;
            }
        }

        // Si no se ha encontrado la órden, se añade a la lista
        if (!ya_contada) {
            ordenes[cantidad_ordenes++] = orders[i].order_id; // Añadimos el órden a la lista
        }

        suma_pizzas += orders[i].quantity; // Suma de pizzas por orden
    }

    // Calcular el promedio de pizzas por orden
    float promedio_orden = (cantidad_ordenes > 0) ? suma_pizzas / cantidad_ordenes : 0; // Evitamos división por cero

    // Reservar memoria para el string de salida
    char *respuesta = malloc(100);
    if (!respuesta) {
        free(ordenes);
        perror("Error al asignar memoria.");
        return NULL;
    }

    // Convertir el promedio de pizzas a string con 2 decimales y añadir a la respuesta
    char pizzas_promedio[20]; // Reservamos espacio 
    sprintf(pizzas_promedio, "%.2f", promedio_orden); // Convertir el promedio de pizzas a string con 2 decimales

    // Construir la respuesta
    strcpy(respuesta, "Promedio de pizzas por orden: ");  // Empezamos escribiendo la primera parte del mensaje
    strcat(respuesta, pizzas_promedio);  // Añadimos el promedio de pizzas

    free(ordenes); // Liberar memoria usada para órdenes
    return respuesta; // Devolver la respuesta
}

// Encuentra el promedio de pizzas por día
char* encontrar_promedio_pizzas_dia(int *size, order *orders) {
    float suma_pizzas = 0; // Suma de pizzas por día
    int cantidad_dias = 0; // Cantidad de días diferentes

    // Asumimos que como máximo hay 'largo' dias diferentes
    char **dias = malloc((*size) * sizeof(int)); // Reservamos espacio de sobra
    if (!dias) {
        perror("Error al asignar memoria."); // Error al asignar memoria
        return NULL;
    }

    // Contar la cantidad de días diferentes y sumar las pizzas por día
    for (int i = 0; i < *size; i++) {
        int ya_contado = 0; // Indica si ya se ha encontrado el día
        for (int j = 0; j < cantidad_dias; j++) {
            if (strcmp(dias[j], orders[i].order_date) == 0) { 
                ya_contado = 1; // Si coincide, se marca como ya encontrado
                break;
            }
        }

        // Si no se ha encontrado el día, se añade a la lista
        if (!ya_contado) {
            dias[cantidad_dias] = malloc(strlen(orders[i].order_date) + 1); // Reservamos espacio
            if (!dias[cantidad_dias]) { // Error al asignar memoria
                // Liberar memoria usada para fechas
                for (int k = 0; k < cantidad_dias; k++) free(dias[k]);
                free(dias);
                perror("Error al asignar memoria.");
                return NULL;
            }
            strcpy(dias[cantidad_dias], orders[i].order_date); // Copiamos el día
            cantidad_dias++; // Aumentamos el contador de la cantidad de días
        }

        suma_pizzas += orders[i].quantity; // Suma de pizzas por día
    }

    // Calcular el promedio de pizzas por día
    float promedio_dia = (cantidad_dias > 0) ? suma_pizzas / cantidad_dias : 0; // Evitamos división por cero

    // Reservar memoria para el string de salida
    char *respuesta = malloc(100); 
    if (!respuesta) {
        // Liberar memoria usada para fechas
        for (int i = 0; i < cantidad_dias; i++) free(dias[i]);
        free(dias);
        perror("Error al asignar memoria."); // Error al asignar memoria
        return NULL;
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
    return respuesta; // Devolver la respuesta
}

// Definición de la estructura para almacenar la cantidad de pizzas por categoría
typedef struct {
    char nombre[50];
    float cantidad;
} Categoria;

// Encuentra la cantidad de pizzas por categoría vendidas
char* ventas_categoria(int *size, order *orders) {
    Categoria *categorias = malloc((*size) * sizeof(Categoria)); // Reservamos memoria para categorías
    if (!categorias) {
        perror("Error al asignar memoria."); // Error al asignar memoria
        return NULL;
    }

    int total_categorias = 0; // Contador de categorías

    // Contar la cantidad de pizzas vendidas por categoría
    for (int i = 0; i < *size; i++) {
        int idx = -1;
        for (int j = 0; j < total_categorias; j++) {
            if (strcmp(categorias[j].nombre, orders[i].pizza_category) == 0) { // Comprobamos si la categoría coincide
                idx = j; // Si coincide, se guarda el índice
                break;
            }
        }

        // Si no se ha encontrado la categoría, se añade a la lista
        if (idx == -1) {
            strcpy(categorias[total_categorias].nombre, orders[i].pizza_category); // Copiamos la categoría
            categorias[total_categorias].cantidad = 0; // Inicializamos la cantidad de pizzas
            idx = total_categorias; // Guardamos el índice
            total_categorias++; // Aumentamos el contador de categorías
        }
        categorias[idx].cantidad += orders[i].quantity; // Sumamos la cantidad de pizzas
    }

    // Reservar memoria para el string de salida
    char *respuesta = malloc(2048);
    if (!respuesta) {
        free(categorias);
        perror("Error al asignar memoria."); // Error al asignar memoria
        return NULL;
    }

    // Construir la respuesta
    strcpy(respuesta, "Cantidad de pizzas vendidas por categoria: ");  // Empezamos escribiendo la primera parte del mensaje

    // Añadimos la lista de categorías y cantidades de pizzas
    int primera_categoria = 1;
    for (int i = 0; i < total_categorias; i++) {
        if (categorias[i].cantidad > 0) {
            if (!primera_categoria) { // Añadimos una coma antes de añadir la siguiente categoría
                strcat(respuesta, ", ");
            }
            char cantidad[1000]; // Reservamos espacio para la cantidad de pizzas y categorias
            sprintf(cantidad, "%s: %.2f pizzas", categorias[i].nombre, categorias[i].cantidad); // Convertimos la cantidad a string
            strcat(respuesta, cantidad); // Añadimos la cantidad de pizzas a la respuesta
            primera_categoria = 0; // Marcamos como no primera categoría
        }
    }

    free(categorias); // Liberar memoria usada para categorías
    return respuesta; // Devolver la respuesta
}