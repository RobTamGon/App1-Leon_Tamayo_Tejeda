#include <stdio.h>
#include "structs.h"
#include "lectura_csv.h" // Importamos la función leer_csv

#define MAX_VENTAS 500

int main() {
    VentaPizza ventas[MAX_VENTAS];

    // Llamamos a la función que lee el CSV
    int total_ventas = leer_csv("venta.csv", ventas, MAX_VENTAS);

    printf("Total ventas cargadas: %d\n", total_ventas);

    // Imprimimos las primeras 10 ventas
    for (int j = 0; j < 10 && j < total_ventas; j++) {
        printf("Venta %d - Pizza: %s, Cantidad: %.2f, Total: %.2f\n",
               j + 1, ventas[j].pizza_name, ventas[j].quantity, ventas[j].unit_price);
    }

    return 0;
}
