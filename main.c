#include <stdio.h>

//ESTA PARTE ES TEMPORAL, SOLAMENTE PARA PROBAR
struct Venta
{
	int a;
	int b;
};

char* f1(int *size, struct Venta *Ventas)
{
	return "f1";
}

char* f2(int *size, struct Venta *Ventas)
{
	return "f2";
}

char* f3(int *size, struct Venta *Ventas)
{
	return "f3";
}

char* f4(int *size, struct Venta *Ventas)
{
	return "f4";
}

char* f5(int *size, struct Venta *Ventas)
{
	return "f5";
}

char* f6(int *size, struct Venta *Ventas)
{
	return "f6";
}

char* f7(int *size, struct Venta *Ventas)
{
	return "f7";
}

char* f8(int *size, struct Venta *Ventas)
{
	return "f8";
}

char* f9(int *size, struct Venta *Ventas)
{
	return "f9";
}

char* f10(int *size, struct Venta *Ventas)
{
	return "f10";
}


int main(int argc, char *argv[])
{
	printf("Argument Count: %i\n", argc);
	for (int i = 0; i < argc; i++)
	{
		printf("%s\n", argv[i]);
	}

	struct Venta V;
	V.a = 1;
	V.b = 2;

	int T = 10;

	char* (*pointer)(int*, struct Venta*) = f1;

	printf("%s\n\n", (*pointer)(&T, &V));

	char* (*metricas[argc - 2])(int*, struct Venta*);

	for (int i = 2; i < argc; i++)
	{
		//O UN SWITCH PARA CADA MÉTRICA
		// O UNA LISTA DE PARÁMETROS, Y UNA LISTA DE PUNTEROS
		//QUIZÁS EN UNA FUNCIÓN DEDICADA A CONVERTIR LOS PARÁMETROS EN UNA LISTA DE PUNTEROS A FUNCIONES
		printf("%s\n", argv[i]);
	}





	return 0;
}