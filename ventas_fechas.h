#ifndef VENTAS_FECHAS_H
#define VENTAS_FECHAS_H

// Incluimos el .h de leer_csv.h y se define el .h
#include "leer_csv.h"

// Definición de funciones fecha con más y menos ventas, y fecha con más y menos ingresos
// Encuentra la fecha con más ventas en cantidad de pizzas
char* encontrar_fecha_mas_vendida(int *largo, Venta *ventas);

// Encuentra la fecha con más ventas en dinero
char* encontrar_fecha_mas_ingresos(int *largo, Venta *ventas);

// Encuentra la fecha con menos ventas en cantidad de pizzas
char* encontrar_fecha_menos_vendida(int *largo, Venta *ventas);

// Encuentra la fecha con menos ventas en dinero
char* encontrar_fecha_menos_ingresos(int *largo, Venta *ventas);

#endif // VENTAS_FECHAS_H
