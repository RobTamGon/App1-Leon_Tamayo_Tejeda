#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ventas_fechas.h"

#define MAX_FECHAS 1000 // Suponemos un máximo de 1000 fechas distintas

// Estructura auxiliar para almacenar ventas por fecha
typedef struct {
    char fecha[20];
    int total_pizzas;
    float total_dinero;
} VentaFecha;

// Encuentra la fecha con más ventas en cantidad de pizzas
char* encontrar_fecha_mas_vendida(int *largo, Venta *ventas) {
    VentaFecha ventas_fecha[MAX_FECHAS] = {0};
    int total_fechas = 0;
    char fecha_mas_vendida[20] = {0};

    for (int i = 0; i < largo; i++) {
        int idx = -1;
        for (int j = 0; j < total_fechas; j++) {
            if (strcmp(ventas_fecha[j].fecha, ventas[i].order_date) == 0) {
                idx = j;
                break;
            }
        }
        if (idx == -1) {
            strcpy(ventas_fecha[total_fechas].fecha, ventas[i].order_date);
            idx = total_fechas;
            total_fechas++;
        }
        ventas_fecha[idx].total_pizzas += ventas[i].quantity;
    }

    // Encontrar la fecha con más ventas en cantidad de pizzas
    int max_ventas = 0, index_max = 0;
    for (int i = 0; i < total_fechas; i++) {
        if (ventas_fecha[i].total_pizzas > max_ventas) {
            max_ventas = ventas_fecha[i].total_pizzas;
            index_max = i;
        }
    }
    strcpy(fecha_mas_vendida, ventas_fecha[index_max].fecha);
    
    char *respuesta = malloc(2048);  // Reservamos espacio de sobra
    strcpy(respuesta, "Fecha mas ventas: ");  // Empezamos escribiendo la primera parte del mensaje
    strcat(respuesta, fecha_mas_vendida);  // Añadimos la fecha

    return respuesta;
}

// Encuentra la fecha con más ventas en dinero
char* encontrar_fecha_mas_ingresos(int *largo, Venta *ventas) {
    VentaFecha ventas_fecha[MAX_FECHAS] = {0};
    int total_fechas = 0;
    char fecha_mas_ingresos[20] = {0};

    for (int i = 0; i < largo; i++) {
        int idx = -1;
        for (int j = 0; j < total_fechas; j++) {
            if (strcmp(ventas_fecha[j].fecha, ventas[i].order_date) == 0) {
                idx = j;
                break;
            }
        }
        if (idx == -1) {
            strcpy(ventas_fecha[total_fechas].fecha, ventas[i].order_date);
            idx = total_fechas;
            total_fechas++;
        }
        ventas_fecha[idx].total_dinero += ventas[i].quantity * ventas[i].unit_price;
    }

    // Encontrar la fecha con más ingresos
    float max_ingresos = 0;
    int index_max = 0;
    for (int i = 0; i < total_fechas; i++) {
        if (ventas_fecha[i].total_dinero > max_ingresos) {
            max_ingresos = ventas_fecha[i].total_dinero;
            index_max = i;
        }
    }
    strcpy(fecha_mas_ingresos, ventas_fecha[index_max].fecha);

    char *respuesta = malloc(2048);  // Reservamos espacio de sobra
    strcpy(respuesta, "Fecha mas ingresos: ");  // Empezamos escribiendo la primera parte del mensaje
    strcat(respuesta, fecha_mas_ingresos);  // Añadimos la fecha

    return respuesta;
}

// Encuentra la fecha con menos ventas en cantidad de pizzas
char* encontrar_fecha_menos_vendida(int *largo, Venta *ventas) {
    VentaFecha ventas_fecha[MAX_FECHAS] = {0};
    int total_fechas = 0;
    char fecha_menos_vendida[20] = {0};

    for (int i = 0; i < largo; i++) {
        int idx = -1;
        for (int j = 0; j < total_fechas; j++) {
            if (strcmp(ventas_fecha[j].fecha, ventas[i].order_date) == 0) {
                idx = j;
                break;
            }
        }
        if (idx == -1) {
            strcpy(ventas_fecha[total_fechas].fecha, ventas[i].order_date);
            idx = total_fechas;
            total_fechas++;
        }
        ventas_fecha[idx].total_pizzas += ventas[i].quantity;
    }

    // Encontrar la fecha con menos ventas en cantidad de pizzas
    int min_ventas = ventas_fecha[0].total_pizzas, index_min = 0;
    for (int i = 1; i < total_fechas; i++) {
        if (ventas_fecha[i].total_pizzas < min_ventas) {
            min_ventas = ventas_fecha[i].total_pizzas;
            index_min = i;
        }
    }
    strcpy(fecha_menos_vendida, ventas_fecha[index_min].fecha);

    char *respuesta = malloc(2048);  // Reservamos espacio de sobra
    strcpy(respuesta, "Fecha menos ventas: ");  // Empezamos escribiendo la primera parte del mensaje
    strcat(respuesta, fecha_menos_vendida);  // Añadimos la fecha

    return respuesta;
}

// Encuentra la fecha con menos ventas en dinero
char* encontrar_fecha_menos_ingresos(int *largo, Venta *ventas) {
    VentaFecha ventas_fecha[MAX_FECHAS] = {0};
    int total_fechas = 0;
    char fecha_menos_ingresos[20] = {0};

    for (int i = 0; i < largo; i++) {
        int idx = -1;
        for (int j = 0; j < total_fechas; j++) {
            if (strcmp(ventas_fecha[j].fecha, ventas[i].order_date) == 0) {
                idx = j;
                break;
            }
        }
        if (idx == -1) {
            strcpy(ventas_fecha[total_fechas].fecha, ventas[i].order_date);
            idx = total_fechas;
            total_fechas++;
        }
        ventas_fecha[idx].total_dinero += ventas[i].quantity * ventas[i].unit_price;
    }

    // Encontrar la fecha con menos ingresos
    float min_ingresos = ventas_fecha[0].total_dinero;
    int index_min = 0;
    for (int i = 1; i < total_fechas; i++) {
        if (ventas_fecha[i].total_dinero < min_ingresos) {
            min_ingresos = ventas_fecha[i].total_dinero;
            index_min = i;
        }
    }
    strcpy(fecha_menos_ingresos, ventas_fecha[index_min].fecha);

    char *respuesta = malloc(2048);  // Reservamos espacio de sobra
    strcpy(respuesta, "Fecha menos ingresos: ");  // Empezamos escribiendo la primera parte del mensaje
    strcat(respuesta, fecha_menos_ingresos);  // Añadimos la fecha

    return respuesta;
}
