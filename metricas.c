#include "metricas.h"
#include "funciones/pizza_mas_vendida.h"
#include "funciones/pizza_menos_vendida.h"

Metrica metricas[] = {
    {"pms", metrica_pms},
    {"pls", metrica_pls},
};

int total_metricas = sizeof(metricas) / sizeof(Metrica);
