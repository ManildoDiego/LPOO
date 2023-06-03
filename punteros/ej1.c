#include <stdio.h>

void ordenarNumeros(int *numeros, int size) {
	int temp;
	for (int i = 0; i < size - 1; i++) {
	  for (int j = 0; j < size - i - 1; j++) {
			if (*(numeros + j) > *(numeros + j + 1)) {
			  temp = *(numeros + j);
			  *(numeros + j) = *(numeros + j + 1);
			  *(numeros + j + 1) = temp;
			}
	  }
	}
}

int main() {
	int numeros[5];

	for (size_t i = 0; i < 5; i++) {
	  printf("Ingrese numero %llu: ", i + 1);
	  scanf("%d", &numeros[i]);
	}

	ordenarNumeros(numeros, 5);

	int a = numeros[0];
	int b = numeros[1];
	int c = numeros[2];
	int d = numeros[3];
	int e = numeros[4];

	printf("Numeros ordenados: %d, %d, %d, %d, %d\n", a, b, c, d, e);

	return 0;
}