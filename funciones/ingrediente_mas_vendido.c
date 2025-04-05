#include <stdio.h>    // Para imprimir
#include <string.h>   // Para trabajar con texto (strcmp, strcpy, strtok)
#include <stdlib.h>   // Para pedir memoria
#include "../structs.h"
#include "../utils.h"
#include "ingrediente_mas_vendido.h"


#define MAX_INGREDIENTES 500  // Suponemos máximo 500 ingredientes distintos


char* ingrediente_mas_vendido(int *size, VentaPizza *ventas) {
    // Estructura temporal para guardar ingredientes
    typedef struct {
        char nombre[64];
        float cantidad_total;
    } IngredienteVenta;

    IngredienteVenta resumen[MAX_INGREDIENTES];  // Aquí vamos guardando los ingredientes
    int total_ingredientes = 0;
    int cantidad_ventas = *size;

    // 1. Recorrer todas las ventas
    for (int i = 0; i < cantidad_ventas; i++) {
        limpiar_enter(ventas[i].pizza_ingredients);  // Limpiar ingredientes de saltos raros

        char ingredientes[256];
        strcpy(ingredientes, ventas[i].pizza_ingredients);  // Copiar ingredientes para no modificar el original

        // Separar ingredientes uno por uno
        char *token = strtok(ingredientes, ",");
        while (token != NULL) {
            // Eliminar espacio inicial si hay
            while (*token == ' ') token++;

            int encontrado = 0;

            // Buscar si ya vimos este ingrediente antes
            for (int j = 0; j < total_ingredientes; j++) {
                if (strcmp(token, resumen[j].nombre) == 0) {
                    resumen[j].cantidad_total += ventas[i].quantity;
                    encontrado = 1;
                    break;
                }
            }

            // Si es un ingrediente nuevo, lo agregamos
            if (!encontrado) {
                strcpy(resumen[total_ingredientes].nombre, token);
                resumen[total_ingredientes].cantidad_total = ventas[i].quantity;
                total_ingredientes++;
            }

            // Pasar al siguiente ingrediente
            token = strtok(NULL, ",");
        }
    }

    // 2. Si no encontramos ingredientes
    if (total_ingredientes == 0) {
        char *mensaje = malloc(64);
        strcpy(mensaje, "No se encontraron ingredientes válidos.");
        return mensaje;
    }

    // 3. Buscar el ingrediente más vendido
    float mayor_venta = 0;
    for (int i = 0; i < total_ingredientes; i++) {
        if (resumen[i].cantidad_total > mayor_venta) {
            mayor_venta = resumen[i].cantidad_total;
        }
    }

    // 4. Armar la respuesta
    char *respuesta = malloc(2048);
    strcpy(respuesta, "Ingrediente mas vendido: ");

    int primera = 1;
    for (int i = 0; i < total_ingredientes; i++) {
        if (resumen[i].cantidad_total == mayor_venta) {
            if (!primera) {
                strcat(respuesta, ", ");  // Coma si ya agregamos uno antes
            }
            strcat(respuesta, resumen[i].nombre);  // Agregamos el nombre del ingrediente
            primera = 0;
        }
    }

    // Agregar la cantidad de unidades vendidas
    char cantidad_texto[64];
    sprintf(cantidad_texto, " (%.0f unidades)", mayor_venta);
    strcat(respuesta, cantidad_texto);

    return respuesta;
}
