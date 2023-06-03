#include <stdio.h>

#define N 10

void leer_matriz(int A[N][N], int filas, int columnas);
void escribir_matriz(int A[N][N], int filas, int columnas);
void multiplicar(int A[N][N], int B[N][N], int C[N][N], int m, int n, int p);

int main() {
	// Declaracion de variables
	int m, n, p;
	int A[N][N], B[N][N], C[N][N];
	
	// Lectura de datos de la matriz A
	printf("\n Datos de la Matriz A: \n");
	printf("Filas: ");
	scanf("%d", &m);
	printf("Columnas: ");
	scanf("%d", &n);
	leer_matriz(A, m, n);
	
	// Lectura de datos de la matriz B
	printf("\n Datos de la Matriz B: \n");
	printf("Columnas: ");
	scanf("%d", &p);
	leer_matriz(B, n, p);
	
	// Impresion de las matrices A y B
	printf("\n Matriz A:\n");
	escribir_matriz(A, m, n);
	printf("\n Matriz B: \n");
	escribir_matriz(B, n, p);
	
	// Multiplicacion de las matrices A y B
	multiplicar(A, B, C, m, n, p);
	
	// Impresion de la matriz resultante C
	printf("\n Matriz AxB: \n");
	escribir_matriz(C, m, p);
}

// Funcion para leer una matriz
void leer_matriz(int A[N][N], int filas, int columnas) {
	int i, j;
	for (i = 0; i < filas; i++) {
		for (j = 0; j < columnas; j++) {
			printf("Ingresa la entrada [%d][%d]: ", i + 1, j + 1);
			scanf("%d", &A[i][j]);
		}
	}
}

// Funcion para escribir una matriz
void escribir_matriz(int A[N][N], int filas, int columnas) {
	int i, j;
	for (i = 0; i < filas; i++) {
		for (j = 0; j < columnas; j++) {
			printf("\t%d", A[i][j]);
		}
		printf("\n");
	}
}

// Funcion para multiplicar dos matrices
void multiplicar(int A[N][N], int B[N][N], int C[N][N], int m, int n, int p) {
	int i, j, k;
	
	// Limpiar o inicializar matriz C
	for (i = 0; i < m; i++)
		for (k = 0; k < p; k++)
			C[i][k] = 0;

	// Multiplicación de matrices
	for (i = 0; i < m; i++)
		for (j = 0; j < n; j++)
			for (k = 0; k < p; k++)
				C[i][k] = C[i][k] + A[i][j] * B[j][k];
}