#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ventas_pizzas.h"

// Función para encontrar la pizza más vendida
char* encontrar_pizza_mas_vendida(int *largo, Venta *ventas) {
    float pizzas[1000] = {0}; // Supongamos que hay un máximo de 1000 tipos de pizzas
    char nombres[1000][50]; // Almacenamos los nombres de pizzas

    int total_pizzas = 0; // Contador de pizzas

    // Recorrer todos los registros de ventas y almacena los nombres de pizzas y sus cantidades
    for (int i = 0; i < *largo; i++) {
        int idx = -1; // Inicializamos el índice a -1 para indicar que no se ha encontrado la pizza
        for (int j = 0; j < total_pizzas; j++) {
            if (strcmp(nombres[j], ventas[i].pizza_name) == 0) { // Comprobamos si el nombre de la pizza coincide
                idx = j; // Si coincide, se guarda el índice
                break;
            }
        }
        if (idx == -1) { // Si no se ha encontrado el nombre de la pizza, se añade a la lista
            strcpy(nombres[total_pizzas], ventas[i].pizza_name); // Copiamos el nombre de la pizza
            idx = total_pizzas; // Guardamos el índice
            total_pizzas++; // Aumentamos el contador de pizzas
        }
        pizzas[idx] += ventas[i].quantity; // Sumamos la cantidad de pizzas
    }

    // Encontrar la pizza más vendida
    float max_ventas = 0; // Inicializamos la cantidad máxima de pizzas a 0
    for (int i = 0; i < total_pizzas; i++) { // Recorremos todas las pizzas
        if (pizzas[i] > max_ventas) { // Si la cantidad de pizzas es mayor que la máxima, se actualiza
            max_ventas = pizzas[i]; // Actualizamos la cantidad máxima
        }
    }

    char *respuesta = malloc(2048);  // Reservamos memoria para la respuesta
    if (!respuesta) {
        perror("Error al asignar memoria."); // Error al asignar memoria
        return NULL;
    }

    strcpy(respuesta, "Pizza mas vendida: ");  // Empezamos escribiendo la primera parte del mensaje

    // Añadir todas las pizzas que tienen la cantidad máxima de ventas
    int primera_pizza = 1; // Indica si es la primera pizza a añadir
    for (int i = 0; i < total_pizzas; i++) {
        if (pizzas[i] == max_ventas) { // Si la cantidad de pizzas es igual a la máxima, se añade
            if (!primera_pizza) {
                strcat(respuesta, ", "); // Añadimos una coma antes de añadir la siguiente pizza
            }
            strcat(respuesta, nombres[i]); // Añadimos el nombre de la pizza
            primera_pizza = 0; // Marcamos como no primera pizza
        }
    }
    char cantidad_maxima[10]; // Reservamos espacio para la cantidad máxima
    // Convertir la cantidad máxima a string
    sprintf(cantidad_maxima, "%.2f", max_ventas);

    strcat(respuesta, ". Cantidad: "); // Añadimos la cantidad
    strcat(respuesta, cantidad_maxima); // Añadimos la cantidad máxima a la respuesta

    return respuesta; // Devolver la respuesta
}

// Función para encontrar la pizza menos vendida
char* encontrar_pizza_menos_vendida(int *largo, Venta *ventas) {
    float pizzas[1000] = {0}; // Supongamos que hay un máximo de 1000 tipos de pizzas
    char nombres[1000][50]; // Almacenamos los nombres de pizzas

    int total_pizzas = 0; // Contador de pizzas
    // Recorrer todos los registros de ventas y almacena los nombres de pizzas y sus cantidades
    for (int i = 0; i < *largo; i++) {
        int idx = -1; // Inicializamos el índice a -1 para indicar que no se ha encontrado la pizza
        for (int j = 0; j < total_pizzas; j++) {
            if (strcmp(nombres[j], ventas[i].pizza_name) == 0) { // Comprobamos si el nombre de la pizza coincide
                idx = j; // Si coincide, se guarda el índice
                break;
            }
        }
        if (idx == -1) { // Si no se ha encontrado el nombre de la pizza, se añade a la lista
            strcpy(nombres[total_pizzas], ventas[i].pizza_name); // Copiamos el nombre de la pizza
            idx = total_pizzas; // Guardamos el índice
            total_pizzas++; // Aumentamos el contador de pizzas
        }
        pizzas[idx] += ventas[i].quantity; // Sumamos la cantidad de pizzas
    }

    // Encontrar la pizza menos vendida
    float min_ventas = pizzas[0]; // Inicializamos la cantidad mínima de pizzas a la primera pizza
    for (int i = 1; i < total_pizzas; i++) {
        if (pizzas[i] < min_ventas) { // Si la cantidad de pizzas es menor que la mínima, se actualiza
            min_ventas = pizzas[i]; // Actualizamos la cantidad mínima
        }
    }

    char *respuesta = malloc(2048);  // Reservamos memoria para la respuesta
    if (!respuesta) {
        perror("Error al asignar memoria."); // Error al asignar memoria
        return NULL;
    }

    strcpy(respuesta, "Pizza menos vendida: ");  // Empezamos escribiendo la primera parte del mensaje
    int primera_pizza = 1; // Indica si es la primera pizza a añadir
    // Añadir todas las pizzas que tienen la cantidad mínima de ventas
    for (int i = 0; i < total_pizzas; i++) {
        if (pizzas[i] == min_ventas) { // Si la cantidad de pizzas es igual a la mínima, se añade
            if (!primera_pizza) {
                strcat(respuesta, ", "); // Añadimos una coma antes de añadir la siguiente pizza
            }
            strcat(respuesta, nombres[i]); // Añadimos el nombre de la pizza
            primera_pizza = 0; // Marcamos como no primera pizza
        }
    }

    char cantidad_minima[10]; // Reservamos espacio para la cantidad mínima
    // Convertir la cantidad máxima a string
    sprintf(cantidad_minima, "%.2f", min_ventas);

    strcat(respuesta, ". Cantidad: "); // Añadimos la cantidad
    strcat(respuesta, cantidad_minima); // Añadimos la cantidad mínima a la respuesta

    return respuesta; // Devolver la respuesta
}

// Función para encontrar el ingrediente más vendido
char* encontrar_ingrediente_mas_vendido(int *largo, Venta *ventas) {
    char ingredientes[500][50]; // Máximo 500 ingredientes distintos
    int cantidades[500] = {0}; // Almacenamos las cantidades de ingredientes
    int total_ingredientes = 0; // Contador de ingredientes

    // Recorrer todos los registros de ventas y almacena los ingredientes y sus cantidades
    for (int i = 0; i < *largo; i++) {
        char ingredientes_temp[200]; // Reservamos espacio para el ingrediente
        strcpy(ingredientes_temp, ventas[i].pizza_ingredients); // Copiamos los ingredientes de la venta
        
        // Separamos los ingredientes por comas y los guardamos en una lista 
        char *token = strtok(ingredientes_temp, ","); // Inicializamos el token de las cantidades de ingredientes
        while (token != NULL) {
            // Eliminar espacios iniciales
            while (*token == ' ') token++; 

            int idx = -1; // Inicializamos el índice a -1 para indicar que no se ha encontrado el ingrediente
            // Comprobamos si el ingrediente ya existe
            for (int j = 0; j < total_ingredientes; j++) {
                if (strcmp(ingredientes[j], token) == 0) { // Si coincide, se guarda el índice
                    idx = j; // Guardamos el índice
                    break;
                }
            }
            if (idx == -1) { // Si no se ha encontrado el ingrediente, se añade a la lista
                strcpy(ingredientes[total_ingredientes], token); // Copiamos el ingrediente
                idx = total_ingredientes; // Guardamos el índice
                total_ingredientes++; // Aumentamos el contador de ingredientes
            }
            cantidades[idx] += ventas[i].quantity; // Sumamos la cantidad de pizzas
            token = strtok(NULL, ","); // Siguiente token de ingredientes
        }
    }

    // Encontrar el ingrediente más usado
    float max_cantidad = 0; // Inicializamos la cantidad máxima a 0
    for (int i = 0; i < total_ingredientes; i++) { 
        if (cantidades[i] > max_cantidad) { // Si la cantidad de ingredientes es mayor que la máxima, se actualiza
            max_cantidad = cantidades[i]; // Actualizamos la cantidad máxima
        }
    }

    char *respuesta = malloc(2048);  // Reservamos memoria para la respuesta
    if (!respuesta) {
        perror("Error al asignar memoria."); // Error al asignar memoria
        return NULL;
    }

    strcpy(respuesta, "Ingrediente mas vendido: ");  // Empezamos escribiendo la primera parte del mensaje
    int primer_ingrediente = 1; // Indica si es el primer ingrediente a añadir
    // Añadir todOS los ingredientes que tienen la cantidad máxima
    for (int i = 0; i < total_ingredientes; i++) {
        if (cantidades[i] == max_cantidad) { // Si la cantidad de ingredientes es igual a la máxima, se añade
            if (!primer_ingrediente) {
                strcat(respuesta, ", "); // Añadimos una coma antes de añadir la siguiente ingrediente
            }
            strcat(respuesta, ingredientes[i]); // Añadimos el nombre del ingrediente
            primer_ingrediente = 0; // Marcamos como no primer ingrediente
        }
    }

    char cantidad_maxima_ingrediente[10]; // Reservamos espacio para la cantidad máxima
    // Convertir la cantidad máxima a string con 2 decimales
    sprintf(cantidad_maxima_ingrediente, "%.2f", max_cantidad); 

    strcat(respuesta, ". Cantidad: "); // Añadimos la cantidad
    strcat(respuesta, cantidad_maxima_ingrediente); // Añadimos la cantidad máxima a la respuesta
 
    return respuesta; // Devolver la respuesta
}
