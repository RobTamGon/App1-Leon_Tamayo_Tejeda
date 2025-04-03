#ifndef METRICAS_H
#define METRICAS_H

#include "structs.h"

// Firma de función para todas las métricas
typedef char* (*FuncionMetrica)(int*, VentaPizza*);

// Estructura para asociar nombre de métrica con su función
typedef struct {
    char *codigo;
    FuncionMetrica funcion;
} Metrica;

// Declaración del arreglo de métricas
extern Metrica metricas[];
extern int total_metricas;

#endif
