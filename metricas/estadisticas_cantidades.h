#ifndef ESTADISTICAS_CANTIDADES_H
#define ESTADISTICAS_CANTIDADES_H

#include "../structs.h"

// Encuentra el promedio de pizzas por orden
char* promedio_pizzas_orden(int *size, order *orders);

// Encuentra el promedio de pizzas por día
char* promedio_pizzas_dia(int *size, order *orders);

// Encuentra la cantidad de pizzas vendidas para cada categoría
char* ventas_categoria(int *size, order *orders);

#endif