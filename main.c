#include <stdio.h>
#include "leer_csv.h"
#include "ventas_fechas.h"
#include "ventas_pizzas.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Uso: %s <archivo_csv>\n", argv[0]);
        return 1;
    }

    int contador_ventas;
    Venta* ventas = leer_csv(argv[1], &contador_ventas);

    if (!ventas) {
        return 1;
    }

    printf("Se cargaron %d ordenes:\n", contador_ventas);
    for (int i = 0; i < contador_ventas; i++) {
        printf("%d - %s - %.2f unidades\n", ventas[i].order_id, ventas[i].pizza_name, ventas[i].quantity);
    }

    // Imprime la fecha con más ventas en cantidad de pizzas
    printf("%s" , encontrar_fecha_mas_vendida(&contador_ventas, ventas));
    printf("\n");

    // Imprime la fecha con más ventas en dinero
    printf("%s", encontrar_fecha_mas_ingresos(&contador_ventas, ventas));
    printf("\n");

    // Imprime la fecha con menos ventas en cantidad de pizzas
    printf("%s", encontrar_fecha_menos_vendida(&contador_ventas, ventas));
    printf("\n");

    // Imprime la fecha con menos ventas en dinero
    printf("%s", encontrar_fecha_menos_ingresos(&contador_ventas, ventas));
    printf("\n");

    // Imprime la fecha con menos ventas en dinero
    printf("%s", encontrar_pizza_mas_vendida(&contador_ventas, ventas));
    printf("\n");

    // Imprime la fecha con menos ventas en dinero
    printf("%s", encontrar_pizza_menos_vendida(&contador_ventas, ventas));
    printf("\n");

    // Imprime la fecha con menos ventas en dinero
    printf("%s", encontrar_ingrediente_mas_vendido(&contador_ventas, ventas));
    printf("\n");

    liberar_ventas(ventas);
    return 0;
}
