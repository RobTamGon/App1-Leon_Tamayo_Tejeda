#include <stdio.h>      // Librería estándar para entrada y salida (como printf, fopen, etc.)
#include <stdlib.h>     // Librería estándar para funciones como atof, malloc, exit, etc.
#include <string.h>     // Librería para manipular strings (como strcpy, strlen, etc.)
#include "../structs.h"    // Archivo propio donde se definió la estructura VentaPizza

#define MAX_LINEA 1024      // Tamaño máximo de una línea del CSV
#define MAX_CAMPOS 20       // Máximo número de campos por línea

void limpiar_comillas(char *campo) {
    size_t len = strlen(campo);
    if (len >= 2 && campo[0] == '"' && campo[len - 1] == '"') {
        // Corre todos los caracteres una posición hacia la izquierda
        memmove(campo, campo + 1, len - 2);
        campo[len - 2] = '\0';  // Añade el fin de string correctamente
    }
}

int leer_csv(const char *nombre_archivo, VentaPizza ventas[], int max_ventas) {
    FILE *archivo = fopen(nombre_archivo, "r");  // Abre el archivo CSV en modo lectura
    if (!archivo) {                           // Si no se puede abrir el archivo
        perror("No se pudo abrir el archivo"); // Muestra un mensaje de error en consola
        return 1;                             // Sale del programa con error
    }

    char linea[MAX_LINEA];          // Arreglo para guardar una línea completa del archivo
    char *campos[MAX_CAMPOS];       // Arreglo de punteros para almacenar cada campo de una línea
    int total_ventas = 0;           // Contador de ventas leídas

    // Ignorar la primera fila (encabezados)
    fgets(linea, sizeof(linea), archivo);

    // Leer línea por línea
    while (fgets(linea, sizeof(linea), archivo)&& total_ventas < max_ventas) { // Lee una línea del archivo CSV
        int i = 0; // Contador de campos
        char *ptr = linea; // Puntero para recorrer la línea carácter por carácter
        int entre_comillas = 0; // Variable para saber si estamos dentro de comillas (0 = no, 1 = sí)
        campos[i++] = ptr; // El primer campo comienza desde el inicio de la línea
    
        while (*ptr) { // Mientras no lleguemos al final de la línea (carácter nulo '\0')
            if (*ptr == '"') { // Si encontramos una comilla doble (")
                entre_comillas = !entre_comillas; // Cambiamos el estado (dentro/fuera de comillas)
            }
            else if (*ptr == ',' && !entre_comillas) { // Si encontramos una coma fuera de comillas
                *ptr = '\0'; // Reemplazamos la coma por un carácter nulo, cortando el campo actual
                campos[i++] = ptr + 1; // El siguiente campo comienza justo después de la coma
            }
            ptr++; // Avanzamos al siguiente carácter de la línea
        }
        
        // Creamos una nueva estructura para almacenar esta venta
        VentaPizza v;

        // Limpiar comillas dobles si existen en ingredientes y nombre de pizza
        limpiar_comillas(campos[10]);
        limpiar_comillas(campos[11]);

        // Copiamos cada campo leído desde el CSV a los campos de la estructura
        strcpy(v.pizza_id, campos[0]);           // ID de la pizza
        strcpy(v.order_id, campos[1]);           // ID del pedido
        strcpy(v.pizza_name_id, campos[2]);      // ID del nombre de la pizza
        v.quantity = atof(campos[3]);            // Cantidad (convertimos string a float)
        strcpy(v.order_date, campos[4]);         // Fecha del pedido
        strcpy(v.order_time, campos[5]);         // Hora del pedido
        v.unit_price = atof(campos[6]);          // Precio unitario (string a float)
        v.total_price = atof(campos[7]);         // Precio total (string a float)
        strcpy(v.pizza_size, campos[8]);         // Tamaño de la pizza (S, M, L, etc.)
        strcpy(v.pizza_category, campos[9]);     // Categoría (vegetariana, clásica, etc.)
        strcpy(v.pizza_ingredients, campos[10]); // Ingredientes (cadena larga)
        strcpy(v.pizza_name, campos[11]);        // Nombre real de la pizza

        ventas[total_ventas++] = v; // Guardamos la estructura en el arreglo y aumentamos el contador

    }
    fclose(archivo); // Cerramos el archivo CSV
    return total_ventas;
}
