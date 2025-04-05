#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../structs.h"

#define MAX_FECHAS 1000 // Suponemos un máximo de 1000 fechas distintas

// Estructura auxiliar para almacenar ventas por fecha
typedef struct {
    char fecha[20];
    float total_pizzas;
    float total_dinero;
} VentaFecha;

// Encuentra la fecha con más ventas en cantidad de pizzas
char* encontrar_fecha_mas_vendida(int *size, order *orders) {
    VentaFecha ventas_fecha[MAX_FECHAS] = {0}; // Inicializamos la estructura de ventas por fecha
    int total_fechas = 0; // Contador de fechas

    // Recorrer las ventas y almacenar las ventas por fecha 
    for (int i = 0; i < *size; i++) {
        int idx = -1; // Inicializamos el índice a -1 para indicar que no se ha encontrado la fecha
        for (int j = 0; j < total_fechas; j++) {
            if (strcmp(ventas_fecha[j].fecha, orders[i].order_date) == 0) { // Si coincide, se guarda el índice
                idx = j; // Guardamos el índice
                break;
            }
        }
        if (idx == -1) { // Si no se ha encontrado la fecha, se añade a la lista
            strcpy(ventas_fecha[total_fechas].fecha, orders[i].order_date); // Copiamos la fecha
            idx = total_fechas; // Guardamos el índice
            total_fechas++; // Aumentamos el contador de fechas
        }
        // Sumar la cantidad de pizzas de la fecha
        ventas_fecha[idx].total_pizzas += orders[i].quantity;
    }

    // Encontrar la fecha con más ventas en cantidad de pizzas
    float max_ventas = 0; // Inicializamos la cantidad máxima de pizzas a 0
    for (int i = 0; i < total_fechas; i++) {
        if (ventas_fecha[i].total_pizzas > max_ventas) { // Si la cantidad de pizzas es mayor que la máxima, se actualiza
            max_ventas = ventas_fecha[i].total_pizzas; // Actualizamos la cantidad máxima
        }
    }

    char *respuesta = malloc(2048);  // Reservamos memoria para la respuesta
    if (!respuesta) {
        perror("Error al asignar memoria."); // Error al asignar memoria
        return NULL;
    }
    
    char pizzas_recaudado[20]; // Reservamos espacio para la cantidad de pizzas
    sprintf(pizzas_recaudado, "%.2f", max_ventas); // Convertimos el total de pizzas a string con 2 decimales

    strcpy(respuesta, "Fecha con mas ventas en terminos de cantidad de pizzas: ");  // Empezamos escribiendo la primera parte del mensaje
    // Añadir todas las fechas que tienen la cantidad máxima de ventas
    int primera_fecha = 1; // Indica si es la primera fecha a añadir
    for (int i = 0; i < total_fechas; i++) {
        if (ventas_fecha[i].total_pizzas == max_ventas) { // Si la cantidad de pizzas es igual a la máxima, se añade
            if (!primera_fecha) {
                strcat(respuesta, ", "); // Añadimos una coma antes de añadir la siguiente fecha
            }
            strcat(respuesta, ventas_fecha[i].fecha); // Añadimos la fecha
            primera_fecha = 0; // Marcamos como no primera fecha
        }
    }

    strcat(respuesta, ". Cantidad de pizzas: ");  // Añadimos la tercera parte del mensaje
    strcat(respuesta, pizzas_recaudado);  // Añadimos el total de pizzas

    return respuesta; // Devolver la respuesta
}

// Encuentra la fecha con más ventas en dinero
char* encontrar_fecha_mas_ingresos(int *size, order *orders) {
    VentaFecha ventas_fecha[MAX_FECHAS] = {0}; // Inicializamos la estructura de ventas por fecha
    int total_fechas = 0; // Contador de fechas

    // Recorrer las ventas y almacenar el total de dinero por fecha
    for (int i = 0; i < *size; i++) {
        int idx = -1; // Inicializamos el índice a -1 para indicar que no se ha encontrado la fecha
        for (int j = 0; j < total_fechas; j++) {
            if (strcmp(ventas_fecha[j].fecha, orders[i].order_date) == 0) { // Si coincide, se guarda el índice
                idx = j; // Guardamos el índice
                break;
            }
        }
        if (idx == -1) { // Si no se ha encontrado la fecha, se añade a la lista
            strcpy(ventas_fecha[total_fechas].fecha, orders[i].order_date); // Copiamos la fecha
            idx = total_fechas; // Guardamos el índice
            total_fechas++; // Aumentamos el contador de fechas
        }
        ventas_fecha[idx].total_dinero += orders[i].total_price; // Sumamos el total de dinero de la fecha
    }

    // Encontrar la fecha con más ingresos
    float max_ingresos = 0; // Inicializamos la cantidad máxima de ingresos a 0
    for (int i = 0; i < total_fechas; i++) {
        if (ventas_fecha[i].total_dinero > max_ingresos) { // Si la cantidad de ingresos es mayor que la máxima, se actualiza
            max_ingresos = ventas_fecha[i].total_dinero; // Actualizamos la cantidad máxima
        }
    }

    char *respuesta = malloc(2048);  // Reservamos memoria para la respuesta
    if (!respuesta) {
        perror("Error al asignar memoria."); // Error al asignar memoria
        return NULL;
    }

    // Convertir el total de dinero a string con 2 decimales
    char dinero_recaudado[20]; // Reservamos espacio para la cantidad de dinero
    sprintf(dinero_recaudado, "%.2f", max_ingresos); 

    strcpy(respuesta, "Fecha con mas ventas en terminos de dinero: ");  // Empezamos escribiendo la primera parte del mensaje
    // Añadir todas las fechas que tienen la cantidad máxima de ingresos    
    int primera_fecha = 1; // Indica si es la primera fecha a añadir
    for (int i = 0; i < total_fechas; i++) {
        if (ventas_fecha[i].total_dinero == max_ingresos) { // Si la cantidad de ingresos es igual a la máxima, se añade
            if (!primera_fecha) {
                strcat(respuesta, ", "); // Añadimos una coma antes de añadir la siguiente fecha
            }
            strcat(respuesta, ventas_fecha[i].fecha); // Añadimos la fecha
            primera_fecha = 0; // Marcamos como no primera fecha
        }
    }
    strcat(respuesta, ". Cantidad de dinero recaudado: ");  // Añadimos la segunda parte del mensaje
    strcat(respuesta, dinero_recaudado);  // Añadimos el total de dinero

    return respuesta;
}

// Encuentra la fecha con menos ventas en cantidad de pizzas
char* encontrar_fecha_menos_vendida(int *size, order *orders) {
    VentaFecha ventas_fecha[MAX_FECHAS] = {0}; // Inicializamos la estructura de ventas por fecha
    int total_fechas = 0; // Contador de fechas

    // Recorrer las ventas y almacenar las ventas por fecha
    for (int i = 0; i < *size; i++) {
        int idx = -1; // Inicializamos el índice a -1 para indicar que no se ha encontrado la fecha
        for (int j = 0; j < total_fechas; j++) {
            if (strcmp(ventas_fecha[j].fecha, orders[i].order_date) == 0) { // Si coincide, se guarda el índice
                idx = j; // Guardamos el índice
                break;
            }
        }
        if (idx == -1) { // Si no se ha encontrado la fecha, se añade a la lista
            strcpy(ventas_fecha[total_fechas].fecha, orders[i].order_date); // Copiamos la fecha
            idx = total_fechas; // Guardamos el índice
            total_fechas++; // Aumentamos el contador de fechas
        }
        ventas_fecha[idx].total_pizzas += orders[i].quantity; // Sumamos la cantidad de pizzas de la fecha
    }
    
    // Encontrar la fecha con menos ventas en cantidad de pizzas
    float min_ventas = ventas_fecha[0].total_pizzas; // Inicializamos la cantidad mínima de pizzas a la primera fecha
    for (int i = 1; i < total_fechas; i++) {
        if (ventas_fecha[i].total_pizzas >= 0 && ventas_fecha[i].total_pizzas < min_ventas) { // Si la cantidad de pizzas es menor que la mínima, se actualiza
            min_ventas = ventas_fecha[i].total_pizzas; // Actualizamos la cantidad mínima
        }
    }

    char *respuesta = malloc(2048);  // Reservamos memoria para la respuesta
    if (!respuesta) {
        perror("Error al asignar memoria."); // Error al asignar memoria
        return NULL;
    }

    // Convertir el total de dinero a string con 2 decimales
    char pizzas_recaudado[20]; // Reservamos espacio para la cantidad de pizzas
    sprintf(pizzas_recaudado, "%.2f", min_ventas);

    strcpy(respuesta, "Fecha con menos ventas en terminos de cantidad de pizzas: ");  // Empezamos escribiendo la primera parte del mensaje
    // Añadir todas las fechas que tienen la cantidad mínima de ventas
    int primera_fecha = 1; // Indica si es la primera fecha a añadir
    for (int i = 0; i < total_fechas; i++) {
        if (ventas_fecha[i].total_pizzas == min_ventas) { // Si la cantidad de pizzas es igual a la mínima, se añade
            if (!primera_fecha) {
                strcat(respuesta, ", "); // Añadimos una coma antes de añadir la siguiente fecha
            }
            strcat(respuesta, ventas_fecha[i].fecha); // Añadimos la fecha
            primera_fecha = 0; // Marcamos como no primera fecha
        }
    }

    strcat(respuesta, ". Cantidad de pizzas: ");  // Añadimos la tercera parte del mensaje
    strcat(respuesta, pizzas_recaudado);  // Añadimos el total de pizzas

    return respuesta; // Devolver la respuesta
}

// Encuentra la fecha con menos ventas en dinero
char* encontrar_fecha_menos_ingresos(int *size, order *orders) {
    VentaFecha ventas_fecha[MAX_FECHAS] = {0}; // Inicializamos la estructura de ventas por fecha
    int total_fechas = 0; // Contador de fechas

    // Recorrer las ventas y almacenar el total de dinero por fecha
    for (int i = 0; i < *size; i++) {
        int idx = -1; // Inicializamos el índice a -1 para indicar que no se ha encontrado la fecha
        for (int j = 0; j < total_fechas; j++) {
            if (strcmp(ventas_fecha[j].fecha, orders[i].order_date) == 0) { // Si coincide, se guarda el índice
                idx = j; // Guardamos el índice
                break;
            }
        }
        if (idx == -1) { // Si no se ha encontrado la fecha, se añade a la lista
            strcpy(ventas_fecha[total_fechas].fecha, orders[i].order_date); // Copiamos la fecha
            idx = total_fechas; // Guardamos el índice
            total_fechas++; // Aumentamos el contador de fechas
        }
        ventas_fecha[idx].total_dinero += orders[i].total_price; // Sumamos el total de dinero de la fecha
    }

    // Encontrar la fecha con menos ingresos
    float min_ingresos = ventas_fecha[0].total_dinero; // Inicializamos la cantidad mínima de ingresos a la primera fecha
    for (int i = 1; i < total_fechas; i++) {
        if (ventas_fecha[i].total_dinero >= 0 && ventas_fecha[i].total_dinero < min_ingresos) { // Si la cantidad de ingresos es menor que la mínima, se actualiza
            min_ingresos = ventas_fecha[i].total_dinero; // Actualizamos la cantidad mínima
        }
    }

    char *respuesta = malloc(2048);  // Reservamos memoria para la respuesta
    if (!respuesta) {
        perror("Error al asignar memoria."); // Error al asignar memoria
        return NULL;
    }
    
    // Convertir el total de dinero a string con 2 decimales
    char dinero_recaudado[20];  // Reservamos espacio para la cantidad de dinero
    sprintf(dinero_recaudado, "%.2f", min_ingresos);

    strcpy(respuesta, "Fecha con menos ventas en terminos de dinero: ");  // Empezamos escribiendo la primera parte del mensaje
    // Añadir todas las fechas que tienen la cantidad mínima de ingresos
    int primera_fecha = 1;
    for (int i = 0; i < total_fechas; i++) {
        if (ventas_fecha[i].total_dinero == min_ingresos) { // Si la cantidad de ingresos es igual a la mínima, se añade
            if (!primera_fecha) {
                strcat(respuesta, ", "); // Añadimos una coma antes de añadir la siguiente fecha
            }
            strcat(respuesta, ventas_fecha[i].fecha); // Añadimos la fecha
            primera_fecha = 0;  // Marcamos como no primera fecha
        }
    }
    strcat(respuesta, ". Cantidad de dinero recaudado: ");  // Añadimos la segunda parte del mensaje
    strcat(respuesta, dinero_recaudado);  // Añadimos el total de dinero

    return respuesta; // Devolver la respuesta
}
