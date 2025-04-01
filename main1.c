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
    for (int i = 0; i < 10 && i < total_ventas; i++) {
        printf("Venta %d - Pizza: %s, Cantidad: %.2f, Total: %.2f, Ingrediente: %s \n", 
               i + 1, ventas[i].pizza_name, ventas[i].quantity, ventas[i].unit_price, ventas[i].pizza_ingredients);
    }

    return 0;
}
