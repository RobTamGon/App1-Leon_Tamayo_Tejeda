#include "leer_csv.h"
#include <string.h>

#define MAX_LINE_LENGTH 512

Venta* leer_csv(const char* nombre_archivo, int* largo) {
    FILE* archivo = fopen(nombre_archivo, "r");
    if (!archivo) {
        perror("Error al abrir el archivo CSV");
        return NULL;
    }

    char linea[MAX_LINE_LENGTH];
    *largo = 0; // Inicializamos el contador de líneas a 1 para la segunda línea (cabecera)

    // Leer la primera línea del archivo
    fgets(linea, sizeof(linea), archivo); // Ignoramos la cabecera
    
    // Contar líneas para saber cuántas órdenes hay
    while (fgets(linea, sizeof(linea), archivo)) {
        (*largo)++;
    }
    rewind(archivo); // Volvemos al inicio del archivo

    // Leer la primera línea del archivo
    fgets(linea, sizeof(linea), archivo); // Ignoramos la cabecera

    // Reservamos memoria para todas las órdenes
    Venta* ventas = malloc((*largo) * sizeof(Venta));
    if (!ventas) {
        perror("Error al asignar memoria");
        fclose(archivo);
        return NULL;
    }

    // Leer las líneas y parsear datos
    int i = 0;
    while (fgets(linea, sizeof(linea), archivo)) {
        sscanf(linea, "%d,%d,%49[^,],%f,%14[^,],%9[^,],%f,%f,%c,%19[^,],\"%199[^\"]\",%49[^\n]",
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
