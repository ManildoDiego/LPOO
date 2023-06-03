#include <stdio.h>

void carga(int n, int Vector[]);    // foward declaration de la funcion carga
void imprimir(int n, int Vector[]); // foward declaration de la funcion imprimir
void ordenar(int n, int Vector[]);  // foward declaration de la funcion ordenar

int main() {
	int n = 5; // se crea un entero y se le asigna el numero 5
	int V[n]; // se crea un array de 5 espacios de memoria
	carga(n, V); // llama a la funcion carga con sus respectivos parametros
	imprimir(n, V); // llama a la funcion imprimir con sus respectivos parametros
	ordenar(n, V); // llama a la funcion ordenar con sus respectivos parametros
	imprimir(n, V); // llama a la funcion imprimir con sus respectivos parametros

	printf("\n");
	for (int i = 0; i < n; i++) {
		printf("%5d", V[i]);
	}
	return 0;
}

void carga(int n, int Vector[]) {
	for (int i = 0; i < n; i++) {
		printf("ingrese el valor de la posicion %d: ", i);
		scanf("%d", &Vector[i]);
	}
}

void imprimir(int n, int Vector[]) {
	for (int i = 0; i < n; i++) {
		printf("\n %5d", Vector[i]);
	}
	printf("\n");
}

void ordenar(int n, int Vector[]) {
	int aux;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (Vector[i] > Vector[j]) {
				aux = Vector[i];
				Vector[i] = Vector[j];
				Vector[j] = aux;
			}
		}
	}
	printf("\n");
}
