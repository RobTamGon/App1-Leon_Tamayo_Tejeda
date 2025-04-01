# Variables para configurar el Makefile
TARGET = app1
COMPILER = gcc
OBJECTS = main.o

# Modifica algunos parámetros según el sistema operativo que lo ejecute
# (Windows también requiere añadir la extensión .exe al ejecutable cuando se borre este archivo al limpiar)
ifeq ($(OS), Windows_NT)
	APP = $(TARGET).exe

    RM = cmd /c del /f
else
    RM = -rm -f
endif


# Target de compilación
# (También elimina los Objetos (.o) intermedios después de crear el ejecutable)
all: $(TARGET)
	$(RM) $(OBJECTS)


# Vinculación de Objetos intermedios al ejecutable
$(TARGET): $(OBJECTS)
	$(COMPILER) -o $(TARGET) $(OBJECTS)

# Archivos .c y .h a compilar en Objetos (.o)
main.o: main.c
	$(COMPILER) -c main.c

# Instrucción para limpiar el directorio, eliminando el archivo ejecutable y los objetos (.o) intermedios
# (Ejemplo: make clean)
.PHONY: clean
clean:
	$(RM) $(APP) *.o