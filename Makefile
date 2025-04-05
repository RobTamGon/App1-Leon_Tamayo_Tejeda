# Variables para configurar el Makefile
TARGET = app1
COMPILER = gcc
OBJECTS = main.o cargar_ordenes.o atributo_mayor_menor.o fecha_mayor_menor.o estadisticas_cantidades.o

# Modifica algunos parámetros según el sistema operativo que lo ejecute
# (Windows también requiere añadir la extensión .exe al ejecutable cuando se borre este archivo al limpiar)
ifeq ($(OS), Windows_NT)
	APP = $(TARGET).exe

    RM = cmd /c del /f
else
    RM = -rm -f
endif


# Target de compilación e impresión de instrucciones de ejecución después de terminar proceso de crear el ejecutable
# (También elimina los Objetos (.o) intermedios después de crear el ejecutable)
all: $(TARGET)
	$(RM) $(OBJECTS)
	@echo ################################################################################################################################
	@echo # PROGRAMA COMPILADO EXITOSAMENTE                                                                                              #
	@echo ################################################################################################################################
	@echo # INSTRUCCIONES PARA EJECUTAR EL PROGRAMA:                                                                                     #
	@echo # ---------------------------------------------------------------------------------------------------------------------------- #
	@echo # PASO 1                                                                                                                       #
	@echo # Acceda a la carpeta con el proyecto en una terminal usando el comando cd, y escriba:                                         #
	@echo # ./app1                                                                                                                       #
	@echo # ---------------------------------------------------------------------------------------------------------------------------- #
	@echo # PASO 2                                                                                                                       #
	@echo # Luego, para conocer datos sobre las ventas, separando por un espacio cada vez siguiendo la parte del comando ya escrito      #
	@echo # puede agregar cualquiera de los siguientes argumentos sin importar el orden:                                                 #
	@echo # - pms: Pizza mas vendida                                                                                                     #
	@echo # - pls: Pizza menos vendida                                                                                                   #
	@echo # - dms: Fecha con mas ventas en terminos de dinero (junto a la cantidad de dinero recaudado)                                  #
	@echo # - dls: Fecha con menos ventas en terminos de dinero (junto a la cantidad de dinero recaudado)                                #
	@echo # - dmsp: Fecha con mas ventas en terminos de cantidad de pizzas (junto a la cantidad de pizzas)                               #
	@echo # - dlsp: Fecha con menos ventas en terminos de cantidad de pizzas (junto a la cantidad de pizzas)                             #
	@echo # - apo: Promedio de pizzas por orden                                                                                          #
	@echo # - apd: Promedio de pizzas por dia                                                                                            #
	@echo # - ims: Ingrediente mas vendido                                                                                               #
	@echo # - hp: Cantidad de pizzas por categoria vendidas                                                                              #
	@echo # ---------------------------------------------------------------------------------------------------------------------------- #
	@echo # PASO 3                                                                                                                       #
	@echo # Presione enter para ejecutar el programa con los argumentos agregados.                                                       #
	@echo # ---------------------------------------------------------------------------------------------------------------------------- #
	@echo # EJEMPLO                                                                                                                      #
	@echo # Para mostrar todos los datos posibles, escriba:                                                                              #
	@echo # ./app1 ventas.csv pms pls dms dls dmsp dlsp apo apd ims hp                                                                   #
	@echo ################################################################################################################################


# Vinculación de Objetos intermedios al ejecutable
$(TARGET): $(OBJECTS)
	$(COMPILER) -o $(TARGET) $(OBJECTS)

# Archivos .c y .h a compilar en Objetos (.o)
main.o: main.c structs.h
	$(COMPILER) -c main.c

cargar_ordenes.o: archivo/cargar_ordenes.c archivo/cargar_ordenes.h structs.h
	$(COMPILER) -c archivo/cargar_ordenes.c

atributo_mayor_menor.o: metricas/atributo_mayor_menor.c metricas/atributo_mayor_menor.h structs.h
	$(COMPILER) -c metricas/atributo_mayor_menor.c

fecha_mayor_menor.o: metricas/fecha_mayor_menor.c metricas/fecha_mayor_menor.h structs.h
	$(COMPILER) -c metricas/fecha_mayor_menor.c

estadisticas_cantidades.o: metricas/estadisticas_cantidades.c metricas/estadisticas_cantidades.h structs.h
	$(COMPILER) -c metricas/estadisticas_cantidades.c

# Instrucción para limpiar el directorio, eliminando el archivo ejecutable y los objetos (.o) intermedios
# (Ejemplo: make clean)
.PHONY: clean
clean:
	$(RM) $(APP) *.o