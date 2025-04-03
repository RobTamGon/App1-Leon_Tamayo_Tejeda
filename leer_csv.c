#include "leer_csv.h"
#include <string.h>

#define MAX_LINE_LENGTH 512

Venta* leer_csv(const char* nombre_archivo, int* contador) {
    FILE* archivo = fopen(nombre_archivo, "r");
    if (!archivo) {
        perror("Error al abrir el archivo CSV");
        return NULL;
    }

    char linea[MAX_LINE_LENGTH];
    *contador = 0;

    // Contar líneas para saber cuántas órdenes hay
    while (fgets(linea, sizeof(linea), archivo)) {
        (*contador)++;
    }
    rewind(archivo); // Volvemos al inicio del archivo

    // Reservamos memoria para todas las órdenes
    Venta* ventas = malloc((*contador) * sizeof(Venta));
    if (!ventas) {
        perror("Error al asignar memoria");
        fclose(archivo);
        return NULL;
    }

    // Leer las líneas y parsear datos
    int i = 0;
    while (fgets(linea, sizeof(linea), archivo)) {
        sscanf(linea, "%d,%d,%49[^,],%lf,%14[^,],%9[^,],%lf,%lf,%c,%19[^,],\"%199[^\"]\",%49[^\n]",
            &ventas[i].pizza_id, &ventas[i].order_id, ventas[i].pizza_name_id,
            &ventas[i].quantity, ventas[i].order_date, ventas[i].order_time,
            &ventas[i].unit_price, &ventas[i].total_price, &ventas[i].pizza_size,
            ventas[i].pizza_category, ventas[i].pizza_ingredients, ventas[i].pizza_name);
        i++;
    }

    fclose(archivo);
    return ventas;
}

void liberar_ventas(Venta* ventas) {
    free(ventas);
}
