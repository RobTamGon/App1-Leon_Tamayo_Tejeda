#include <stdio.h>    // Para poder imprimir y trabajar con texto
#include <string.h>   // Para comparar y copiar textos (como los nombres de pizzas)
#include <stdlib.h>   // Para pedir memoria al computador (malloc y free)
#include "../structs.h"   // Archivo donde están definidas nuestras estructuras
#include "pizza_mas_vendida.h"  // Donde escribimos el prototipo de esta función
#include "../utils.h"

#define MAX_PIZZAS 10000   // Vamos a asumir que como máximo hay 200 tipos de pizzas


// Función principal que encuentra cuál fue la pizza más vendida
char* pizza_mas_vendida(int *size, VentaPizza *ventas) {
    PizzaVenta resumen[MAX_PIZZAS];  // Aquí vamos a guardar las pizzas distintas y cuánto vendieron
    int total_pizzas = 0;             // Cuántas pizzas distintas hemos encontrado
    int cantidad_ventas = *size;      // Cuántas ventas hay en total

     // Vamos a recorrer todas las ventas una por una
     for (int i = 0; i < cantidad_ventas; i++) {
        limpiar_enter(ventas[i].pizza_name);  // Primero, limpiamos el nombre por si trae un enter escondido
        int encontrada = 0;  // Esta variable nos dice si ya habíamos visto esta pizza antes

         // Recorremos el resumen que llevamos hecho hasta ahora
         for (int j = 0; j < total_pizzas; j++) {
            // Comparamos si la pizza ya estaba
            if (strcmp(ventas[i].pizza_name, resumen[j].nombre) == 0) {
                // Si la encontramos, sumamos las unidades vendidas
                resumen[j].cantidad_total += ventas[i].quantity;
                encontrada = 1;  // Ya la encontramos, no hay que agregarla de nuevo
                break;           // Salimos del for
            }
        }

         // Si no la encontramos, es una pizza nueva
         if (!encontrada) {
            strcpy(resumen[total_pizzas].nombre, ventas[i].pizza_name);  // Guardamos su nombre
            resumen[total_pizzas].cantidad_total = ventas[i].quantity;   // Guardamos cuántas unidades se vendieron
            total_pizzas++;  // Aumentamos el contador de pizzas distintas
        }
    }

     // Ahora que ya tenemos todo el resumen, buscamos cuál pizza se vendió más veces
     float mayor_venta = 0;  // Aquí vamos a guardar el número mayor de unidades vendidas
     for (int i = 0; i < total_pizzas; i++) {
         if (resumen[i].cantidad_total > mayor_venta) {
             mayor_venta = resumen[i].cantidad_total;  // Actualizamos si encontramos una pizza con más ventas
         }
     }

    // Si por alguna razón no hubo ventas, devolvemos un mensaje que diga eso
    if (mayor_venta == 0) {
        char *mensaje = malloc(64);  // Reservamos espacio para el mensaje
        strcpy(mensaje, "No se encontraron ventas válidas.");  // Copiamos el mensaje
        return mensaje;  // Lo devolvemos
    }

     // Ahora creamos el texto final que vamos a devolver
    char *respuesta = malloc(2048);  // Reservamos espacio de sobra
    strcpy(respuesta, "Pizza mas vendida: ");  // Empezamos escribiendo la primera parte del mensaje

    int primera = 1;  // Esto nos ayuda a saber si tenemos que poner coma o no
    // Recorremos otra vez todas las pizzas
    for (int i = 0; i < total_pizzas; i++) {
        if (resumen[i].cantidad_total == mayor_venta) {
            if (!primera) {
                strcat(respuesta, ", ");  // Si ya pusimos una pizza antes, agregamos una coma
            }
            strcat(respuesta, resumen[i].nombre);  // Agregamos el nombre de la pizza
            primera = 0;  // Después de la primera, siempre agregaremos comas
        }
    }

        // Al final agregamos entre paréntesis la cantidad de unidades vendidas
        char cantidad_texto[64];
        sprintf(cantidad_texto, " (%.0f unidades)", mayor_venta);  // Convertimos el número en texto
        strcat(respuesta, cantidad_texto);  // Lo pegamos al mensaje
    
        return respuesta;  // Devolvemos el texto completo para que lo impriman donde quieran
    }
    