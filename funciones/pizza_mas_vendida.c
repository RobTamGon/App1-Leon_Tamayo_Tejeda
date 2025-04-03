#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../structs.h"
#include "pizza_mas_vendida.h"

#define MAX_PIZZAS 200

char* metrica_pms(int *size, VentaPizza *ventas) {
    // Arreglo para guardar los nombres y cantidades
    PizzaVenta resumen[MAX_PIZZAS];
    int total = 0;

    // Agrupar cantidades por pizza
    for (int i = 0; i < *size; i++) {
        int j;
        for (j = 0; j < total; j++) {
            if (strcmp(ventas[i].pizza_name, resumen[j].nombre) == 0) {
                resumen[j].cantidad_total += ventas[i].quantity;
                break;
            }
        }
        if (j == total && total < MAX_PIZZAS) {
            strcpy(resumen[total].nombre, ventas[i].pizza_name);
            resumen[total].cantidad_total = ventas[i].quantity;
            total++;
        }
    }

    // Buscar la pizza con mayor cantidad
    float max = 0;
    char *ganadora = NULL;

    for (int i = 0; i < total; i++) {
        if (resumen[i].cantidad_total > max) {
            max = resumen[i].cantidad_total;
            ganadora = resumen[i].nombre;
        }
    }

    // Retornar el nombre (como copia dinámica)
    return ganadora ? strdup(ganadora) : strdup("Sin datos");
}
