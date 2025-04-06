#ifndef ATRIBUTO_MAYOR_MENOR_H
#define ATRIBUTO_MAYOR_MENOR_H

#include "../structs.h"

// Obtiene cuál(es) fue(ron) la(s) pizza(s) más vendida(s) y cuántas unidades de esta(s) se vendieron
char* pizza_mas_vendida(int *size, order *orders);

// Obtiene cuál(es) fue(ron) la(s) pizza(s) menos vendida(s) y cuántas unidades de esta(s) se vendieron
char* pizza_menos_vendida(int *size, order *orders);

// Obtiene cuál(es) fue(ron) el/los ingrediente(s) más vendido(s) y cuántas unidades de esto(s) se vendieron
char* ingrediente_mas_vendido(int *size, order *orders);

#endif