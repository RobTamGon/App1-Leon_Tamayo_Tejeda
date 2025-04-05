#ifndef VENTAS_PROMEDIO_H
#define VENTAS_PROMEDIO_H

#include "leer_csv.h"

// Encuentra el promedio de pizzas por orden
char* encontrar_promedio_pizzas_orden(int *largo, Venta *ventas);

// Encuentra el promedio de pizzas por día
char* encontrar_promedio_pizzas_por_dia(int *largo, Venta *ventas);

// Encuentra la cantidad de pizzas por categoría vendidas
char* encontrar_categorias_vendidas(int *largo, Venta *ventas);


#endif // VENTAS_PROMEDIO_H