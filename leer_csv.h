#ifndef LEER_CSV_H
#define LEER_CSV_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int pizza_id;
    int order_id;
    char pizza_name_id[50];
    int quantity;
    char order_date[15];
    char order_time[10];  
    double unit_price;
    double total_price;
    char pizza_size;
    char pizza_category[20];
    char pizza_ingredients[200];
    char pizza_name[50];
} Venta;

Venta* leer_csv(const char* nombre_archivo, int* largo);
void liberar_ventas(Venta* ventas);

#endif