#ifndef VENTAS_FECHAS_H
#define VENTAS_FECHAS_H

#include "leer_csv.h"

// Encuentra la fecha con más ventas en cantidad de pizzas
char* encontrar_fecha_mas_vendida(int *largo, Venta *ventas);

// Encuentra la fecha con más ventas en dinero
char* encontrar_fecha_mas_ingresos(int *largo, Venta *ventas);

// Encuentra la fecha con menos ventas en cantidad de pizzas
char* encontrar_fecha_menos_vendida(int *largo, Venta *ventas);

// Encuentra la fecha con menos ventas en dinero
char* encontrar_fecha_menos_ingresos(int *largo, Venta *ventas);

#endif // VENTAS_FECHAS_H
