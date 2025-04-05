#include <string.h>  // para strlen
#include "utils.h"

// Definimos la función de limpiar enter
void limpiar_enter(char *texto) {
    int len = strlen(texto);
    if (len > 0 && texto[len - 1] == '\n') {
        texto[len - 1] = '\0';
    }
}
