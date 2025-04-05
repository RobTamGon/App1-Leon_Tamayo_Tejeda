#ifndef LEER_CSV_H
#define LEER_CSV_H

// Se incluyen las bibliotecas necesarias y se define el .h
#include <stdio.h>
#include <stdlib.h>

// Se define la estructura para cada fila del CSV
typedef struct {
    int pizza_id;
    int order_id;
    char pizza_name_id[50];
    float quantity;
    char order_date[15];
    char order_time[10];  
    float unit_price;
    float total_price;
    char pizza_size[4];
    char pizza_category[20];
    char pizza_ingredients[200];
    char pizza_name[50];
} Venta;

// Definición de funciones leer_csv y liberar_ventas
Venta* leer_csv(const char* nombre_archivo, int* largo);
void liberar_ventas(Venta* ventas);

#endif