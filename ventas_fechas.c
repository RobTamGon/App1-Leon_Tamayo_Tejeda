#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ventas_fechas.h"

#define MAX_FECHAS 1000 // Suponemos un máximo de 1000 fechas distintas

// Estructura auxiliar para almacenar ventas por fecha
typedef struct {
    char fecha[20];
    float total_pizzas;
    float total_dinero;
} VentaFecha;

// Encuentra la fecha con más ventas en cantidad de pizzas
char* encontrar_fecha_mas_vendida(int *largo, Venta *ventas) {
    VentaFecha ventas_fecha[MAX_FECHAS] = {0};
    int total_fechas = 0;
    //char *fecha_mas_vendida = malloc(2048);  // Reservamos espacio de sobra

    for (int i = 0; i < *largo; i++) {
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
        // Sumar la cantidad de pizzas y el total de dinero de la fecha
        ventas_fecha[idx].total_pizzas += ventas[i].quantity;
        //ventas_fecha[idx].total_dinero += ventas[i].total_price;
        // Impresión de depuración para verificar la suma de quantity y total_dinero
        //printf("Sumando %.2f pizzas y %.2f de dinero a la fecha %s, total actual: %.2f pizzas, %.2f de dinero\n",
        //    ventas[i].quantity, ventas[i].quantity * ventas[i].unit_price, ventas[i].order_date,
        //    ventas_fecha[idx].total_pizzas, ventas_fecha[idx].total_dinero);
    }

    // Imprimir las fechas y cantidades para depuración
    //printf("Fechas y cantidades procesadas:\n");
    //for (int i = 0; i < total_fechas; i++) {
    //    printf("Fecha: %s, Total Pizzas: %.2f, Total Dinero: %.2f\n",
    //           ventas_fecha[i].fecha, ventas_fecha[i].total_pizzas, ventas_fecha[i].total_dinero);
    //}

    // Encontrar la fecha con más ventas en cantidad de pizzas
    float max_ventas = 0; 
    //int index_max = 0;
    for (int i = 0; i < total_fechas; i++) {
        if (ventas_fecha[i].total_pizzas > max_ventas) {
            max_ventas = ventas_fecha[i].total_pizzas;
            //index_max = i;
        }
    }
    //strcpy(fecha_mas_vendida, ventas_fecha[index_max].fecha);

    char *respuesta = malloc(2048);  // Reservamos espacio de sobra
    if (!respuesta) {
        return "Error al asignar memoria.";
    }
    
    // Convertir el total de pizzas a string con 2 decimales
    //char dinero_recaudado[20];
    //sprintf(dinero_recaudado, "%.2f", ventas_fecha[index_max].total_dinero);
    char pizzas_recaudado[20];
    sprintf(pizzas_recaudado, "%.2f", max_ventas);

    //strcpy(respuesta, " Fecha con mas ventas en términos de dinero: ");  // Empezamos escribiendo la primera parte del mensaje
    //strcat(respuesta, fecha_mas_vendida);  // Añadimos la fecha
    //strcat(respuesta, ", Cantidades de dinero recaudado: ");  // Añadimos la segunda parte del mensaje
    //strcat(respuesta, dinero_recaudado);  // Añadimos el total de dinero

    strcpy(respuesta, "Fecha con mas ventas en terminos de cantidad de pizzas: ");  // Empezamos escribiendo la primera parte del mensaje
    //strcat(respuesta, fecha_mas_vendida);  // Añadimos la fecha
    // Añadir todas las fechas que tienen la cantidad máxima de ventas
    int primera_fecha = 1;
    for (int i = 0; i < total_fechas; i++) {
        if (ventas_fecha[i].total_pizzas == max_ventas) {
            if (!primera_fecha) {
                strcat(respuesta, ", ");
            }
            strcat(respuesta, ventas_fecha[i].fecha);
            primera_fecha = 0;
        }
    }

    strcat(respuesta, ". Cantidad de pizzas: ");  // Añadimos la tercera parte del mensaje
    strcat(respuesta, pizzas_recaudado);  // Añadimos el total de pizzas

    return respuesta;
}

// Encuentra la fecha con más ventas en dinero
char* encontrar_fecha_mas_ingresos(int *largo, Venta *ventas) {
    VentaFecha ventas_fecha[MAX_FECHAS] = {0};
    int total_fechas = 0;
    //char *fecha_mas_ingresos = malloc(2048);  // Reservamos espacio de sobra

    for (int i = 0; i < *largo; i++) {
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
        ventas_fecha[idx].total_dinero += ventas[i].total_price;
    }

    // Encontrar la fecha con más ingresos
    float max_ingresos = 0;
    //int index_max = 0;
    for (int i = 0; i < total_fechas; i++) {
        if (ventas_fecha[i].total_dinero > max_ingresos) {
            max_ingresos = ventas_fecha[i].total_dinero;
            //index_max = i;
        }
    }
    //strcpy(fecha_mas_ingresos, ventas_fecha[index_max].fecha);

    char *respuesta = malloc(2048);  // Reservamos espacio de sobra
    if (!respuesta) {
        return "Error al asignar memoria.";
    }

    // Convertir el total de dinero a string con 2 decimales
    char dinero_recaudado[20];
    sprintf(dinero_recaudado, "%.2f", max_ingresos);

    strcpy(respuesta, "Fecha con mas ventas en terminos de dinero: ");  // Empezamos escribiendo la primera parte del mensaje
    //strcat(respuesta, fecha_mas_ingresos);  // Añadimos la fecha
    // Añadir todas las fechas que tienen la cantidad máxima de ingresos    
    int primera_fecha = 1;
    for (int i = 0; i < total_fechas; i++) {
        if (ventas_fecha[i].total_dinero == max_ingresos) {
            if (!primera_fecha) {
                strcat(respuesta, ", ");
            }
            strcat(respuesta, ventas_fecha[i].fecha);
            primera_fecha = 0;
        }
    }
    strcat(respuesta, ". Cantidad de dinero recaudado: ");  // Añadimos la segunda parte del mensaje
    strcat(respuesta, dinero_recaudado);  // Añadimos el total de dinero

    return respuesta;
}

// Encuentra la fecha con menos ventas en cantidad de pizzas
char* encontrar_fecha_menos_vendida(int *largo, Venta *ventas) {
    VentaFecha ventas_fecha[MAX_FECHAS] = {0};
    int total_fechas = 0;
    //char *fecha_menos_vendida = malloc(2048);  // Reservamos espacio de sobra

    for (int i = 0; i < *largo; i++) {
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
    //printf("Fechas y cantidades procesadas:\n");
    //for (int i = 0; i < total_fechas; i++) {
    //    printf("Fecha: %s, Total Pizzas: %f\n", ventas_fecha[i].fecha, ventas_fecha[i].total_pizzas);
    //}

    // Encontrar la fecha con menos ventas en cantidad de pizzas
    float min_ventas = ventas_fecha[0].total_pizzas;
    //int index_min = 0;
    for (int i = 1; i < total_fechas; i++) {
        if (ventas_fecha[i].total_pizzas >= 0 && ventas_fecha[i].total_pizzas < min_ventas) {
            min_ventas = ventas_fecha[i].total_pizzas;
            //index_min = i;
        }
    }
    //strcpy(fecha_menos_vendida, ventas_fecha[index_min].fecha);

    char *respuesta = malloc(2048);  // Reservamos espacio de sobra
    if (!respuesta) {
        return "Error al asignar memoria.";
    }

    // Convertir el total de dinero a string con 2 decimales
    char pizzas_recaudado[20];
    sprintf(pizzas_recaudado, "%.2f", min_ventas);
    //sprintf(pizzas_recaudado, "%.2f", ventas_fecha[index_min].total_pizzas);

    strcpy(respuesta, "Fecha con menos ventas en terminos de cantidad de pizzas: ");  // Empezamos escribiendo la primera parte del mensaje
    //strcat(respuesta, fecha_menos_vendida);  // Añadimos la fecha
    // Añadir todas las fechas que tienen la cantidad mínima de ventas
    int primera_fecha = 1;
    for (int i = 0; i < total_fechas; i++) {
        //if (ventas_fecha[i].total_pizzas == min_ventas) {
        if (ventas_fecha[i].total_pizzas == min_ventas) {
            if (!primera_fecha) {
                strcat(respuesta, ", ");
            }
            strcat(respuesta, ventas_fecha[i].fecha);
            primera_fecha = 0;
        }
    }

    strcat(respuesta, ". Cantidad de pizzas: ");  // Añadimos la tercera parte del mensaje
    strcat(respuesta, pizzas_recaudado);  // Añadimos el total de pizzas

    return respuesta;
}

// Encuentra la fecha con menos ventas en dinero
char* encontrar_fecha_menos_ingresos(int *largo, Venta *ventas) {
    VentaFecha ventas_fecha[MAX_FECHAS] = {0};
    int total_fechas = 0;
    //char *fecha_menos_ingresos = malloc(2048);  // Reservamos espacio de sobra

    for (int i = 0; i < *largo; i++) {
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
        ventas_fecha[idx].total_dinero += ventas[i].total_price;
    }

    // Encontrar la fecha con menos ingresos
    float min_ingresos = ventas_fecha[0].total_dinero;
    //int index_min = 0;
    for (int i = 1; i < total_fechas; i++) {
        if (ventas_fecha[i].total_dinero >= 0 && ventas_fecha[i].total_dinero < min_ingresos) {
            min_ingresos = ventas_fecha[i].total_dinero;
            //index_min = i;
        }
    }
    //strcpy(fecha_menos_ingresos, ventas_fecha[index_min].fecha);

    char *respuesta = malloc(2048);  // Reservamos espacio de sobra
    if (!respuesta) {
        return "Error al asignar memoria.";
    }
    
    // Convertir el total de dinero a string con 2 decimales
    char dinero_recaudado[20];
    sprintf(dinero_recaudado, "%.2f", min_ingresos);
    //sprintf(dinero_recaudado, "%.2f", ventas_fecha[index_min].total_dinero);

    strcpy(respuesta, "Fecha con menos ventas en terminos de dinero: ");  // Empezamos escribiendo la primera parte del mensaje
    //strcat(respuesta, fecha_menos_ingresos);  // Añadimos la fecha
    // Añadir todas las fechas que tienen la cantidad mínima de ingresos
    int primera_fecha = 1;
    for (int i = 0; i < total_fechas; i++) {
        if (ventas_fecha[i].total_dinero == min_ingresos) {
            if (!primera_fecha) {
                strcat(respuesta, ", ");
            }
            strcat(respuesta, ventas_fecha[i].fecha);
            primera_fecha = 0;
        }
    }
    strcat(respuesta, ". Cantidad de dinero recaudado: ");  // Añadimos la segunda parte del mensaje
    strcat(respuesta, dinero_recaudado);  // Añadimos el total de dinero

    return respuesta;
}
