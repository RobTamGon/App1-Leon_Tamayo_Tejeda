#ifndef FECHA_MAYOR_MENOR_H
#define FECHA_MAYOR_MENOR_H

#include "../structs.h"

// Definición de funciones que regresan la fecha con más y menos ventas, y la fecha con más y menos ingresos
// Encuentra la fecha con más ventas en cantidad de pizzas
char* encontrar_fecha_mas_vendida(int *size, order *orders);

// Encuentra la fecha con más ventas en dinero
char* encontrar_fecha_mas_ingresos(int *size, order *orders);

// Encuentra la fecha con menos ventas en cantidad de pizzas
char* encontrar_fecha_menos_vendida(int *size, order *orders);

// Encuentra la fecha con menos ventas en dinero
char* encontrar_fecha_menos_ingresos(int *size, order *orders);

#endif