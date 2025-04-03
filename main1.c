#include <stdio.h>
#include <string.h>
#include "structs.h"
#include "lectura/lectura_csv.h" // Importamos la función leer_csv
#include "funciones/pizza_mas_vendida.h"
#include "funciones/pizza_menos_vendida.h"


#define MAX_VENTAS 500

int main(int argc, char *argv[]) {
    VentaPizza ventas[MAX_VENTAS];
    int total_ventas = leer_csv(argv[1], ventas, MAX_VENTAS);
    
    // Imprimimos las primeras 10 ventas
    //for (int i = 0; i < 10 && i < total_ventas; i++) {
        //printf("Venta %d - Pizza: %s, Cantidad: %.2f, Total: %.2f, Ingrediente: %s \n, Fecha: %s", 
              // i + 1, ventas[i].pizza_name, ventas[i].quantity, ventas[i].unit_price, ventas[i].pizza_ingredients, ventas[i].order_date);
    //}

    if (total_ventas == 0) {
        printf("No se cargaron ventas.\n");
        return 1;
    }

    if (argc < 2) {
        printf("Opciones disponibles:\n");
        printf("  pms     → Pizza más vendida\n");
        printf("  top3    → Top 3 pizzas más vendidas\n");
        printf("  cat     → Ventas por categoría\n");
        return 0;
    }

    for (int i = 2; i < argc; i++) {
        if (strcmp(argv[i], "pms") == 0) {
            pizza_mas_vendida(ventas, total_ventas);
        } else if (strcmp(argv[i], "pls") == 0) {
            pizza_menos_vendida(ventas, total_ventas);
        } else if (strcmp(argv[i], "cat") == 0) {
            printf("(Aquí se mostraría la agrupación por categoría)\n");
        } else {
            printf("Comando desconocido: %s\n", argv[i]);
        }
    }

    return 0;
}
    

