#include <stdio.h>
#include <string.h>
#include "structs.h"
#include "lectura/lectura_csv.h" // Importamos la función leer_csv
#include "funciones/pizza_mas_vendida.h"

#define MAX_VENTAS 500

int main(int argc, char *argv[]) {
    VentaPizza ventas[MAX_VENTAS];
    int total_ventas = leer_csv("venta.csv", ventas, MAX_VENTAS);
    
    // Imprimimos las primeras 10 ventas
    //for (int i = 0; i < 10 && i < total_ventas; i++) {
        //printf("Venta %d - Pizza: %s, Cantidad: %.2f, Total: %.2f, Ingrediente: %s \n", 
              // i + 1, ventas[i].pizza_name, ventas[i].quantity, ventas[i].unit_price, ventas[i].pizza_ingredients);
   // }

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

    if (strcmp(argv[1], "pms") == 0) {
        pizza_mas_vendida(ventas, total_ventas);
    } 
    else if (strcmp(argv[1], "top3") == 0) {
        // top3_pizzas(ventas, total_ventas);
        printf("(Aquí se mostrarían las top 3 más vendidas)\n");
    } 
    else if (strcmp(argv[1], "cat") == 0) {
        // ventas_por_categoria(ventas, total_ventas);
        printf("(Aquí se mostraría la agrupación por categoría)\n");
    } 
    else {
        printf("Comando desconocido: %s\n", argv[1]);
    }

    return 0;
}
    

