#include <stdio.h>
#include <string.h>
#include "../structs.h"
#include "pizza_mas_vendida.h"

#define MAX_PIZZAS 200


void pizza_mas_vendida(VentaPizza ventas[], int total_ventas) {
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

    // Buscar la pizza más vendida
    float max_cantidad = 0;
    int indice_max = -1;
    for (int i = 0; i < total_pizzas; i++) {
        if (resumen[i].cantidad_total > max_cantidad) {
            max_cantidad = resumen[i].cantidad_total;
            indice_max = i;
        }
    }

    if (indice_max != -1) {
        printf("\n🍕 La pizza más vendida es: %s\n", resumen[indice_max].nombre);
        printf("👉 Total de unidades vendidas: %.2f\n", resumen[indice_max].cantidad_total);
    } else {
        printf("No se encontraron ventas válidas.\n");
    }
}
