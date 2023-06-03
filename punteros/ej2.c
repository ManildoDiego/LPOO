#include <stdio.h>

int main() {
	int x, *y; // se crea una variable x (int) y (puntero a entero)
	x = 10; // x es igual a 10
	y = &x; // el puntero ahora apunta a la direccion de memoria de x
	printf("%d %d %d", y, *y, &y);
	/*
		y  -> devuelve la direccion de memoria de la variable x
		*y -> devuelve el valor almacenado de la variable x, es decir, 10
		&y -> devuelve la posicion de memoria de la variable y
	*/
	return 0;
}
