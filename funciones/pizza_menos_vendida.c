#include <stdio.h>    // Para imprimir
#include <string.h>   // Para comparar y copiar textos
#include <stdlib.h>   // Para pedir memoria
#include "../structs.h"
#include "../utils.h"
#include "pizza_menos_vendida.h"

#define MAX_PIZZAS 200  // Suponemos máximo 200 tipos de pizzas


char* pizza_menos_vendida(int *size, VentaPizza *ventas) {
    PizzaVenta resumen[MAX_PIZZAS];  // Aquí guardamos las pizzas que vayamos encontrando
    int total_pizzas = 0;
    int cantidad_ventas = *size;     // Cuántas ventas hay

    // 1. Recorrer todas las ventas
    for (int i = 0; i < cantidad_ventas; i++) {
        limpiar_enter(ventas[i].pizza_name);  // Limpiamos nombres que tengan saltos de línea
        int encontrada = 0;  // Para saber si ya vimos esta pizza antes

        // Revisar si ya tenemos esta pizza
        for (int j = 0; j < total_pizzas; j++) {
            if (strcmp(ventas[i].pizza_name, resumen[j].nombre) == 0) {
                resumen[j].cantidad_total += ventas[i].quantity;  // Sumamos la cantidad
                encontrada = 1;
                break;
            }
        }

        // Si es una pizza nueva, la agregamos al resumen
        if (!encontrada) {
            strcpy(resumen[total_pizzas].nombre, ventas[i].pizza_name);
            resumen[total_pizzas].cantidad_total = ventas[i].quantity;
            total_pizzas++;
        }
    }

    // 2. Si no hay ventas, devolvemos un mensaje
    if (total_pizzas == 0) {
        char *mensaje = malloc(64);
        strcpy(mensaje, "No se encontraron ventas válidas.");
        return mensaje;
    }

    // 3. Buscar la menor cantidad de ventas
    float menor_venta = resumen[0].cantidad_total;  // Empezamos con la primera pizza
    for (int i = 1; i < total_pizzas; i++) {
        if (resumen[i].cantidad_total < menor_venta) {
            menor_venta = resumen[i].cantidad_total;
        }
    }

    // 4. Armar el resultado
    char *respuesta = malloc(2048);  // Reservamos espacio suficiente
    strcpy(respuesta, "Pizza menos vendida: ");

    int primera = 1;  // Para manejar las comas
    for (int i = 0; i < total_pizzas; i++) {
        if (resumen[i].cantidad_total == menor_venta) {
            if (!primera) {
                strcat(respuesta, ", ");  // Agregamos coma si no es la primera
            }
            strcat(respuesta, resumen[i].nombre);  // Agregamos el nombre de la pizza
            primera = 0;
        }
    }

    // Agregar al final la cantidad de unidades vendidas
    char cantidad_texto[64];
    sprintf(cantidad_texto, " (%.0f unidades)", menor_venta);
    strcat(respuesta, cantidad_texto);

    return respuesta;  // Devolvemos el texto completo
}
