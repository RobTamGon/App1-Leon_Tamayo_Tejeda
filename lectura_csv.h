//Creamos un archivo .h (header) para declarar las funciones, estructuras 
//y constantes que queremos usar desde otros archivos .c, sin tener que copiar el código. 
//Esto permite organizar el programa en módulos separados, facilita la reutilización del código y mejora el mantenimiento, 
//ya que cualquier cambio se centraliza en un solo lugar.
#ifndef LECTURA_CSV_H
#define LECTURA_CSV_H

#include "structs.h"

int leer_csv(const char *nombre_archivo, VentaPizza ventas[], int max_ventas);

#endif
