#include <stdio.h>
#include <string.h>
#include "../structs.h"
#include "pizza_menos_vendida.h"

#define MAX_PIZZAS 200

void pizza_menos_vendida(VentaPizza ventas[], int total_ventas) {
    PizzaVenta resumen[MAX_PIZZAS];
    int total_pizzas = 0;

    for (int i = 0; i < total_ventas; i++) {
        int encontrada = 0;
        for (int j = 0; j < total_pizzas; j++) {
            if (strcmp(ventas[i].pizza_name, resumen[j].nombre) == 0) {
                resumen[j].cantidad_total += ventas[i].quantity;
                encontrada = 1;
                break;
            }
        }
        if (!encontrada && total_pizzas < MAX_PIZZAS) {
            strcpy(resumen[total_pizzas].nombre, ventas[i].pizza_name);
            resumen[total_pizzas].cantidad_total = ventas[i].quantity;
            total_pizzas++;
        }
    }

    // Buscar la menor cantidad vendida
    float min_cantidad = resumen[0].cantidad_total;
    for (int i = 1; i < total_pizzas; i++) {
        if (resumen[i].cantidad_total < min_cantidad) {
            min_cantidad = resumen[i].cantidad_total;
        }
    }

    printf("\n Pizzas menos vendidas (empate o única):\n");
    for (int i = 0; i < total_pizzas; i++) {
        if (resumen[i].cantidad_total == min_cantidad) {
            printf(" %s - Unidades vendidas: %.2f\n", resumen[i].nombre, resumen[i].cantidad_total);
        }
    }

    if (total_pizzas == 0) {
        printf("No se encontraron ventas válidas.\n");
    }
}
