#include <stdio.h>
#include "leer_csv.h"

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

    printf("Se cargaron %d órdenes:\n", contador_ventas);
    for (int i = 0; i < contador_ventas; i++) {
        printf("%d - %s - %d unidades\n", ventas[i].order_id, ventas[i].pizza_name, ventas[i].quantity);
    }

    liberar_ventas(ventas);
    return 0;
}
