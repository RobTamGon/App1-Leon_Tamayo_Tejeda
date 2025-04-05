#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>


void parsear_fecha_hora(const char *order_date, const char *order_time, struct tm *fecha) {
    // Inicializar la estructura a cero
    memset(fecha, 0, sizeof(struct tm));

    // Suponiendo que order_date está en formato "día/mes/año"
    // y order_time en formato "hora:minuto:segundo", por ejemplo: "1/1/2015" y "11:38:36"
    sscanf(order_date, "%d/%d/%d", &fecha->tm_mday, &fecha->tm_mon, &fecha->tm_year);
    sscanf(order_time, "%d:%d:%d", &fecha->tm_hour, &fecha->tm_min, &fecha->tm_sec);

    // Ajustes: tm_mon es 0-11 y tm_year es años transcurridos desde 1900
    fecha->tm_mon -= 1;
    fecha->tm_year -= 1900;
}

typedef struct {
    int pizza_id;
    int order_id;
    char pizza_name_id[50];
    float quantity;
    char order_date[20];
    char order_time[20];
    float unit_price;
    float total_price;
    char pizza_size[10];
    char pizza_category[50];
    char pizza_ingredients[200];
    char pizza_name[100];
} Venta;

typedef struct {
    char *contenido; // Puntero al contenido del archivo
    size_t tamano;   // Tamaño del archivo
} Archivo;

Archivo leer_archivo(const char *nombre_archivo) {
    Archivo archivo = {NULL, 0};
    FILE *fp = fopen(nombre_archivo, "r");
    if (!fp) {
        printf("Error: No se pudo abrir el archivo de entrada.\n");
        return archivo;
    }
    
    fseek(fp, 0, SEEK_END);
    archivo.tamano = ftell(fp);
    rewind(fp);
    
    archivo.contenido = (char *)malloc(archivo.tamano + 1);
    if (!archivo.contenido) {
        printf("Error: No se pudo asignar memoria.\n");
        fclose(fp);
        return archivo;
    }
    
    fread(archivo.contenido, 1, archivo.tamano, fp);
    archivo.contenido[archivo.tamano] = '\0';
    fclose(fp);
    
    return archivo;
}

Venta *parse_ventas(const char *nombre_archivo, int *nventas) {
    Archivo archivo = leer_archivo(nombre_archivo);
    if (!archivo.contenido) {
        *nventas = 0;
        return NULL;
    }

    // Contar líneas sin modificar el contenido original
    int total_lineas = 0;
    for (size_t i = 0; i < archivo.tamano; i++) {
        if (archivo.contenido[i] == '\n')
            total_lineas++;
    }
    // Se asume que el archivo tiene cabecera y al menos una línea de datos
    int num_datos = total_lineas - 1;
    *nventas = num_datos;

    // Reservar arreglo de estructuras
    Venta *ventas = malloc(sizeof(Venta) * num_datos);
    if (!ventas) {
        printf("Error: No se pudo asignar memoria para ventas.\n");
        free(archivo.contenido);
        *nventas = 0;
        return NULL;
    }

    // Procesar línea por línea
    char *contenido_copia = strdup(archivo.contenido);
    free(archivo.contenido);

    char *linea, *saveptr_line;
    int index = 0;
    // Obtener la primera línea (cabecera) y descartarla
    linea = strtok_r(contenido_copia, "\n", &saveptr_line);

    // Para cada línea de datos
    while ((linea = strtok_r(NULL, "\n", &saveptr_line)) != NULL && index < num_datos) {
        // Usamos strsep para separar cada campo por coma.
        // IMPORTANTE: Esto es un parser básico y no maneja de forma completa las comillas con comas en su interior.
        char *resto = linea;
        char *token;
        int campo = 0;
        while ((token = strsep(&resto, ",")) != NULL) {
            switch(campo) {
                case 0:
                    ventas[index].pizza_id = atoi(token);
                    break;
                case 1:
                    ventas[index].order_id = atoi(token);
                    break;
                case 2:
                    strncpy(ventas[index].pizza_name_id, token, sizeof(ventas[index].pizza_name_id)-1);
                    ventas[index].pizza_name_id[sizeof(ventas[index].pizza_name_id)-1] = '\0';
                    break;
                case 3:
                    ventas[index].quantity = atof(token);
                    break;
                case 4:
                    strncpy(ventas[index].order_date, token, sizeof(ventas[index].order_date)-1);
                    ventas[index].order_date[sizeof(ventas[index].order_date)-1] = '\0';
                    break;
                case 5:
                    strncpy(ventas[index].order_time, token, sizeof(ventas[index].order_time)-1);
                    ventas[index].order_time[sizeof(ventas[index].order_time)-1] = '\0';
                    break;
                case 6:
                    ventas[index].unit_price = atof(token);
                    break;
                case 7:
                    ventas[index].total_price = atof(token);
                    break;
                case 8:
                    strncpy(ventas[index].pizza_size, token, sizeof(ventas[index].pizza_size)-1);
                    ventas[index].pizza_size[sizeof(ventas[index].pizza_size)-1] = '\0';
                    break;
                case 9:
                    strncpy(ventas[index].pizza_category, token, sizeof(ventas[index].pizza_category)-1);
                    ventas[index].pizza_category[sizeof(ventas[index].pizza_category)-1] = '\0';
                    break;
                case 10:
                    strncpy(ventas[index].pizza_ingredients, token, sizeof(ventas[index].pizza_ingredients)-1);
                    ventas[index].pizza_ingredients[sizeof(ventas[index].pizza_ingredients)-1] = '\0';
                    break;
                case 11:
                    strncpy(ventas[index].pizza_name, token, sizeof(ventas[index].pizza_name)-1);
                    ventas[index].pizza_name[sizeof(ventas[index].pizza_name)-1] = '\0';
                    break;
                default:
                    break;
            }
            campo++;
        }
        index++;
    }
    free(contenido_copia);
    return ventas;
}