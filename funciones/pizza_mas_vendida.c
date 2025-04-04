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
    for (int i = 0; i < total_pizzas; i++) {
        if (resumen[i].cantidad_total > max_cantidad) {
            max_cantidad = resumen[i].cantidad_total;
        }
    }

    printf("\n Pizzas más vendidas (empate o única):\n");
    for (int i = 0; i < total_pizzas; i++) {
        if (resumen[i].cantidad_total == max_cantidad) {
            printf(" %s - Unidades vendidas: %.2f\n", resumen[i].nombre, resumen[i].cantidad_total);
        }
    }

    // Si no hubo ninguna
    if (max_cantidad == 0) {
        printf("No se encontraron ventas válidas.\n");
    }
}