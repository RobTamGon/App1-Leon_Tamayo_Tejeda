#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../structs.h"
#include "pizza_menos_vendida.h"

#define MAX_PIZZAS 200

char* metrica_pls(int *size, VentaPizza *ventas) {
    PizzaVenta resumen[MAX_PIZZAS];
    int total = 0;

    // Agrupar ventas por nombre de pizza
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

    // Buscar la pizza menos vendida
    float min = resumen[0].cantidad_total;
    char *peor = resumen[0].nombre;

    for (int i = 1; i < total; i++) {
        if (resumen[i].cantidad_total < min) {
            min = resumen[i].cantidad_total;
            peor = resumen[i].nombre;
        }
    }

    return peor ? strdup(peor) : strdup("Sin datos");
}
