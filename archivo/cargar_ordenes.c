#include <stdio.h>				// Para imprimir (perror) y manipular archivos (fopen, fgets, sscanf y fclose)

#include "../structs.h"			// Contiene la estructura de datos order

#define MAX_LARGO_LINEA 1024	// Tamaño máximo de una línea del archivo CSV a procesar



// Obtiene el largo del archivo CSV entregado
// (Ignorando la primera línea para que el resultado equivalga a la cantidad de órdenes a procesar)
int obtener_cantidad_ordenes(const char *nombre_archivo)
{
	// Abre el archivo para leer, con un check para avisar si el archivo no existe o no se puede leer
	FILE* archivo = fopen(nombre_archivo, "r");
	if (!archivo)
	{
		perror("ERROR al abrir el archivo CSV");
		return -1;
	}

	// Inicializa la variable a contener temporalmente las líneas y el contador largo para regresar como resultado
	char linea[MAX_LARGO_LINEA];
	int largo = 0;

	// Omite la primera línea para que largo equivalga a la cantidad de órdenes
	// (Lo que descuenta la fila de nombres de las columnas)
	fgets(linea, MAX_LARGO_LINEA, archivo);

	// Itera hasta el final del archivo, contando las líneas, para regresar la cuenta final
	while (fgets(linea, MAX_LARGO_LINEA, archivo))
	{
		largo++;
	}

	return largo;
}


// Carga la lista de órdenes a partir de lo extraído del archivo CSV entregado
void cargar_ordenes(const char *nombre_archivo, order *ordenes)
{
	// Abre el archivo para leer, con un check para avisar si el archivo no existe o no se puede leer
	FILE* archivo = fopen(nombre_archivo, "r");
	if (!archivo)
	{
		perror("ERROR al abrir el archivo CSV");
		return;
	}


	// Inicializa la variable a contener temporalmente las líneas
	char linea[MAX_LARGO_LINEA];

	// Lee la primera línea del archivo para ignorar la fila de nombres de las columnas
	fgets(linea, MAX_LARGO_LINEA, archivo);

	// Lee las líneas y convierte el texto en datos para guardar en las estructuras order
	int i = 0;
	while (fgets(linea, MAX_LARGO_LINEA, archivo))
	{
		sscanf(linea, "%f,%f,%49[^,],%f,%14[^,],%9[^,],%f,%f,%3[^,],%19[^,],\"%199[^\"]\",%49[^\n]",
			&ordenes[i].pizza_id,
			&ordenes[i].order_id,
			ordenes[i].pizza_name_id,
			&ordenes[i].quantity,
			ordenes[i].order_date,
			ordenes[i].order_time,
			&ordenes[i].unit_price,
			&ordenes[i].total_price,
			ordenes[i].pizza_size,
			ordenes[i].pizza_category,
			ordenes[i].pizza_ingredients, //SE PODRÍA HACER QUE EN cargar_ordenes SE SEPAREN, DE TAL FORMA QUE pizza_ingredients SEA UNA LISTA CON LOS INGREDIENTES
			ordenes[i].pizza_name
		);

		i++;
	}

	fclose(archivo);
}