#include "leer_csv.h"
#include <string.h>

#define MAX_LINE_LENGTH 512 // Límite máximo de longitud de una línea

Venta* leer_csv(const char* nombre_archivo, int* largo) {
    FILE* archivo = fopen(nombre_archivo, "r"); // Abrimos el archivo en modo lectura
    if (!archivo) {
        perror("Error al abrir el archivo CSV"); // Error al abrir el archivo
        return NULL;
    }

    char linea[MAX_LINE_LENGTH]; // Reservamos espacio para la líneas
    *largo = 0; // Inicializamos el contador de líneas a 0 

    // Leer la primera línea del archivo
    fgets(linea, sizeof(linea), archivo); // Ignoramos la cabecera

    // Contar líneas para saber cuántas órdenes hay
    while (fgets(linea, sizeof(linea), archivo)) {
        (*largo)++;
    }
    rewind(archivo); // Volvemos al inicio del archivo

    // Leer la primera línea del archivo
    fgets(linea, sizeof(linea), archivo); // Para ignorar la cabecera

    // Reservamos memoria para todas las órdenes
    Venta* ventas = malloc((*largo) * sizeof(Venta)); // Reservamos espacio para todas las órdenes
    if (!ventas) {
        perror("Error al asignar memoria"); // Error al asignar memoria
        fclose(archivo);
        return NULL;
    }

    // Leer las líneas y parsear datos
    int i = 0; // Inicializamos el contador de líneas
    while (fgets(linea, sizeof(linea), archivo)) { // Leemos cada línea del archivo
        // Parsear los datos de la línea
        sscanf(linea, "%d,%d,%49[^,],%f,%14[^,],%9[^,],%f,%f,%3[^,],%19[^,],\"%199[^\"]\",%49[^\n]", // Leemos los datos de la línea
            &ventas[i].pizza_id, &ventas[i].order_id, ventas[i].pizza_name_id, 
            &ventas[i].quantity, ventas[i].order_date, ventas[i].order_time, 
            &ventas[i].unit_price, &ventas[i].total_price, &ventas[i].pizza_size, 
            ventas[i].pizza_category, ventas[i].pizza_ingredients, ventas[i].pizza_name);

        i++; // Aumentamos el contador de líneas
    }

    fclose(archivo); // Cerramos el archivo
    return ventas; // Devolver las órdenes
}

// Función para liberar la memoria asignada a las órdenes
void liberar_ventas(Venta* ventas) { 
    free(ventas); // Liberar la memoria asignada a las órdenes
}
