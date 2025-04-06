#ifndef CARGAR_ORDENES_H
#define CARGAR_ORDENES_H

#include "../structs.h"

int obtener_cantidad_ordenes(const char *nombre_archivo);
void cargar_ordenes(const char *nombre_archivo, order *ordenes);

#endif