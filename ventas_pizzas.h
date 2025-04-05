#ifndef VENTAS_PIZZAS_H
#define VENTAS_PIZZAS_H

// Incluimos el .h de leer_csv.h y se define el .h
#include "leer_csv.h"

// Definición de funciones pizzas más y menos vendidas, e ingrediente más vendido
// Encuentra la pizza más vendida
char* encontrar_pizza_mas_vendida(int *largo, Venta *ventas);

// Encuentra la pizza menos vendida
char* encontrar_pizza_menos_vendida(int *largo, Venta *ventas);

// Encuentra el ingrediente más vendido
char* encontrar_ingrediente_mas_vendido(int *largo, Venta *ventas);

#endif // VENTAS_PIZZAS_H
